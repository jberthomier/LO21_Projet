#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QVector>
#include "couple.h"

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
    QVector<QVector<Note> > versions;

    //Gestion de l'identificateur des versions
    unsigned int id;
    unsigned int newId();

public:
    static NoteManager& getInstance();
    Note* makeNote(); //comme on retourne un pointeur sur Note, ok même si la classe Note est abstraite
    Note& getNote(const unsigned int id); //récupérer n'importe quelle note, même archivée ou dans la corbeille
    Note& getNoteActuelle(const unsigned int id);
    template<typename T> void editNote(const unsigned int id);
    void restaurerNote(const unsigned int id);
    void supprimerNoteActuelle(const unsigned int id);
    void supprimerVersions(const unsigned int id);
    void viderCorbeille();
    void save() const; //à faire !
};

template<typename T> void NoteManager::editNote(const unsigned int id) {
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
        QVector<Note> NewNote;
        NewNote.push_back(*note);
        versions.push_back(NewNote);
    }
}

#endif // NOTEMANAGER_H
