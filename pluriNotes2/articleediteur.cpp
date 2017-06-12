#include "articleediteur.h"


ArticleEditeur::ArticleEditeur(Article* a, QWidget* parent) : NoteEditeur(a,parent)
{
    qDebug()<<"Entree21";
    text1 = new QLabel("Texte");
    texte = new QTextEdit;
    qDebug()<<"Entree22";
    layout->addWidget(text1);
    qDebug()<<"Entree22-1";
    layout->addWidget(texte);
    qDebug()<<"Entree23";
    texte->setText(a->getTexte());
    qDebug()<<"Entree24";
    QObject::connect(texte,SIGNAL(textChanged()),this,SLOT(activeSave()));
    qDebug()<<"Entree25";
}

ArticleEditeur::~ArticleEditeur() {

}

void ArticleEditeur::sauvegarde() {
    if(dynamic_cast<Article*>(getNote()))
        qDebug()<<"article";
    dynamic_cast<Article*>(getNote())->setText(texte->toPlainText());
}
