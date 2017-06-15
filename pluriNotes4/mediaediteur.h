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
#include "notemanager.h"

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
        NoteManager& m = NoteManager::getInstance();
        Media* media = dynamic_cast<Media*>(getNote());
        m.setMediaDescription(description->toPlainText(), media);
        m.setFilename(chemin->text());
        qDebug()<<"help1";
        NoteEditeur::SaveNote();
    }

    void openFile(QString f="");
};

#endif // MEDIAEDITEUR_H
