#include "mediaediteur.h"

MediaEditeur::MediaEditeur(Media *m, QWidget *parent) : NoteEditeur(m,parent)
{
   /* desc = new QLabel("Description");
    filepath = new QLabel("Chemin");

    description = new QTextEdit;
    chemin = new QTextEdit;

    layout->addWidget(desc);
    layout->addWidget(description);

    layout->addWidget(filepath);
    layout->addWidget(chemin);

    desc->setText(m->getDescription());
    chemin->setText(m->getChemin());

    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activeSave()));
    QObject::connect(chemin,SIGNAL(textChanged()),this,SLOT(activeSave()));
*/
}


MediaEditeur::~MediaEditeur() {

}
