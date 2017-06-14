#include "mediaediteur.h"

MediaEditeur::MediaEditeur(Media *m, QWidget *parent) : NoteEditeur(m,parent)
{
    desc = new QLabel("Description");
    filepath = new QLabel("Chemin",this);

    description = new QTextEdit;
    chemin = new QLineEdit(this);

    QPushButton *openButton = new QPushButton(tr("Open..."));
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    player = new VideoPlayer();

    QVBoxLayout* v1 = new QVBoxLayout();
    QHBoxLayout* h1 = new QHBoxLayout();
    QHBoxLayout* h2 = new QHBoxLayout();

    h1->addWidget(desc);
    h1->addWidget(description);

    h2->addWidget(filepath);
    h2->addWidget(chemin);
    h2->addWidget(openButton);

    v1->addLayout(h1);
    v1->addWidget(player);
    v1->addLayout(h2);

    layout->addLayout(v1);

    if(m->getFilename()!=""){
        openFile(m->getFilename());
        chemin->setText(m->getFilename());
    }


    description->setText(m->getDescription());

    QObject::connect(description, SIGNAL(textChanged()), this, SLOT(activeSave()));
    QObject::connect(chemin, SIGNAL(textChanged(QString)), this, SLOT(activeSave()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveMedia()));



}


MediaEditeur::~MediaEditeur() {

}


void MediaEditeur::openFile(QString f){

    if (f==""){
        QFileDialog fileDialog(this);
        fileDialog.setWindowTitle(tr("Open Movie"));
        fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
        f = fileDialog.getOpenFileName();
        chemin->setText(f);
    }
    player->setUrl(QUrl::fromLocalFile(f));
    player->play();
}
