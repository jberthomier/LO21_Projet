#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QVector>
#include <QString>
#include <QList>
#include "couple.h"
#include <QDir>


class NoteManager {

private:
    //L'unique instance de la classe est accessible via cet attribut statique instance.
    static NoteManager* instance;

    /*Déclaration des constructeurs, opérateurs de recopie et d'affectation afin d'empêcher la création d'une deuxième instance par l'utilisateur.*/
    NoteManager();
    ~NoteManager();
    NoteManager(const NoteManager& nm);
    NoteManager& operator=(const NoteManager& nm);

    //Stockage des versions
    QVector<QVector<Note*> > versions;

    //Gestion de l'identificateur des versions
    QString id;
    QString newId();

    QDir directory; //répertoire où sont rangées toutes les notes

public:
    static NoteManager& getInstance();
    Note* makeNote(); //comme on retourne un pointeur sur Note, ok même si la classe Note est abstraite
    Article* makeArticle();
    Tache* makeTache();
    Media* makeMedia();

    Note* getNote(const QString id); //récupérer n'importe quelle note, même archivée ou dans la corbeille
    Note& getNoteActuelle(const QString  id);
    void setDirectory(QString path){directory=path;}
    QString getDirectory(){return directory.path();}
    void pushToVersions(Note* note);

    template<typename T> void editNote(const QString  id);
    void restaurerNote(const QString  id);
    void supprimerNoteActuelle(const QString  id);
    void supprimerVersions(const QString  id);
    void archiverNote(Note* note){note->archiver();}
    void viderCorbeille();
    void save(Note *n, QString repertoire) const; //à faire !
    void saveAll() const;
    QList<Note*> getActiveNotes(); //retourne la liste des notes actives
    QList<Note*> getArchiveNotes(); //retourne la liste des notes archivées
    QList<Tache*> getSortedTasks();
};

template<typename T> void NoteManager::editNote(QString  id) {
    try {
        T t = getNote(id);
        if (t.isActive() == false)
            throw ArchiveException("La note est archivee.");
        T* newNote = t.edit();
        int position = -1;
        for (int i = 0; i < versions.size(); i++) {
            for (int j = 0; j < versions[i].size(); i++) {
                if (id == versions[i][j].getId()) {
                    position = i;
                    break;
                }
            }
            if (position != -1) break;
        }
        versions[position].push_back(*newNote);
    }
    catch (NotesException e) { //si la note n'existe pas, on veut en créer une
        Note* note = NoteManager::makeNote();
        QVector<Note*> NewNote;
        NewNote.push_back(note);
        versions.push_back(NewNote);
    }
}

#endif // NOTEMANAGER_H
