#include "PluriNotes.h"
#include <qDebug>
#include <QList>
#include <QTabWidget>

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    centralLayout = new QHBoxLayout;


    QObject::connect(ui.actionArticle, SIGNAL(triggered()), this, SLOT(newArticle()));
    QObject::connect(ui.actionTache, SIGNAL(triggered()), this, SLOT(newTache()));
    QObject::connect(ui.actionMedia, SIGNAL(triggered()), this, SLOT(newMedia()));
    QObject::connect(ui.actionOuvrir, SIGNAL(triggered()), this, SLOT(load()));
    QObject::connect(ui.Update, SIGNAL(clicked(bool)), this, SLOT(updateActiveNotes()));
    QObject::connect(ui.Update, SIGNAL(clicked(bool)), this, SLOT(updateArchiveNotes()));
    QObject::connect(ui.Update, SIGNAL(clicked(bool)), this, SLOT(updateSortedTasks()));
    
    QObject::connect(ui.noteList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ouvrirNote(QListWidgetItem*)));
    QObject::connect(ui.archiveList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ouvrirNote(QListWidgetItem*)));
    QObject::connect(ui.taskList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ouvrirNote(QListWidgetItem*)));

    QObject::connect(ui.actionNouvelleRelation, SIGNAL(triggered()), this, SLOT(CreationRelation()));
    QObject::connect(ui.actionParcoursRelation, SIGNAL(triggered()), this, SLOT(ParcoursRelation()));
    QObject::connect(ui.actionVisualisationRelations, SIGNAL(triggered()), this, SLOT(VisualisationRelation()));

    updateActiveNotes(); //création de la liste des notes actives
    updateArchiveNotes(); //création de la liste des notes archivées
    updateSortedTasks(); //création de la liste des taches triées par priorité


}


PluriNotes::~PluriNotes()
{
    //delete ui;
}

void PluriNotes::newArticle()
{

        NoteManager& m = NoteManager::getInstance();
        Article* a= m.makeArticle();
         qDebug()<<"Entree4";
        AffichageNote* viewer = new AffichageNote;
         qDebug()<<"Entree5";
        viewer->afficheArticle(a);
         qDebug()<<"Entree6";
        viewer->show();
        qDebug()<<"Entree6-1";
        /*this->updateActiveNotes();
        qDebug()<<"Test1";
        this->updateArchiveNotes();
        qDebug()<<"Test2";
        this->updateSortedTasks();
        qDebug()<<"Test3";*/
}

void PluriNotes::newTache()
{
        NoteManager& m = NoteManager::getInstance();

        Tache* t= m.makeTache();
        AffichageNote* viewer = new AffichageNote();
         qDebug()<<"Entree5";
        viewer->afficheTache(t);
         qDebug()<<"Entree6";
        viewer->show();
}

void PluriNotes::newMedia()
{
        NoteManager& m = NoteManager::getInstance();

        Media* med= m.makeMedia();
        AffichageNote* viewer = new AffichageNote();
         qDebug()<<"Entree5";
        viewer->afficheMedia(med);
         qDebug()<<"Entree6";
        viewer->show();
}

void PluriNotes::getChemin (QListWidgetItem* id) {
    NoteManager& m = NoteManager::getInstance();
    Note* n=m.getNote(id->text());
    qDebug()<<"Ouverture note"<<id->text();
    AffichageNote* viewer = new AffichageNote();
    viewer->afficheNote(n);
    viewer->show();
}

void PluriNotes::updateActiveNotes(){
    QList<Note*> notes = NoteManager::getInstance().getActiveNotes();
    ui.noteList->clear();
    for(auto ite = notes.begin(); ite != notes.end(); ++ite) {
        ui.noteList->addItem((*ite)->getId());
    }
}
void PluriNotes::updateArchiveNotes(){
    QList<Note*> notes = NoteManager::getInstance().getArchiveNotes();
    ui.archiveList->clear();
    for(auto ite = notes.begin(); ite != notes.end(); ++ite) {
        ui.archiveList->addItem((*ite)->getId());
    }
}

