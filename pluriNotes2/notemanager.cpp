#include "notemanager.h"
#include "plurinotes.h"
#include <QFile>
#include<QDate>

using namespace std;

NoteManager* NoteManager::instance = NULL;

unsigned int NoteManager::newId() {
    return id++;
}

NoteManager::NoteManager() : versions(0), id(0), directory("C:\\Users\\CDespagne\\Desktop\\pluriNotes2") {}

NoteManager::~NoteManager() {
    saveAll(); //fonction qui sauve le texte des Notes sur un fichier en mémoire
    versions.clear(); // destruction des vecteurs internes. les destructeurs appelés libèrent la mémoire automatiquement
}

NoteManager& NoteManager::getInstance() {
    if (!instance) {
        //Création de l'instance unique si ce n'est pas encore fait. Seules les méthodes membres de NoteManager accèdent à son constructeur.
        instance = new NoteManager;
    }
    return *instance;
}

Article* NoteManager::makeArticle() {
    //QString id = newId();
    qDebug()<<"Entree1";
    //QDate date;
    QDate date = QDate::currentDate();
    qDebug()<<"Entree3";
    Article* a= new Article("","",date,date,"","");
    QVector<Note*> NewNote;
    NewNote.push_back(a);
    versions.push_back(NewNote);

    return a;
    //
}

Tache* NoteManager::makeTache() {
    QString id = newId();
    QDate date;
    return new Tache(id,"",date,date,"",0,date,En_cours, "");
}

Media* NoteManager::makeMedia() {
    QString id = newId();
    QDate date;
    return new Media(id,"", date, date,"", "","",image );
}

Note& NoteManager::getNote( QString id) {

    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ((*ite2)->getId() == id) return **ite2;
        }
    }
    throw NotesException("la note n'existe pas");
}

Note& NoteManager::getNoteActuelle( QString  id) { //rechercher la version active de la note correspondant à l'id
    // 1) rechercher le vector dans lequel se trouve la note correspondant à l'id en argument
    int position = -1;
    QVector<Note*> v;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ((*ite2)->getId() == id) {
                position = 0;
                v = *ite;
                break;
            }
        } if (position == 0) break;
    }
    // 2) trouver quelle est la note active dans ce vector
    for (QVector<Note*>::iterator ite = v.begin(); ite != v.end(); ++ite) {
        if ((*ite)->isActive() == true) return **ite;
    }
    throw NotesException("Aucune version active trouvee pour cette note.");
}

void NoteManager::restaurerNote( QString  id) {
        Note* oldNote = &getNote(id);
//test pour vérifier que la note à restaurer n'est pas active. Si elle est déjà active, ne rien faire.
        if (oldNote->isActive()==false && oldNote->inCorbeille()==true) {
            try { // si une version active existe déjà alors il faut l'archiver avant de réactiver l'autre note
                Note* activeNote = &getNoteActuelle(id);
                activeNote->archiver();
                oldNote->restaurer();
            }
            catch (NotesException e) { //si aucune version active n'existe pour cette note alors on se contente de réactiver la note
                oldNote->restaurer();
            }
        }
}

void NoteManager::supprimerNoteActuelle( QString  id) {
    QVector<Note*> v;
    Note * oldNote;
    int position = -1;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ( (*ite2)->getId() == id && (*ite2)->isActive() )  { //tester si la note actuelle est dans une relation référence. si oui alors archiver
                oldNote = (*ite2); //mémorisation de la note supprimée afin de ne pas la restaurer accidentellement dans la deuxième partie de la fonction
                (*ite2)->archiver(); //passer en archive (active=false) la note active
                v = *ite; //v est le vecteur dans lequel est rangée la note
                break;
            }
            if ((*ite2)->getId() == id && (*ite2)->isActive()) { //si la note n'est pas référencée alors la jeter dans la corbeille
                (*ite2)->jeter();
                v = *ite;
                break;
            }
        }
        if (position != -1) break;
    }
    //trouver la version à restaurer : tri sur la date de dernière modification la plus récente
    QDate date = v[0]->getDateM();
    Note * note = NULL;
    for (int i = 0; i < v.size(); i++) {
            if ( date<v[i]->getDateM() && oldNote->getId()!= v[i]->getId() ) {
                date = v[i]->getDateM();
                note = v[i];
            }
        }
    note->restaurer();
}

void NoteManager::supprimerVersions(const QString  id) {
//Mettre dans la corbeille ou en archive toutes les versions de la note active passée en argument
    QVector<Note*> v;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if  ((*ite2)->getId() == id) {
                v = *ite;
                return;
            }
        }
    }

    for (int i = 0; i < v.size(); i++) {
        //test pour savoir s'il existe une référence sur la note à faire
        if(RelationManager::getInstance().noteReference(*(v[i]),"reference")==true){
            v[i]->archiver(); //si oui alors archiver la note
        }
        else {
            v[i]->jeter(); //si non alors placer la note dans la corbeille
        }
    }
}

void NoteManager::viderCorbeille() {
//Parcours de la structure versions. Pour chaque note rencontrée où corbeille vaut true, on l'efface de versions.
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ((*ite2)->inCorbeille())
                (*ite).erase(ite2);
        }
    }
}

void NoteManager::save(Note* n, QString rep) const {
    qDebug()<<"test4";
    Article * a = dynamic_cast<Article*>(n);
    if  ( a!=nullptr) //test pour savoir si c'est une tache
    {
        qDebug()<<"test5";
        a->saveNote(rep);
        qDebug()<<"test13";
     }
}

void NoteManager::saveAll() const{
    /* QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for (auto ite = versions.begin(); ite != versions.end(); ++ite) {
        for (auto ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2)
        {
        stream.writeStartElement("note");
        stream.writeTextElement("id",(*ite2)->getId());
        stream.writeTextElement("titre",(*ite2)->getTitre());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
    }*/
}

QList<Note*> NoteManager::getActiveNotes(){
    QList<Note*> result;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if  ((*ite2)->isActive()==true)
                result.push_back((*ite2));
        }
    }
    return result;
}

QList<Note*> NoteManager::getArchiveNotes(){
    QList<Note*> result;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if  ((*ite2)->isActive()==false)
                result.push_back((*ite2));
        }
    }
    return result;
}

QList<Tache*> NoteManager::getSortedTasks(){
    QList<Tache*> result;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            Tache * tache = dynamic_cast<Tache*>(*ite2);
            if  ( tache!=nullptr) //test pour savoir si c'est une tache
                result.push_back(tache);
        }
     }
    //tri de la liste result (liste de taches) selon la priorité
    qSort(result);
    return result;
}
