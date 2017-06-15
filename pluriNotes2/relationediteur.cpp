#include "relationediteur.h"

RelationEditeur::RelationEditeur(QWidget* parent) : QWidget(parent)
{

    couche = new QVBoxLayout;
    crel = new QHBoxLayout;
    cdesc = new QHBoxLayout;
    buttons = new QHBoxLayout;

    rel1 = new QLabel("Nom de la relation");
    titre = new QLineEdit;

    crel->addWidget(rel1);
    crel->addWidget(titre);

    description1 = new QLabel("Description");
    description = new QTextEdit;

    cdesc->addWidget(description1);
    cdesc->addWidget(description);

    orientation = new QCheckBox("Non orientée");

    button_create = new QPushButton("Créer");
    button_close = new QPushButton("Fermer");

    QObject::connect(button_create,SIGNAL(clicked(bool)),this,SLOT(create()));
    QObject::connect(button_close,SIGNAL(clicked(bool)),this,SLOT(close()));

    buttons->addWidget(button_create);
    buttons->addWidget(button_close);
    buttons->addWidget(orientation);

    couche->addLayout(crel);
    couche->addLayout(cdesc);
    couche->addLayout(buttons);

    this->setLayout(couche);
}

RelationEditeur::~RelationEditeur(){}

RelationEditeur::RelationEditeur(Relation* r,QWidget* parent) : QWidget(parent)
{

    couche = new QVBoxLayout;
    crel = new QHBoxLayout;
    cdesc = new QHBoxLayout;
    buttons = new QHBoxLayout;

    rel1 = new QLabel("Nom de la relation");
    titre = new QLineEdit;
    titre->setText(r->getTitre());


    crel->addWidget(rel1);
    crel->addWidget(titre);

    description1 = new QLabel("Description");
    description = new QTextEdit;
    description->setText(r->getDescription());

    cdesc->addWidget(description1);
    cdesc->addWidget(description);

    orientation = new QCheckBox("Non orientée");
    orientation->setChecked(!r->getOri());
    orientation->setEnabled(false);

    button_create = new QPushButton("Créer");
    button_close = new QPushButton("Fermer");
    button_save = new QPushButton("Sauvegarder");
    //button_delete = new QPushButton("Supprimer");

    QObject::connect(button_create,SIGNAL(clicked(bool)),this,SLOT(create()));
    QObject::connect(button_close,SIGNAL(clicked(bool)),this,SLOT(close()));
    QObject::connect(button_save,SIGNAL(clicked(bool)),this,SLOT(save()));
    //QObject::connect(button_delete,SIGNAL(clicked(bool)),this,SLOT(deleteRelation()));

    buttons->addWidget(button_create);
    buttons->addWidget(button_close);
    buttons->addWidget(button_save);
    //buttons->addWidget(button_delete);
    buttons->addWidget(orientation);

    couche->addLayout(crel);
    couche->addLayout(cdesc);
    couche->addLayout(buttons);

    this->setLayout(couche);
}

void RelationEditeur::create(){
    if(this->titre->text() != "" && this->description->toPlainText() !=""){
        RelationManager& rm = RelationManager::getInstance();
        if(rm.existRelation(titre->text()))
            QMessageBox::information(this,"","Ce titre existe déjà !");
        else {
            Relation* r = new Relation(titre->text(),description->toPlainText());
            if(!orientation->isChecked())
                r->setOrientation(true);
            rm.addRelation(r);
        }
    }
    else
        QMessageBox::information(this,"","Champs vides à compléter !");
}

void RelationEditeur::save(){
    if(this->titre->text() != "" && this->description->toPlainText() !=""){
        RelationManager& rm = RelationManager::getInstance();
        if(rm.existRelation(titre->text()))
            QMessageBox::information(this,"","Ce titre existe déjà !");
        else {
            Relation& r = rm.getRelation(ancienTitre);
            r.setTitre(titre->text());
            r.setDescription(description->toPlainText());
            QMessageBox::information(this,"","Relation Sauvegardée");
        }
    }
    else
        QMessageBox::information(this,"","Champs vides à compléter !");
}