void PluriNotes::updateSortedTasks(){ //veut-on aussi afficher la date et la priorité avec la tache ?
    QList<Tache*> notes = NoteManager::getInstance().getSortedTasks();
    ui.taskList->clear();
    for(auto ite = notes.begin(); ite != notes.end(); ++ite) {
        ui.taskList->addItem((*ite)->getId());
     }
}


void PluriNotes::ouvrirNote(QListWidgetItem* id) {
    NoteManager& m = NoteManager::getInstance();
    Note* n=m.getNote(id->text());
    qDebug()<<"Ouverture note"<<id->text();
    AffichageNote* viewer = new AffichageNote();
    viewer->afficheNote(n);
    viewer->show();
}


void PluriNotes::load() {
    qDebug()<<"HEY";
    NoteManager& m = NoteManager::getInstance();
    QString fichier = QFileDialog::getOpenFileName();
    qDebug()<<"HEY1";
    m.setFilename(fichier);
    qDebug()<<"HEY1-1";
    QFile fin(fichier);
    qDebug()<<"HEY2";
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    qDebug()<<"HEY3";
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        qDebug()<<"HEY4";
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        qDebug()<<"HEY5";
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        qDebug()<<"HEY6";
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            qDebug()<<"HEY7";
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            qDebug()<<"HEY8";
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "Article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                        qDebug()<<"HEY10";
                    }
                    // ...and next...
                    xml.readNext();
                    qDebug()<<"HEY11";
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                Article* a=m.makeArticle();
                m.setFilename(titre);
                m.setArticleText(a,text);
                m.setNoteTitle(a,titre);
                AffichageNote* viewer = new AffichageNote;
                viewer->afficheArticle(a);
                viewer->show();

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
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
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
                Tache* t=m.makeTache();
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
                qDebug()<<t->getFilename();
                t->setTitre(titre);
                t->setAction(action);
                qDebug()<<t->action;
                t->setEtat(e);
                qDebug()<<t->etat;
                t->setEcheance(DateE);
                qDebug()<<t->echeance;
                t->setPriorite(p);
                qDebug()<<t->priorite;
                AffichageNote* viewer = new AffichageNote;
                viewer->afficheTache(t);
                viewer->show();

            }
            if(xml.name() == "Media") {
                qDebug()<<"new media\n";
                QString identificateur;
                QString titre;
                QString description;
                QString chemin;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Media")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
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
                    // ...and next...
                    xml.readNext();
                    qDebug()<<"HEY11";
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                Media* med=m.makeMedia();
                m.setFilename(titre);
                m.setNoteTitle(med,titre);
                m.setMediaDescription(description, med);
                m.setMediaPath(chemin,med);
                AffichageNote* viewer = new AffichageNote;
                viewer->afficheMedia(med);
                viewer->show();

            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}

void PluriNotes::CreationRelation(){
    RelationEditeur* window = new RelationEditeur;
    window->show();
}

void PluriNotes::ParcoursRelation(){
    qDebug()<<"Youhou1-1 ?";
    window_exploration = new ExplorationRelations();
    qDebug()<<"Youhou1-2 ?";
    QObject::connect(window_exploration->getListe(), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(OuvrirRelation()));
    qDebug()<<"Youhou1- 3 ?";
   window_exploration->show();
}

void PluriNotes::OuvrirRelation(){
    qDebug()<<"Youhou1-4 ?";
    if(window_exploration->getListe()->currentRow() != -1){
        qDebug()<<"Youhou1-5 ?";
        QString titre_rela = window_exploration->getListe()->currentItem()->text();

        RelationManager& rm = RelationManager::getInstance();
        qDebug()<<"Youhou1-6 ?";
        window_relation = new RelationEditeur(&rm.getRelation(titre_rela));

        QObject::connect(window_relation->getButtonCreate(), SIGNAL(clicked(bool)), this, SLOT(OuvertureCouple()));

        QObject::connect(window_relation->getButtonClose(), SIGNAL(clicked(bool)), this, SLOT(ParcoursRelation()));

        qDebug()<<"Youhou1-7 ?";
        window_relation->show();
    }
}

