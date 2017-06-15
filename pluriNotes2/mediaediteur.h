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
#include "player.h"


class MediaEditeur : public NoteEditeur
{
private :

    Q_OBJECT

	//Classe amie
    friend class AffichageNote;

	//Attributs
    QLabel* desc;
    QLabel* filepath;

    QTextEdit* description;
    QLineEdit* chemin;

    VideoPlayer* player;

	//Méthode
    void sauvegarde();

public:

	//Constructeur et destructeur
    MediaEditeur(Media* m, QWidget *parent=0);
    ~MediaEditeur();

public slots:

	//Méthodes
    void saveMedia(){
        dynamic_cast<Media*>(getNote())->setDescription(description->toPlainText());
        dynamic_cast<Media*>(getNote())->setFilename(chemin->text());
        qDebug()<<"help1";
        saveNote();
    }

    void openFile(QString f="");
};

#endif // MEDIAEDITEUR_H
