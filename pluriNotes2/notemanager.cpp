#include "notemanager.h"
#include "plurinotes.h"

#include <QFile>
#include<QDate>
#include<QString>
#include<QIODevice>

using namespace std;

NoteManager* NoteManager::instance = NULL;

/*------------------------------------------------------Constructeurs, opérateur de recopie et d'affectation et destructeur-------------------------------------------------------*/

NoteManager::NoteManager() : versions(0), id("0") {

   //le repertoire courant sera le repertoire de l'exécutable
   QString repertoire= QDir::currentPath();
   qDebug()<<repertoire;
   directory=repertoire;
   qDebug()<<"Test1";

   // si un fichier contenant le dernier id existe, alors le télécharger. sinon id vaut juste "0".
   QFile idfile("id");
   if(idfile.open(QIODevice::ReadWrite)){
      QString line=idfile.readLine();
      id = line;
      idfile.close();
   }
   //si des notes ont été sauvegardées sur fichier, on les recréer et on les range dans le vecteur
   // (mais il ne récupèrera d'une session à l'autre que les notes actives)
    QStringList filter;
    filter<<"*.xml";
   QFileInfoList noteList = directory.entryInfoList(filter,QDir::Files);
   qDebug()<<"Liste ?";
   for (auto ite=noteList.begin(); ite!=noteList.end(); ++ite){
       qDebug()<<"sdqhdf";
       QString name = (*ite).fileName();
       QFile file(name);
       qDebug()<<name;
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           throw NotesException("Erreur ouverture fichier notes");
       }
       QXmlStreamReader xml(&file);
       while(!xml.atEnd() && !xml.hasError()) {
           QXmlStreamReader::TokenType token = xml.readNext();
           if(token == QXmlStreamReader::StartDocument) continue;
           if(token == QXmlStreamReader::StartElement) {
               if(xml.name() == "notes") continue;
               if(xml.name() == "Article") {
                   QString identificateur;
                   QString titre;
                   QString text;
                   QXmlStreamAttributes attributes = xml.attributes();
                   xml.readNext();
                   while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                       if(xml.tokenType() == QXmlStreamReader::StartElement) {

                           if(xml.name() == "id") {
                               xml.readNext(); identificateur=xml.text().toString();
                           }

                           if(xml.name() == "titre") {
                               xml.readNext(); titre=xml.text().toString();
                           }

                           if(xml.name() == "text") {
                               xml.readNext();
                               text=xml.text().toString();
                           }
                       }

                       xml.readNext();
                   }
                   // 3) Génération de l'objet à partir du fichier xml
                   Article* a=makeArticle();
                   setNoteId(a,identificateur); //corriger l'incrémentation de l'id réalisée par le makeArticle
                   a->setFilename(titre);
                   a->setText(text);
                   a->setTitre(titre);
                   pushToVersions(a);
               }

               if(xml.name() == "Tache") {
                   qDebug()<<"new tache\n";
                   QString identificateur;
                   QString titre;
                   QString action;
                   QString echeance;
                   QString etat;
                   QString priorite;
                   QXmlStreamAttributes attributes = xml.attributes();
                   xml.readNext();
                   while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Tache")) {
                       if(xml.tokenType() == QXmlStreamReader::StartElement) {
                           if(xml.name() == "id") {
                               xml.readNext();
                               identificateur=xml.text().toString();
                               qDebug()<<"id="<<identificateur<<"\n";
                           }

                           if(xml.name() == "titre") {
                               xml.readNext();
                               titre=xml.text().toString();
                               qDebug()<<"titre="<<titre<<"\n";
                           }

                           if(xml.name() == "action") {
                               xml.readNext();
                               action=xml.text().toString();
                               qDebug()<<"action="<<action<<"\n";
                           }
                           if(xml.name() == "echeance") {
                               xml.readNext();
                               echeance=xml.text().toString();
                               qDebug()<<"echeance="<<echeance<<"\n";
                           }
                           if(xml.name() == "etat") {
                               xml.readNext();
                               etat=xml.text().toString();
                               qDebug()<<"etat="<<etat<<"\n";
                           }
                           if(xml.name() == "priorite") {
                               xml.readNext();
                               priorite=xml.text().toString();
                               qDebug()<<"priorite="<<priorite<<"\n";
                           }

                           qDebug()<<"HEY10";
                       }
                       // ...and next...
                       xml.readNext();
                       qDebug()<<"HEY11";
                   }
                   qDebug()<<"ajout note "<<identificateur<<"\n";
                   Tache* t=makeTache();
                   Statut e;
                   if (etat=="En attente")
                       e=En_attente;
                   if (etat=="En cours")
                       e=En_cours;
                   if (etat=="Terminee")
                       e=Terminee;
                   QDate DateE = QDate::fromString(echeance,"dd/MM/yyyy");
                   qDebug()<<DateE;
                   unsigned int p= priorite.toInt();

                   t->setFilename(titre);
                   qDebug()<<t->filename;
                   t->setTitre(titre);
                   t->setAction(action);
                   qDebug()<<t->action;
                   t->setEtat(e);
                   qDebug()<<t->etat;
                   t->setEcheance(DateE);
                   qDebug()<<t->echeance;
                   t->setPriorite(p);
                   qDebug()<<t->priorite;
                   pushToVersions(t);
               }
               if(xml.name() == "Media") {
                   qDebug()<<"new media\n";
                   QString identificateur;
                   QString titre;
                   QString description;
                   QString chemin;
                   QXmlStreamAttributes attributes = xml.attributes();
                   xml.readNext();
                   while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Media")) {
                       if(xml.tokenType() == QXmlStreamReader::StartElement) {
                           if(xml.name() == "id") {
                               xml.readNext(); identificateur=xml.text().toString();
                               qDebug()<<"id="<<identificateur<<"\n";
                           }

                           if(xml.name() == "titre") {
                               xml.readNext(); titre=xml.text().toString();
                               qDebug()<<"titre="<<titre<<"\n";
                           }

                           if(xml.name() == "description") {
                               xml.readNext();
                               description=xml.text().toString();
                               qDebug()<<"description="<<description<<"\n";
                           }
                           if(xml.name() == "Chemin") {
                               xml.readNext();
                               chemin=xml.text().toString();
                               qDebug()<<"chemin="<<chemin<<"\n";
                           }
                           qDebug()<<"HEY10";
                       }
                       xml.readNext();
                       qDebug()<<"HEY11";
                   }
                   qDebug()<<"ajout note "<<identificateur<<"\n";
                   Media* med=makeMedia();
                   med->setFilename(titre);
                   med->setTitre(titre);
                   med->setDescription(description);
                   med->setChemin(chemin);
                   pushToVersions(med);
               }
           }
       }
       if(xml.hasError()) {
           throw NotesException("Erreur lecteur fichier notes, parser xml");
       }
       xml.clear();
   }

}

