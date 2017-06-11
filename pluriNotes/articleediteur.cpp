#include "articleediteur.h"


ArticleEditeur::ArticleEditeur(Article* a, QWidget* parent) : NoteEditeur(a,parent)
{
    text1 = new QLabel("Texte");
    texte = new QTextEdit;

    centralLayout->addWidget(text1);
    centralLayout->addWidget(texte);

    texte->setText(a->getTexte());

    QObject::connect(texte,SIGNAL(textChanged()),this,SLOT(activeSave()));
}

ArticleEditeur::~ArticleEditeur() {

}

void ArticleEditeur::sauvegarde() {
    if(dynamic_cast<Article*>(getNote()))
        qDebug()<<"article";
    dynamic_cast<Article*>(getNote())->setText(texte->toPlainText());
}