void PluriNotes::OuvertureCouple(){
    qDebug()<<"Youhou1-8 ?";
    if(window_exploration->getListe()->currentRow() != -1){
        qDebug()<<"Youhou1-9 ?";
        RelationManager& rm = RelationManager::getInstance();

        Relation* r = &rm.getRelation( window_relation->getTitre()->text() );
        qDebug()<<"Youhou1-10 ?";
        window_couple = new FenetreCouple(r);
        connect(window_couple->getButtonCreate(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_arbo()));
        window_couple->show();
        qDebug()<<"Youhou1-11 ?";
    }


}

void PluriNotes::VisualisationRelation(){


    VoirRelations* window_voir = new VoirRelations();
    qDebug()<<"Youhou ?";
    connect(window_voir->getButtonDeletion(), SIGNAL(clicked(bool)), this, SLOT(ouvrir_arbo()));
    qDebug()<<"Youhou1 ?";
    window_voir->show();
    qDebug()<<"Youhou2 ?";

}

void PluriNotes::ouvre_note_asc() {
    if(arbo->getAscendants()->currentColumn() != -1){

        NoteManager& m = NoteManager::getInstance();

        Note* note = m.getNote( arbo->getAscendants()->currentItem()->text(0) );

        AffichageNote* viewer = new AffichageNote;

        if(note->getType()=="article"){
            Article* a=dynamic_cast<Article*>(note);
            viewer->afficheArticle(a);
           }
        else if(note->getType()=="tache"){
            Tache* t=dynamic_cast<Tache*>(note);
            viewer->afficheTache(t);
        }
        else{
            Media* med=dynamic_cast<Media*>(note);
            viewer->afficheMedia(med);
        }

       viewer->show();
       ouvrir_arbo();
    }

}

void PluriNotes::ouvre_note_desc() {
    if(arbo->getDescendants()->currentColumn() != -1){

        NoteManager& m = NoteManager::getInstance();

        Note* note = m.getNote( arbo->getDescendants()->currentItem()->text(0) );


        AffichageNote* viewer = new AffichageNote;

        if(note->getType()=="article"){
            Article* a=dynamic_cast<Article*>(note);
            viewer->afficheArticle(a);
           }
        else if(note->getType()=="tache"){
            Tache* t=dynamic_cast<Tache*>(note);
            viewer->afficheTache(t);
        }
        else{
            Media* med=dynamic_cast<Media*>(note);
            viewer->afficheMedia(med);
        }

       viewer->show();
        ouvrir_arbo();
    }

}

void PluriNotes::ouvrir_arbo(){
    if(arbo && arbo->getButtonAsc()->hasFocus() && arbo->getAscendants()->currentColumn() != -1 ){
        NoteManager& m = NoteManager::getInstance();

        Note* note = m.getNote( arbo->getAscendants()->currentItem()->text(0) );
        arbo->close();
        arbo = new Arborescence(*note, this);
        connect(arbo->getButtonAsc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_asc()));
        connect(arbo->getButtonDesc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_desc()));
        arbo->show();

    }
    else if (arbo && arbo->getButtonDesc()->hasFocus() && arbo->getDescendants()->currentColumn() != -1 ){
        NoteManager& m = NoteManager::getInstance();

        Note* note = m.getNote( arbo->getDescendants()->currentItem()->text(0) );
        arbo->close();
        arbo = new Arborescence(*note, this);
        connect(arbo->getButtonAsc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_asc()));
        connect(arbo->getButtonDesc(), SIGNAL(clicked(bool)), this, SLOT(ouvre_note_desc()));
        arbo->show();


    }
    else{
        if(arbo) arbo->close();

}
}
