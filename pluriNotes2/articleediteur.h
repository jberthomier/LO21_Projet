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
    QHBoxLayout* getLayout()const {return layout;}

public slots:

    void saveArticle(){
        Article* a = dynamic_cast<Article*>(note);
        a->setText(texte->toPlainText());
        qDebug()<<"help1";
        saveNote();
    }

};

#endif // ARTICLEEDITEUR_H
