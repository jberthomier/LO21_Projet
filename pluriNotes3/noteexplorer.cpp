#include "noteexplorer.h"
#include "notemanager.h"

NoteExplorer::NoteExplorer(QWidget *parent) :QWidget(parent)
{
    NoteList = QListWidget(this);
    NoteManager& m = NoteManager::getInstance();
    QList<Note*> notesActives = m.getActiveNotes();
     for (auto ite = notesActives.begin(); ite != list.end(); ++ite){
         NoteList->addItem((*ite)->getTitre());
     }
}
