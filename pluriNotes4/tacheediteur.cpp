#include "tacheediteur.h"

/*------------------------------------------------------Méthode privée de la classe TacheEditeur-------------------------------------------------------*/

void TacheEditeur::sauvegarde() {
    //Appel du getNote() de NoteEditeur
    if(dynamic_cast<Tache*>(getNote()))
    dynamic_cast<Tache*>(getNote())->setAction(action->toPlainText());
    dynamic_cast<Tache*>(getNote())->setPriorite(priorite->value());
    //dynamic_cast<Tache*>(getNote())->setDdm(echance->toPlainText());

}

/*------------------------------------------------------Méthodes publiques de la classe TacheEditeur-------------------------------------------------------*/

/*------------------------------------------------------Constructeur et destructeur-------------------------------------------------------*/

TacheEditeur::TacheEditeur(Tache* t, QWidget* parent) : NoteEditeur(t,parent)
{
    act1 = new QLabel("Action");
    prior = new QLabel("Priorite");
    dateE = new QLabel("Date d'echeance (dd/mm/yyy)");
    state = new QLabel("Etat");

    action = new QTextEdit;
    priorite = new QSpinBox;

    etat = new QComboBox;

    priorite->setMinimum(0);
    priorite->setMaximum(5);
    priorite->setSingleStep(1);
    priorite->setValue(0);

    etat->addItem("En attente");
    etat->addItem("En cours");
    etat->addItem("Terminee");

    echeance = new QDateEdit;

    layout->addWidget(act1);
    layout->addWidget(action);

    layout->addWidget(prior);
    layout->addWidget(priorite);

    layout->addWidget(dateE);
    layout->addWidget(echeance);

    layout->addWidget(state);
    layout->addWidget(etat);

    /*Statut e;
    if (etat->currentText()=="En attente")
        e=En_attente;
    if (etat->currentText()=="En cours")
        e=En_cours;
    if (etat->currentText()=="Terminee")
        e=Terminee;*/

    if (t->getStatut() ==En_attente) etat->setCurrentIndex(0);
    if (t->getStatut() ==En_cours) etat->setCurrentIndex(1);
    if (t->getStatut() ==Terminee) etat->setCurrentIndex(2);

    action->setText(t->getAction());
    priorite->setValue(t->getPriorite());
    echeance->setDate(t->getEcheance());

    QObject::connect(action,SIGNAL(textChanged()),this,SLOT(activeSave()));
    QObject::connect(priorite,SIGNAL(valueChanged(int)),this,SLOT(activeSave()));
    QObject::connect(echeance,SIGNAL(dateChanged(QDate)),this,SLOT(activeSave()));
    QObject::connect(etat,SIGNAL(currentIndexChanged(QString)),this,SLOT(activeSave()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveTache()));
}

TacheEditeur::~TacheEditeur() {

}
