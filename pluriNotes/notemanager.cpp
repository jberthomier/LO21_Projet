#include "notemanager.h"
#include <QFile>

using namespace std;

NoteManager* NoteManager::instance = NULL;

/*------------------------------------------------------Constructeurs, opérateur de recopie et d'affectation et destructeur-------------------------------------------------------*/

NoteManager::NoteManager() : versions(0), id(0) {}

/**
 * \details Lors de l'appel du destructeur, on appel la fonction save qui permet de sauvegarder le texte des notes sur un fichier en mémoire.
 * On appel également la méthode clear sur le tableau de versions permettant de vider le tableau, les destructeurs appelés libèrent la mémoire automatiquement.
 */
NoteManager::~NoteManager() {
    save();
    versions.clear();
}

/*------------------------------------------------------Gestion de l'identificateur des versions-------------------------------------------------------*/

/**
 * \details Pour générer un nouvel id, on l'incrémente
 */
unsigned int NoteManager::newId() {
    return id++;
}

/*------------------------------------------------------Accesseurs en lecture-------------------------------------------------------*/

Note& NoteManager::getNote(QString id) {

    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ((*ite2)->getId() == id) return **ite2;
        }
    }
    throw NoteException("la note n'existe pas");
}

/**
 * \details Permet de récupérer une référence vers la version active de la note correspondant à l'identificateur.
 * On cherche alors le vector dans lequel se trouve la note correspondante.
 * Puis on cherche quelle est la note active dans ce vector.
 */
Note& NoteManager::getNoteActuelle(QString id) {
    //Recherche du vector dans lequel se trouve la note correspondant à l'id en argument
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
    //Détermination de la note active dans ce vector
    for (QVector<Note*>::iterator ite = v.begin(); ite != v.end(); ++ite) {
        if ((*ite)->isActive() == true) return **ite;
    }
    throw NoteException("Aucune version active trouvee pour cette note.");
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

/*------------------------------------------------------Méthodes-------------------------------------------------------*/

NoteManager& NoteManager::getInstance() {
    if (!instance) {
        //Création de l'instance unique si ce n'est pas encore fait. Seules les méthodes membres de NoteManager accèdent à son constructeur.
        instance = new NoteManager;
    }
    return *instance;
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

/**
 * \details On teste que la note à restaurer ne soit pas active. Si elle est déjà active on ne fait rien.
 * Si elle n'est pas active, on teste s'il en existe déjà une version active. Si oui, il faut d'abord archiver
 * la version active avant de restaurer notre note.
 */
void NoteManager::restaurerNote(QString id) {
        Note* oldNote = &getNote(id);
        if (oldNote->isActive()==false) { //Test pour vérifier que la note à restaurer n'est pas active. Si elle est déjà active, ne rien faire.
            try { //Si une version active existe déjà alors il faut l'archiver avant de réactiver l'autre note
                Note* activeNote = &getNoteActuelle(id);
                activeNote->archiver();
                oldNote->restaurer();
            }
            catch (NoteException e) { //Si aucune version active n'existe pour cette note alors on se contente de réactiver la note
                oldNote->restaurer();
            }
        }
}

/**
 * \details On met dans la corbeille ou on archive la note active actuelle passée en argument.
 * S'il existe une référence sur la note, on l'archive, sinon on la met dans la corbeille.
 * Ensuite on restaure la version la plus récente.
 */
void NoteManager::supprimerNoteActuelle(QString id) {
    QVector<Note*> v;
    Note* oldNote;
    int position = -1;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ( (*ite2)->getId() == id && (*ite2)->isActive() )  { //Tester si la note actuelle est dans une relation référence
                oldNote = (*ite2); //Mémorisation de la note supprimée afin de ne pas la restaurer accidentellement dans la deuxième partie de la fonction
                (*ite2)->archiver(); //Passer en archive (active=false) la note active
                v = *ite;
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
    //Trouver la version à restaurer : tri sur la date de dernière modification la plus récente
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

/**
 * \details On met dans la corbeille ou on archive toutes les versions de la note active passée en argument.
 * S'il existe une référence sur une note, on l'archive, sinon on la met dans la corbeille.
 */
void NoteManager::supprimerVersions(QString id) {
    QVector<Note*> v;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if  ((*ite2)->getId() == id) {
                v = *ite;
                return;
            }
        }
    }
    for (int i = 0; i < v.size(); i++) { //Test pour savoir s'il existe une référence sur la version de la note à supprimer
        if(RelationManager::getInstance().noteReference(*(v[i]),"reference")==true){
            v[i]->archiver(); //Si oui alors archiver la note
        }
        else {
            v[i]->jeter(); //Si non alors placer la note dans la corbeille
        }
    }
}

/**
 * \details On parcours le tableau de versions. Pour chaque note rencontrée où corbeille vaut true, on l'efface du tableau de versions.
 */
void NoteManager::viderCorbeille() { 
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
        throw NoteException(QString("erreur sauvegarde notes : ouverture fichier xml"));
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
