#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include "qwidget.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QHboxLayout>
#include <QFileDialog>
#include <iostream>
#include <QObject>
#include <QMessageBox>
#include "Note.h"

class NoteEditeur : public QWidget
{
private :
    Q_OBJECT

    QHBoxLayout * cid;
    QHBoxLayout * ctitre;
    QHBoxLayout * ctext;
    QVBoxLayout * couche;
    QLabel *id1;
    QLabel *titre1;
    QLabel *text1;
    QPushButton *save;
    QLineEdit *id;
    QLineEdit *titre;
    QTextEdit *text;
    Note * note;

    NoteEditeur(NoteEditeur& );
    NoteEditeur& operator=(NoteEditeur const&);

protected :
    QHBoxLayout *centralLayout;
    Note* getNote() const { return note; }

public:
    NoteEditeur(Note* n, QWidget *parent = 0);
    virtual ~NoteEditeur();
    const QString getId() const { return id->text(); }
    static QVector<NoteEditeur*> editeurs;
    void SaveNote()const {getNote()->saveNote();}

signals:
    void Editing(NoteEditeur* f);
    void Editionfinished(NoteEditeur* f);


public slots:
    //Les slots sont avant tout des méthodes qui peuvent être appelées normalement
    void saveNote();
    void activeSave();
    void verification();
};

#endif // NOTEEDITEUR_H

/*
//fenetre de verification de sauvegarde a la fermeture

class NoteEditeurFermeture : public QDialog
{
public:

    NoteEditeurFermeture(QWidget *parent = 0) :QDialog(parent)
    {
        Vlayout = new QVBoxLayout(this);
        Hlayout = new QHBoxLayout(this);

        text = new QLabel("Des changements ont ete effectues. Les sauvegarder ?");
        closeBtn = new QPushButton("Non");
        acceptBtn = new QPushButton("Oui");
        Vlayout->addWidget(text);
        Hlayout->addWidget(acceptBtn);
        Hlayout->addWidget(closeBtn);

        Vlayout->addLayout(Hlayout);
        setModal(true);

        connect(acceptBtn, SIGNAL(clicked()), this, SLOT(accept()));
        connect(closeBtn, SIGNAL(clicked()), this, SLOT(reject()));
        show();
    }
private:
    QVBoxLayout* Vlayout;
    QHBoxLayout* Hlayout;
    QLabel *text;
    QPushButton *closeBtn;

    QPushButton *acceptBtn;
};*/
