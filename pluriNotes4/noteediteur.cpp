#include "noteediteur.h"
#include "notemanager.h"
#include "QFileDialog"

/*------------------------------------------------------Méthodes publiques de la classe NoteEditeur-------------------------------------------------------*/

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
    id->setDisabled(true);
    save->setEnabled(false);

    //QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveNote()));
    QObject::connect(titre,SIGNAL(textChanged(QString)),this,SLOT(activeSave()));
    editeurs.push_back(this);

}

NoteEditeur::~NoteEditeur()
{
    editeurs.remove(editeurs.indexOf(this));
}

void NoteEditeur::SaveNote() {
    qDebug()<<"test1";
    NoteManager& m = NoteManager::getInstance();
    QString repertoire = m.getDirectory();//récupère le répertoire
    qDebug()<<"test2";

    note->setTitre(titre->text());
    qDebug()<<"test3";

    //appel de la méthode save du NoteManager
    m.save(note,repertoire);
    qDebug()<<"test14";

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
