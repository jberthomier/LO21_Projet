#ifndef TACHEEDITEUR_H
#define TACHEEDITEUR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QObject>
#include <QDate>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>

#include "Note.h"
#include "noteediteur.h"

class TacheEditeur : public NoteEditeur
{
private:

    Q_OBJECT

	//Attributs
    QLabel* act1;
    QLabel* prior;
    QLabel* dateE;
    QLabel* state;
    QTextEdit* action;
    QSpinBox* priorite;
    QDateEdit* echeance;
    QComboBox* etat;
	
	//Méthode
    void sauvegarde();

public:

	//Constructeur et destructeur
    TacheEditeur(Tache* t, QWidget *parent = 0);
    ~TacheEditeur();

public slots:

	//Méthodes
    void saveTache(){
        Tache* t = dynamic_cast<Tache*>(note);
        t->setAction(action->toPlainText());
       dynamic_cast<Tache*>(getNote())->setEcheance(echeance->date());

       QDate ddm = QDate::currentDate();
       t->setDdm(ddm);

       dynamic_cast<Tache*>(getNote())->setPriorite(priorite->value());


       Statut s;
         switch (etat->currentIndex()) {
            case 1 :
                s=En_cours;
                break;
            case 2 :
                s=Terminee;
                break;
            default:
                s=En_attente;
                break;
            }
      dynamic_cast<Tache*>(getNote())->setEtat(s);


        qDebug()<<"help2";
        NoteEditeur::SaveNote();
    }

};

#endif // TACHEEDITEUR_H




