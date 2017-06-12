#include "PluriNotes.h"
#include <qDebug>
#include <QList>
#include <QTabWidget>

PluriNotes::PluriNotes(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject::connect(ui.actionArticle, SIGNAL(triggered()), this, SLOT(newArticle()));
    QObject::connect(ui.actionTache, SIGNAL(triggered()), this, SLOT(newTache()));
    QObject::connect(ui.actionMedia, SIGNAL(triggered()), this, SLOT(newMedia()));
    QObject::connect(ui.actionOuvrir, SIGNAL(triggered()), this, SLOT(getChemin(QListWidgetItem*)));

    updateActiveNotes(); //création de la liste des notes actives
    updateArchiveNotes(); //création de la liste des notes archivées
    updateSortedTasks();
}

PluriNotes::~PluriNotes()
{
    //delete ui;
}

void PluriNotes::newArticle()
{

        NoteManager& m = NoteManager::getInstance();
        Article* a= m.makeArticle();
         qDebug()<<"Entree4";
        AffichageNote* viewer = new AffichageNote();
         qDebug()<<"Entree5";
        viewer->afficheArticle(a);
         qDebug()<<"Entree6";
        viewer->show();
        qDebug()<<"Entree6-1";
        this->updateActiveNotes();
        "Test1";
        this->updateArchiveNotes();
        "Test2";
        this->updateSortedTasks();
        "Test3";
}

void PluriNotes::newTache()
{
        NoteManager& m = NoteManager::getInstance();

        Tache* t= m.makeTache();
        //ouvrirNote(t);
}

void PluriNotes::newMedia()
{
        NoteManager& m = NoteManager::getInstance();

        Media* med= m.makeMedia();
        //ouvrirNote(med);
}

void PluriNotes::getChemin (QListWidgetItem* id) {
    NoteManager& m = NoteManager::getInstance();
    Note& n=m.getNote(id->text());
    qDebug()<<"Ouverture note"<<id->text();
    AffichageNote* viewer = new AffichageNote();
    viewer->afficheNote(&n);
    viewer->show();
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


void PluriNotes::ouvrirNote(QListWidgetItem* item) {

    NoteManager& m = NoteManager::getInstance();
    Note& n = m.getNote(item->text());
    qDebug()<<"ouverture note"<<item->text();
    AffichageNote* viewer = new AffichageNote();
    viewer->afficheNote(&n);
    viewer->show();

}
