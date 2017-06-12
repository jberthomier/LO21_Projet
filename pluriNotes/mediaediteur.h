#ifndef MEDIAEDITEUR_H
#define MEDIAEDITEUR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QObject>
#include "Note.h"
#include "noteediteur.h"


class MediaEditeur : public NoteEditeur
{
private :
    Q_OBJECT

    QLabel* desc;
    QLabel* filepath;

    QTextEdit* description;
    QTextEdit* chemin;


    void sauvegarde();


public:
    MediaEditeur(Media* m, QWidget *parent=0);
    ~MediaEditeur();
};

#endif // MEDIAEDITEUR_H
