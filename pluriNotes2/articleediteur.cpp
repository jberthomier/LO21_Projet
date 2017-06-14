#include "articleediteur.h"


ArticleEditeur::ArticleEditeur(Article* a, QWidget* parent) : NoteEditeur(a,parent)
{
    qDebug()<<"Entree21";
    text1 = new QLabel("Texte");
    texte = new QTextEdit;
    qDebug()<<"Entree22";


    getLayout()->addWidget(text1);
    qDebug()<<"Entree22-1";
    getLayout()->addWidget(texte);
    qDebug()<<"Entree23";
    texte->setText(a->getTexte());
    qDebug()<<"Entree24";
    QObject::connect(texte,SIGNAL(textChanged()),this,SLOT(activeSave()));
    qDebug()<<"Entree25";
    save->setEnabled(false);
    QObject::connect(titre,SIGNAL(textChanged()),this,SLOT(activeSave()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
}

ArticleEditeur::~ArticleEditeur() {

}