/**
 * \details Lors de l'appel du destructeur, on appel la fonction save qui permet de sauvegarder le texte des notes sur un fichier en mémoire.
 * On appel également la méthode clear sur le tableau de versions permettant de vider le tableau, les destructeurs appelés libèrent la mémoire automatiquement.
 */
NoteManager::~NoteManager() {
	//sauvegarder dans un fichier le dernier id utilisé pour le remettre à jour (créer si 'louverture échoue)
    saveAll(); //fonction qui sauve le texte des Notes sur un fichier en mémoire
    versions.clear(); // destruction des vecteurs internes. les destructeurs appelés libèrent la mémoire automatiquement
}

/*------------------------------------------------------Gestion de l'identiication des versions-------------------------------------------------------*/

QString NoteManager::newId() {
    unsigned int temp = id.toInt();
    temp+=1;
    id=QString::number(temp);
    QFile idfile("id");
    if(idfile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)){
    QTextStream stream(&idfile);
            stream<<id<<endl;
            idfile.close();

    }

    return id;
}

/*------------------------------------------------------Accesseurs en lecture-------------------------------------------------------*/

NoteManager& NoteManager::getInstance() {
    if (!instance) {
        //Création de l'instance unique si ce n'est pas encore fait. Seules les méthodes membres de NoteManager accèdent à son constructeur.
        instance = new NoteManager;
    }
    return *instance;
}

Note* NoteManager::getNote( QString id) {

    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ((*ite2)->getId() == id) return *ite2;
        }
    }
    throw NotesException("la note n'existe pas");
}

/**
 * \details Permet de récupérer une référence vers la version active de la note correspondant à l'identificateur.
 * On cherche alors le vector dans lequel se trouve la note correspondante.
 * Puis on cherche quelle est la note active dans ce vector.
 */
