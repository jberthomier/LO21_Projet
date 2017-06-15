#include "articleediteur.h"

/*------------------------------------------------------Constructeur et destructeur-------------------------------------------------------*/

ArticleEditeur::ArticleEditeur(Article* a, QWidget* parent) : NoteEditeur(a,parent)
{
    text1 = new QLabel("Texte");
    texte = new QTextEdit;

    getLayout()->addWidget(text1);
    getLayout()->addWidget(texte);
    texte->setText(a->getTexte());
    QObject::connect(texte,SIGNAL(textChanged()),this,SLOT(activeSave()));
    save->setEnabled(false);
    QObject::connect(titre,SIGNAL(textChanged()),this,SLOT(activeSave()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
}

ArticleEditeur::~ArticleEditeur() {

}