/*void RelationEditeur::deleteRelation(){
    RelationManager& rm = RelationManager::getInstance();
    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
            if ( widget->windowTitle() == "PluriNotes")
            {
                qDebug() << ancienTitre;
               qobject_cast<PluriNotes*>(widget)->deleteRelation(&(rm.getRelation(ancienTitre)));
               qDebug() << "lolol";
            }
     }
     QMessageBox::information(this,"","Sauvergarde Réussie");
}*/

ExplorationRelations::ExplorationRelations(QWidget *parent) :QWidget(parent) {

    couche = new QVBoxLayout;
    buttons= new QHBoxLayout;

    titre = new QLabel("Relations");

    RelationManager& rm= RelationManager::getInstance();

    liste = new QListWidget;

    for(RelationManager::Iterator it1 = rm.getIterator(); !it1.isdone();++it1) {
        if((*it1)->getTitre()!="Reference"){
            liste->addItem((*it1)->getTitre());
        }
    }

    button_close = new QPushButton("Fermer");
    QObject::connect(button_close,SIGNAL(clicked(bool)),this,SLOT(close()));

    buttons->addWidget(button_close);

    couche->addWidget(titre);
    couche->addWidget(liste);
    couche->addLayout(buttons);

    this->setLayout(couche);
}

FenetreCouple::FenetreCouple(Relation* r,QWidget *parent) : QWidget(parent) {
    couche = new QVBoxLayout;
    notes = new QHBoxLayout;
    buttons = new QHBoxLayout;

    titreR = new QLabel(r->getTitre());
    titreC = new QLabel("Label");
    couple = new QLineEdit;

    liste_x = new QListWidget;
    liste_y = new QListWidget;

    NoteManager& m = NoteManager::getInstance();

    QList<Note*> l = m.getActiveNotes();
    for(auto it = l.begin(); it!=l.end();++it) {
        if((*it)->active==true) {
            liste_x->addItem((*it)->getTitre());
            tab_id_x.append((*it)->getId());
            liste_y->addItem((*it)->getTitre());
            tab_id_y.append((*it)->getId());
        }
    }

    button_create = new QPushButton("Créer");

    QObject::connect(button_create,SIGNAL(clicked(bool)),this,SLOT(save()));

    buttons->addWidget(button_create);

    notes->addWidget(titreC);
    notes->addWidget(couple);

    couche->addWidget(titreR);
    couche->addLayout(notes);
    couche->addWidget(liste_x);
    couche->addWidget(liste_y);
    couche->addLayout(buttons);

    this->setLayout(couche);

}

void FenetreCouple::save() {
    if(this->liste_x->currentRow() !=-1 && this->liste_y->currentRow()!=-1){
        RelationManager& rm = RelationManager::getInstance();
        Relation& r = rm.getRelation(titreR->text());
        if(tab_id_x[liste_x->currentRow()]== tab_id_y[liste_x->currentRow()])
            QMessageBox::information(this,"","On ne peut pas créer de relations entre deux mêmes notes !");
        else {
           QString l;
           if(couple->text()=="") l = "default";
           else l = couple->text();
           NoteManager&m = NoteManager::getInstance();
           const Note* n1 = m.getNote(tab_id_x[liste_x->currentRow()]);
           const Note* n2 = m.getNote(tab_id_y[liste_y->currentRow()]);
           r.addCouple(*n1,*n2,l);
        }
    }
}

VoirRelations::VoirRelations(QWidget *parent) : QWidget(parent) {

    couche = new QVBoxLayout;
    notes = new QHBoxLayout;
    buttons = new QHBoxLayout;

    rel = new QComboBox;

    RelationManager& rm= RelationManager::getInstance();

    for(RelationManager::Iterator it1 = rm.getIterator(); !it1.isdone();++it1) {
        rel->addItem((*it1)->getTitre());
    }

    liste_couples = new QListWidget;

    Relation& r = rm.getRelation(rel->currentText());
    NoteManager& m = NoteManager::getInstance();

    for (Relation::Iterator it = r.getIterator() ; !it.isdone();++it) {
        QString n1 = (*it)->getNoteSource().getTitre();
        QString n2 = (*it)->getNoteDestination().getTitre();
        if(m.getNote(n1)->active==true && m.getNote(n2)->active==true) {
            liste_couples->addItem(n1+ "->"+n2);
        }
    }


    button_deletion = new QPushButton("Supprimer");
    button_deletion->setEnabled(false);
    button_close = new QPushButton("Fermer");

    QObject::connect(rel,SIGNAL(currentIndexChanged(int)),this,SLOT(activeDelete()));
    QObject::connect(liste_couples,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(CoupleEditer()));
    QObject::connect(rel,SIGNAL(activated(int)),this,SLOT(afficherCouples()));
    QObject::connect(button_deletion,SIGNAL(clicked(bool)),this,SLOT(SupprimerCouple()));
    QObject::connect(button_close,SIGNAL(clicked(bool)),this,SLOT(close()));

    buttons->addWidget(button_deletion);
    buttons->addWidget(button_close);

    couche->addWidget(rel);
    couche->addWidget(liste_couples);
    couche->addLayout(buttons);

    this->setLayout(couche);


}

