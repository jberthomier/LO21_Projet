#include "noteediteur.h"
#include "notemanager.h"

QVector<NoteEditeur*> NoteEditeur::editeurs= {};


NoteEditeur::NoteEditeur(Note* n,QWidget *parent) :
    QWidget(parent),
    note(n)
 {
    id = new QLineEdit();
    titre = new QLineEdit();

    save = new QPushButton("Sauvegarder");
    id1 = new QLabel("Identificateur");
    titre1 = new QLabel("Titre");
    layout = new QHBoxLayout;
    cid = new QHBoxLayout;
    ctitre = new QHBoxLayout;
    couche = new QVBoxLayout;

    cid->addWidget(id1);
    cid->addWidget(id);
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);


    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(layout);
    couche->addWidget(save);

    id->setText(n->getId());
    titre->setText(n->getTitre());


    this->setLayout(couche);
    //Initialement désactivé
    save->setEnabled(false);

    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveNote()));
    QObject::connect(titre,SIGNAL(textChanged(QString)),this,SLOT(activeSave()));
    editeurs.push_back(this);

}


NoteEditeur::~NoteEditeur()
{
    editeurs.remove(editeurs.indexOf(this));
}


void NoteEditeur::saveNote() {
    //Maj de l'objet article
    //qDebug()<<"Test4";
    note->setTitre(titre->text());
    //qDebug()<<"Test5";
    //note->setTexte(text->toPlainText());
    //Sauvegarde dans le fichier xml
    NoteManager::getInstance().save(note);
    qDebug()<<"Test6";
    //Affichage d'un popup d'information
    QMessageBox::information(this,"Sauvegarde","Votre article a bien été sauvegardé");
    qDebug()<<"Test7";
    //Le bouton de sauvegarde est grisé
    save->setEnabled(false);
    qDebug()<<"Test8";
    emit Editionfinished(this);
    qDebug()<<"Test9";
}

void NoteEditeur::activeSave(){
    save->setEnabled(true);
    emit Editing(this);
}

void NoteEditeur::verification(){

}
