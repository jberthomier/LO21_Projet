#include "tacheediteur.h"

TacheEditeur::TacheEditeur(Tache* t, QWidget* parent) : NoteEditeur(t,parent)
{
   /* act1 = new QLabel("Action");
    prior = new QLabel("Priorite");
    dateE = new QLabel("Date d'echeance");

    action = new QTextEdit;
    priorite = new QSpinBox;

    priorite->setMinimum(0);
    priorite->setMaximum(5);
    priorite->setSingleStep(1);
    priorite->setValue(0);

    //echeance = new QDate;

    layout->addWidget(act1);
    layout->addWidget(action);

    layout->addWidget(prior);
    layout->addWidget(priorite);

    layout->addWidget(dateE);
    //layout->addWidget(echeance);

    action->setText(t->getAction());
    priorite->value();
    //echeance->setText(t->getEcheance());

    QObject::connect(action,SIGNAL(textChanged()),this,SLOT(activeSave()));
    QObject::connect(priorite,SIGNAL(valueChanged(int)),this,SLOT(activeSave()));
    //QObject::connect(echeance,SIGNAL(textChanged()),this,SLOT(activeSave()));

*/

}

TacheEditeur::~TacheEditeur() {

}

void TacheEditeur::sauvegarde() {
  /*  //Appel du getNote() de NoteEditeur
    if(dynamic_cast<Tache*>(getNote()))
        qDebug()<<"tache";
    dynamic_cast<Tache*>(getNote())->setAction(action->toPlainText());
    dynamic_cast<Tache*>(getNote())->setPriorite(priorite->value());
    //dynamic_cast<Tache*>(getNote())->setTexte(echance->toPlainText());
*/
}
