#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

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
#include "qwidget.h"
#include "notemanager.h"

class NoteEditeur : public QWidget
{
private :
    Q_OBJECT

protected:

	//Attributs
    QHBoxLayout * cid;
    QHBoxLayout * ctitre;
    QVBoxLayout * couche;
    QLabel *id1;
    QLabel *titre1;
    QPushButton *save;
    QLineEdit *id;
    QLineEdit *titre;
    Note * note;
    QString filename;
	QHBoxLayout *layout;

	//Constructeurs
    NoteEditeur(NoteEditeur& );
    NoteEditeur& operator=(NoteEditeur const&);
	
	//Accesseur en lecture
	Note* getNote() const { return note; }

public:

	//Attribut
    static QVector<NoteEditeur*> editeurs;
	
	//Constructeur et desctructeur
    NoteEditeur(Note* n, QWidget *parent = 0);
    virtual ~NoteEditeur();
	
	//Accesseur en lecture
    const QString getId() const { return id->text(); }
	
	//Méthode
    void SaveNote();

signals:

    void Editing(NoteEditeur* f);
    void Editionfinished(NoteEditeur* f);


public slots:

    //Les slots sont avant tout des méthodes qui peuvent être appelées normalement
   // void saveNote();
    void activeSave();
    void verification();
};

#endif // NOTEEDITEUR_H
