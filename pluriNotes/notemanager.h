#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QVector>
#include <QString>
#include <QList>
#include "couple.h"

class NoteManager {

private:

    /**
     * \brief Instance unique de NoteManager
     * \details L'unique instance de la classe NoteManager est accessible via cet attribut statique instance
     */
    static NoteManager* instance;

    //Constructeurs, opérateurs de recopie et d'affectation et destructeur
    /**
     * \brief Constructeur sans argument de NoteManager
     * \details Il est déclaré en privé afin d'empêcher la création d'une deuxième instance par l'utilisateur
     */
    NoteManager();
    /**
     * \brief Destructeur de NoteManager
     * \details Il est déclaré en privé afin d'empêcher l'appel au destructeur par l'utilisateur.
     */
    ~NoteManager();
    /**
     * \brief Constructeur de NoteManager
     * \details Il est déclaré en privé afin d'empêcher la création d'une deuxième instance par l'utilisateur.
     * Cette méthode n'est pas défini pour que l'on ne puisse pas créer plus d'une instance de NoteManager.
     */
    NoteManager(const NoteManager& nm);
    /**
     * \brief Opérateur d'affectation de NoteManager
     * \details Il est déclaré en privé afin d'empêcher la création d'une deuxième instance par l'utilisateur.
     * Cette méthode n'est pas défini pour que l'on ne puisse pas créer plus d'une instance de NoteManager.
     */
    NoteManager& operator=(const NoteManager& nm);

    //Stockage des versions
    /**
     * \brief Tabeau dynamique des versions des notes
     * \details Permet de stocker toutes les versions des notes
     */
    QVector<QVector<Note*> > versions;

    //Gestion de l'identificateur des versions
    /**
     * \brief Identificateur pour notes
     * \details L'identification des notes est géré par NoteManager qui attribut un identicateur à chaque nouvelle note créée
     */
    unsigned int id;
    /**
     * \brief Génère un nouvel identificateur unique
     */
    unsigned int newId();

public:

    //Accesseurs en lecture
    /**
     * \brief Accesseur en lecture d'une note
     * \details Permet de récupérer une référence vers une note à partir de son identificateur.
     * Cette méthode permet de récupérer un note, même si elle est archivée ou dans la corbeille
     */
    Note& getNote(QString id);
    /**
     * \brief Accesseur en lecture de la note active
     */
    Note& getNoteActuelle(QString id);
    /**
     * \brief Accesseur en lecture des notes actives
     * \details Permet de récupérer dans une liste un pointeur vers les notes actives
     */
    QList<Note*> getActiveNotes();
    /**
     * \brief Accesseur en lecture des notes archivées
     * \details Permet de récupérer dans une liste un pointeur vers les notes archivées
     */
    QList<Note*> getArchiveNotes();
    /**
     * \brief Accesseur en lecture des tâches par ordre de priorité
     * \details Permet de récupérer dans une liste un pointeur vers les tâches, triées par ordre de priorité
     */
    QList<Tache*> getSortedTasks();

    //Méthodes
    static NoteManager& getInstance();
    /**
     * \brief Méthode permettant de créer un nouvel article
     */
    Article* makeArticle();
    /**
     * \brief Méthode permettant de créer une nouvelle tâche
     */
    Tache* makeTache();
    /**
     * \brief Méthode permettant de créer un nouveau média
     */
    Media* makeMedia();
    /**
     * \details Cette fonction est un template. Cela permet d'appeler editNote avec n'importe quelle classe d'objet héritant de Note.
     */
    template<typename T> void editNote(QString id);
    /**
     * \brief Méthode permettant de restaurer une note qui était dans la corbeille ou une ancienne version
     */
    void restaurerNote(QString id);
    /**
     * \brief Méthode permettant de supprimer la note actuelle
     */
    void supprimerNoteActuelle(QString id);
    /**
     * \brief Méthode permettant de supprimer toutes les versions d'une note
     */
    void supprimerVersions(QString id);
    /**
     * \brief Méthode permettant de supprimer toutes les notes de la corbeille.
     */
    void viderCorbeille();
    /**
     * \brief Méthode permettant de sauvegarder les notes
     */
    void save() const;
};

template<typename T> void NoteManager::editNote(QString id) {
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
    catch (NoteException e) { //si la note n'existe pas, on veut en créer une
        QString type = t.getType();
        if (type=="article") {
            Article* note = NoteManager::makeArticle();
            QVector<Article*> NewNote;
        }
        else if (type=="tache") {
            Tache* note = NoteManager::makeTache();
            QVector<Tache*> NewNote;
        }
        else {
            Media* note = NoteManager::makeMedia();
            QVector<Media*> NewNote;
        }
        NewNote.push_back(note);
        versions.push_back(NewNote);
    }
}

#endif // NOTEMANAGER_H
