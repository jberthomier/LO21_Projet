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
    QVBoxLayout * couche;
    QLabel *id1;
    QLabel *titre1;    
    QPushButton *save;
    QLineEdit *id;
    QLineEdit *titre;
    Note * note;

    NoteEditeur(NoteEditeur& );
    NoteEditeur& operator=(NoteEditeur const&);

protected :
    QHBoxLayout *layout;
    Note* getNote() const { return note; }

public:
    NoteEditeur(Note* n, QWidget *parent = 0);
    virtual ~NoteEditeur();
    const QString getId() const { return id->text(); }
    static QVector<NoteEditeur*> editeurs;
    void SaveNote();

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