void VoirRelations::activeDelete(){
    if (rel->currentText()=="Reference")
        button_deletion->setEnabled(false);
    else
        button_deletion->setEnabled(true);
}

void VoirRelations::afficherCouples(){
    RelationManager& rm = RelationManager::getInstance();

    liste_couples->clear();

    Relation& r = rm.getRelation(rel->currentText());
    NoteManager& m = NoteManager::getInstance();

    for( auto it = r.getIterator() ; !it.isdone() ; it++){
        QString n1 = (*it)->getNoteSource().getTitre();
        QString n2 = (*it)->getNoteDestination().getTitre();
        if(m.getNote(n1)->active==true && m.getNote(n2)->active==true ){
            liste_couples->addItem(n1+ "->"+n2);
        }
    }


}

void VoirRelations::afficherCouplesR(QString relation) {
    RelationManager& rm= RelationManager::getInstance();

    liste_couples->clear();

    Relation& r = rm.getRelation(relation);
    NoteManager& m = NoteManager::getInstance();

    int i = rel->findText(relation);
    if (i != -1) {
        qDebug()<<i;
        rel->setCurrentIndex(i);
    }

    for (auto it = r.getIterator(); !it.isdone(); ++it) {
        QString n1 = (*it)->getNoteSource().getTitre();
        QString n2 = (*it)->getNoteDestination().getTitre();
        if(m.getNote(n1)->active==true && m.getNote(n2)->active==true ) {
            liste_couples->addItem(n1+ "->"+n2);
        }
    }
}

void VoirRelations::CoupleEditer(){
    RelationManager& rm = RelationManager::getInstance();
    Relation& r = rm.getRelation(rel->currentText());

    QString label_depart;
    auto it= r.getIterator();

    for (int i=0; i<liste_couples->currentRow();++i)
        it++;

    if(label) {
        label->setText((*it)->getLabel());
    }
    else {
        notes = new QHBoxLayout;
        label1 = new QLabel("Label");
        save_label = new QPushButton("OK");
        label = new QLineEdit((*it)->getLabel());

        QObject::connect(save_label,SIGNAL(clicked(bool)),this,SLOT(saveLabel()));

        notes->addWidget(label);
        notes->addWidget(save_label);
        couche->addWidget(label1);
        couche->addLayout(notes);

    }
}

void VoirRelations::saveLabel(){
    if(this->label->text() !=""){
        RelationManager& rm = RelationManager::getInstance();
        Relation& r = rm.getRelation(rel->currentText());
        QStringList liste =  liste_couples->currentItem()->text().split(" -> ");

        Couple couples = r.getCouples(liste[0],liste[1]);

       couples.setLabel(label->text());

       QMessageBox::information(this,"","Modification Suavegardee");
      }
}

void VoirRelations::SupprimerCouple(){
    if(rel->currentText()=="Reference"){
        QMessageBox::information(this,"","Impossible de supprimer une référence");
    }
    else if (liste_couples->currentRow() != -1) {
        RelationManager& rm = RelationManager::getInstance();
        Relation& r  = rm.getRelation(rel->currentText());
        QStringList liste = liste_couples->currentItem()->text().split("->");
        Couple c= r.getCouples(liste[0],liste[1]);
        r.removeCouple(c);
        QMessageBox::information(this,"","Suppression Réussie !");
        if(label) {
            couche->removeWidget(label1);
            notes->removeWidget(label);
            notes->removeWidget(save_label);
            label->close();
            save_label->close();
            label1->close();
        }
    }
    else
        QMessageBox::information(this,"","Sélectionnez un couple");

}
