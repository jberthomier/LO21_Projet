#include "noteediteur.h"
#include "notemanager.h"

QVector<NoteEditeur*> NoteEditeur::editeurs= {};


NoteEditeur::NoteEditeur(Note* n,QWidget *parent) :
    QWidget(parent),
    note(n)
 {
    id = new QLineEdit();
    titre = new QLineEdit();
    text = new QTextEdit();
    save = new QPushButton("Sauvegarder");
    id1 = new QLabel("Identificateur");
    titre1 = new QLabel("Titre");
    text1 = new QLabel("Texte");
    cid = new QHBoxLayout;
    ctitre = new QHBoxLayout;
    ctext = new QHBoxLayout;
    couche = new QVBoxLayout;

    cid->addWidget(id1);
    cid->addWidget(id);
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);
    ctext->addWidget(text1);
    ctext->addWidget(text);

    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(ctext);
    couche->addWidget(save);

    id->setReadOnly(true);

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
    note->setTitre(titre->text());
    //note->setTexte(text->toPlainText());
    //Sauvegarde dans le fichier xml
    NoteManager::getInstance().save();
    //Affichage d'un popup d'information
    QMessageBox::information(this,"Sauvegarde","Votre article a bien été sauvegardé");
    //Le bouton de sauvegarde est grisé
    save->setEnabled(false);
    emit Editionfinished(this);
}

void NoteEditeur::activeSave(){
    save->setEnabled(true);
    emit Editing(this);
}

void NoteEditeur::verification(){

}