Note& NoteManager::getNoteActuelle( QString  id) {
    //Rechercher le vector dans lequel se trouve la note correspondant à l'id en argument
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
    //Trouver quelle est la note active dans ce vector
    for (QVector<Note*>::iterator ite = v.begin(); ite != v.end(); ++ite) {
        if ((*ite)->isActive() == true) return **ite;
    }
    throw NotesException("Aucune version active trouvee pour cette note.");
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
            if  ( tache!=nullptr) //Test pour savoir si c'est une tache
                result.push_back(tache);
        }
     }
    //Tri de la liste result (liste de taches) selon la priorité
    qSort(result);
    return result;
}

QVector<Note*> NoteManager::getVector(QString id){ //renvoie le vector où se trouve la note
    int position = -1;
    QVector<Note*> v;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ((*ite2)->getId() == id) {
                position = 0;
                v = *ite;
                break;
            }
        }
    }
    return v;
}

/*------------------------------------------------------Méthodes-------------------------------------------------------*/

Article* NoteManager::makeArticle() {
    QString id = newId();
    qDebug()<<"Entree1";
    QDate date = QDate::currentDate();
    qDebug()<<"Entree3";
    Article* a= new Article(id,"","",date,date,"");
    return a;
    //
}

Tache* NoteManager::makeTache() {
    QString id = newId();
    QDate date = QDate::currentDate();
    return new Tache(id,"","",date,date,"",0,date,En_cours);
}

Media* NoteManager::makeMedia() {
    QString id = newId();
    QDate date = QDate::currentDate();
    return new Media(id,"", "",date, date,"", "","",image);
}

/**
 * \details On teste que la note à restaurer ne soit pas active. Si elle est déjà active on ne fait rien.
 * Si elle n'est pas active, on teste s'il en existe déjà une version active. Si oui, il faut d'abord archiver
 * la version active avant de restaurer notre note.
 */
void NoteManager::restaurerNote( QString  id) {
        Note* oldNote = getNote(id);
		//Test pour vérifier que la note à restaurer n'est pas active. Si elle est déjà active, ne rien faire.
        if (oldNote->isActive()==false && oldNote->inCorbeille()==true) {
            try { //Si une version active existe déjà alors il faut l'archiver avant de réactiver l'autre note
                Note* activeNote = &getNoteActuelle(id);
                activeNote->archiver();
                oldNote->restaurer();
            }
            catch (NotesException e) { //Si aucune version active n'existe pour cette note alors on se contente de réactiver la note
                oldNote->restaurer();
            }
        }
}

/**
 * \details On met dans la corbeille ou on archive la note active actuelle passée en argument.
 * S'il existe une référence sur la note, on l'archive, sinon on la met dans la corbeille.
 * Ensuite on restaure la version la plus récente.
 */
void NoteManager::supprimerNoteActuelle( QString  id) {
    QVector<Note*> v;
    Note * oldNote;
    int position = -1;
    for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            if ( (*ite2)->getId() == id && (*ite2)->isActive() )  { //tester si la note actuelle est dans une relation référence. si oui alors archiver
                oldNote = (*ite2); //Mémorisation de la note supprimée afin de ne pas la restaurer accidentellement dans la deuxième partie de la fonction
                (*ite2)->archiver(); //Passer en archive (active=false) la note active
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
    //Trouver la version à restaurer : tri sur la date de dernière modification la plus récente
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

/**
 * \details On met dans la corbeille ou on archive toutes les versions de la note active passée en argument.
 * S'il existe une référence sur une note, on l'archive, sinon on la met dans la corbeille.
 */
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
        //Test pour savoir s'il existe une référence sur la note à faire
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
    Tache * t = dynamic_cast<Tache*>(n);
    if  ( t!=nullptr) //test pour savoir si c'est une tache
    {
        qDebug()<<"test5";
        t->saveNote(rep);
        qDebug()<<"test13";
     }
    Media * m = dynamic_cast<Media*>(n);
    if  ( m!=nullptr) //test pour savoir si c'est une tache
    {
        qDebug()<<"test5";
        m->saveNote(rep);
        qDebug()<<"test13";
     }
}

void NoteManager::pushToVersions(Note* note){
    QVector<Note*> NewNote;
    NewNote.push_back(note);
    versions.push_back(NewNote);
}
