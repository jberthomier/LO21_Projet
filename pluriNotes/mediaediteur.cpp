#include "mediaediteur.h"

MediaEditeur::MediaEditeur(Media *m, QWidget *parent) : NoteEditeur(m,parent)
{
    desc = new QLabel("Description");
    filepath = new QLabel("Chemin");

    description = new QTextEdit;
    chemin = new QTextEdit;

    centralLayout->addWidget(desc);
    centralLayout->addWidget(description);

    centralLayout->addWidget(filepath);
    centralLayout->addWidget(chemin);

    desc->setText(m->getDescription());
    chemin->setText(m->getChemin());

    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activeSave()));
    QObject::connect(chemin,SIGNAL(textChanged()),this,SLOT(activeSave()));
}


MediaEditeur::~MediaEditeur() {

}
