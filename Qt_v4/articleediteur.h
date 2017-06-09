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
#include "notemanager.h"

class ArticleEditeur : public QWidget
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
    Article * article;

    ArticleEditeur(ArticleEditeur& );
    ArticleEditeur& operator=(ArticleEditeur const&);

public:
    ArticleEditeur(Article &a, QWidget *parent = 0);

signals:


public slots:
    //Les slots sont avant tout des méthodes qui peuvent être appelées normalement
    void saveArticle();
    void activeSave();
};

#endif // ARTICLEEDITEUR_H
