#include "notemanager.h"
#include <QFile>
using namespace std;

NoteManager* NoteManager::instance = NULL;

unsigned int NoteManager::newId() {
    return id++;
}

NoteManager::NoteManager() : versions(0), id(0) {}

NoteManager::~NoteManager() {
    save(); //fonction qui sauve le texte des Notes sur un fichier en mémoire
    versions.clear(); // destruction des vecteurs internes. les destructeurs appelés libèrent la mémoire automatiquement
}

NoteManager& NoteManager::getInstance() {
    if (!instance) {
        //Création de l'instance unique si ce n'est pas encore fait. Seules les méthodes membres de NoteManager accèdent à son constructeur.
        instance = new NoteManager;
    }
    return *instance;
}

Note* NoteManager::makeNote() {
    int choice;
    QString id = newId();
    TIME::Date date;
    QString titre;
    bool ok = false;
    while (ok == false) {
        qtout<< "Quel type de note souhaitez-vous créer :" << endl << "1 : Article" << endl << "2 : Tache" << endl << "3 : Media" << endl;
        qtin>> choice;
        switch (choice) {
        case 1:
            qtout<< "Entrez le titre de votre note : ";
            qtin>> titre;
            qtout<< endl;
            return new Article(id, titre, date, date, "");
            ok = true;
            break;
        case 2:
            return new Tache();
            ok = true;
            break;
        case 3:
            return new Media();
            ok = true;
            break;
        default:
            qtout<< "Type invalide." << endl;
            break;
        }
    }
}

Article* NoteManager::makeArticle() {
    QString id = newId();
    TIME::Date date;
    return new Article(id,"",date,date,"");
}

Tache* NoteManager::makeTache() {
    QString id = newId();
    TIME::Date date;
    return new Tache(id,"",date,date,0,date,En_cours, "");
}

Media* NoteManager::makeMedia() {
    QString id = newId();
    TIME::Date date;
    return new Media(id,"", date, date, "","",image );
}

Note& NoteManager::getNote(const unsigned int id) {

    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ((*ite2)->getId() == id) return **ite2;
        }
    }
    throw NotesException("la note n'existe pas");
}

Note& NoteManager::getNoteActuelle(const unsigned int id) { //rechercher la version active de la note correspondant à l'id
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

void NoteManager::restaurerNote(const unsigned int id) {
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

void NoteManager::supprimerNoteActuelle(const unsigned int id) {
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
    TIME::Date date = v[0]->getDateM();
    Note * note = NULL;
    for (int i = 0; i < v.size(); i++) {
            if ( date<v[i]->getDateM() && oldNote->getId()!= v[i]->getId() ) {
                date = v[i]->getDateM();
                note = v[i];
            }
        }
    note->restaurer();
}

void NoteManager::supprimerVersions(const unsigned int id) {
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

void NoteManager::save() const {
/*    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2)
        {
        stream.writeStartElement("note");
        stream.writeTextElement("id",(*ite2).getId());
        stream.writeTextElement("titre",(*ite2).getTitre());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
    }*/
}

