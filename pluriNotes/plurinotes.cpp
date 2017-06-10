#include "PluriNotes.h"
#include <qDebug>
#include <QList>
#include <QTabWidget>

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    /*qDebug()<<"launched";
    ui->setupUi(this);
    FilePath = QDir::currentPath() + "/config.ini";
    QFileInfo file_path(FilePath);
    if (!file_path.exists()){
        QSettings* settings = new QSettings(FilePath, QSettings::IniFormat);
        settings->setValue("folder", QDir::currentPath());
        settings->sync();
        qDebug()<<"file created"<<endl;
    }*/

    //loadSettings();
    //ouvrirProjet();
    QObject::connect(ui.actionArticle, SIGNAL(triggered()), this, SLOT(newArticle()));
    QObject::connect(ui.actionTache, SIGNAL(triggered()), this, SLOT(newTache()));
    QObject::connect(ui.actionMedia, SIGNAL(triggered()), this, SLOT(newMedia()));
    QObject::connect(ui.actionOuvrir, SIGNAL(triggered()), this, SLOT(getChemin()));

    updateActiveNotes(); //création de la liste des notes actives
    updateArchiveNotes(); //création de la liste des notes archivées
    updateSortedTasks();
     /*Par contre les notes créées lors de la session ne s'affichent pas, il faudra rappeler update après la création d'une note.*/


}

PluriNotes::~PluriNotes()
{
    //delete ui;
}

void newArticle()
{
        NoteManager& m = NoteManager::getInstance();

        Article* a= m.makeArticle();
        //ouvrirNote(a);
}

void newTache()
{
        NoteManager& m = NoteManager::getInstance();

        Tache* t= m.makeTache();
        //ouvrirNote(t);
}

void newMedia()
{
        NoteManager& m = NoteManager::getInstance();

        Media* med= m.makeMedia();
        //ouvrirNote(med);
}

void getChemin (QListWidgetItem* id) {
    NoteManager& m = NoteManager::getInstance();
    Note& n=m.getNote(id->text());
    qDebug()<<"Ouvertude note"<<id->text();
    //ui.AffichageNote->ouvrirNote(&n);
}

void PluriNotes::updateActiveNotes(){
    QList<Note*> notes = NoteManager::getInstance().getActiveNotes();
    for(auto ite = notes.begin(); ite != notes.end(); ++ite) {
        ui.noteList->addItem((*ite)->getId());
    }
}
void PluriNotes::updateArchiveNotes(){
    QList<Note*> notes = NoteManager::getInstance().getArchiveNotes();
    for(auto ite = notes.begin(); ite != notes.end(); ++ite) {
        ui.archiveList->addItem((*ite)->getId());
    }
}

void PluriNotes::updateSortedTasks(){ //veut-on aussi afficher la date et la priorité avec la tache ?
    QList<Tache*> notes = NoteManager::getInstance().getSortedTasks();
    for(auto ite = notes.begin(); ite != notes.end(); ++ite) {
        ui.taskList->addItem((*ite)->getId());
    }
}
