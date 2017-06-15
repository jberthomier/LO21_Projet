#ifndef ARTICLEEDITEUR_H
#define ARTICLEEDITEUR_H

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

class ArticleEditeur : public NoteEditeur
{
private :
    Q_OBJECT

    QLabel* text1;
    QTextEdit* texte;
    void sauvegarde();

public:
    ArticleEditeur(Article* a, QWidget *parent = 0);
    ~ArticleEditeur();

public slots:

};

#endif // ARTICLEEDITEUR_H
