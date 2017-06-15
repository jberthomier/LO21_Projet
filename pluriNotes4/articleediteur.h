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

	//Attributs
    QLabel* text1;
    QTextEdit* texte;
	
	//Méthode
    void sauvegarde();

public:

	//Constructeur et destructeur
    ArticleEditeur(Article* a, QWidget *parent = 0);
    ~ArticleEditeur();
	
	//Accessseur en lecture
	QHBoxLayout* getLayout()const {return layout;}

public slots:

	//Méthode
	void saveArticle(){
		Article* a = dynamic_cast<Article*>(note);
		a->setText(texte->toPlainText());
		qDebug()<<"help1";
        NoteEditeur::SaveNote();
	}

};

#endif // ARTICLEEDITEUR_H
