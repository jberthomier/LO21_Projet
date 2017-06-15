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
#include <QSpinBox>
#include "Note.h"
#include "noteediteur.h"

class TacheEditeur : public NoteEditeur
{
private:
    Q_OBJECT

    QLabel* act1;
    QLabel* prior;
    QLabel* dateE;
    QTextEdit* action;
    QSpinBox* priorite;
    QDate echeance;
    void sauvegarde();

public:
    TacheEditeur(Tache* t, QWidget *parent = 0);
    ~TacheEditeur();

public slots:

};

#endif // TACHEEDITEUR_H




