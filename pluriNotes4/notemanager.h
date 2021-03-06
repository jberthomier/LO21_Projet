#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QVector>
#include <QString>
#include <QList>
#include "couple.h"
#include <QDir>


class NoteManager {

private:
    //Attribut
	/**
     * \brief Répertoire où sont rangées toutes les notes
     */
    QDir directory; //répertoire où sont rangées toutes les notes
	/**
     * \brief Nom du fichier dans lequel sera sauvegardé la note
     */
    mutable QString filename;
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
    NoteManager(const NoteManager& m);
	/**
     * \brief Opérateur d'affectation de NoteManager
     * \details Il est déclaré en privé afin d'empêcher la création d'une deuxième instance par l'utilisateur.
     * Cette méthode n'est pas défini pour que l'on ne puisse pas créer plus d'une instance de NoteManager.
     */
    NoteManager& operator=(const NoteManager& m);

    //Stockage des versions
	/**
     * \brief Tabeau dynamique des versions des notes
     * \details Permet de stocker toutes les versions des notes
     */
    QVector<QVector<Note*> > versions;

    //Gestion de l'identificateur des versions
	/**
     * \brief Identificateur pour les versions
     */
    QString id;
	/**
     * \brief Génère un nouvel identificateur pour une note
     */
    QString newId();

public:
    static NoteManager& getInstance();
	
	//Accesseurs en lecture
	/**
     * \brief Accesseur en lecture du nom du fichier dans lequel sera sauvegardé la note
     */
	QString getFilename() const { return filename; }
	/**
     * \brief Accesseur en lecture d'une note
     * \details Permet de récupérer une référence vers une note (n'importe laquelle) à partir de son identificateur.
     * Cette méthode permet de récupérer un note, même si elle est archivée ou dans la corbeille
     */
	Note* getNote(const QString id); //récupérer n'importe quelle note, même archivée ou dans la corbeille
    /**
     * \brief Accesseur en lecture de la version active d'une note
	   \details Cette méthode servira lorsque l’on voudra restaurer une note. En effet, s’il existe déjà une version active, 
	   il faudra d’abord archiver celle-ci avant de réactiver notre note. On fera donc appel à la méthode getNoteActuelle(QString id) 
	   pour récupérer la version active de la note que l’on veut réactiver
     */
	Note& getNoteActuelle(const QString  id);
	/**
     * \brief Accesseur en lecture du chemin du répertoire dans lequel le fichier contenant la sauvegarde des notes sera placé
     */
	QString getDirectory(){return directory.path();}
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
    
    QVector<Note*> getVector(QString id);
	
	//Accesseur en écriture
	void setNoteId(Note* note, QString id){note->setId(id);}
    void setNoteTitle(Note * n, QString title){n->setTitre(title);}
    /**
     * \brief Accesseur en écriture du chemin du répertoire dans lequel le fichier contenant la sauvegarde des notes sera placé
     */
    void setDirectory(QString path){directory=path;}
	/**
     * \brief Accesseur en écriture du nom du fichier dans lequel sera sauvegardé la note
     */
	void setFilename(const QString& f) { filename=f; }
    void setMediaDescription(QString d, Media*m){m->setDescription(d);}
    void setArticleText(Article*a,QString t){a->setText(t);}
    void setMediaPath(QString path, Media* m){m->setChemin(path);}
	
	//Méthodes
    Note* makeNote(); //comme on retourne un pointeur sur Note, ok même si la classe Note est abstraite
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
    void pushToVersions(Note* note);
	void load();
    /**
     * \brief Méthode permettant de restaurer une note qui était dans la corbeille ou une ancienne version
     */
    void restaurerNote(const QString  id);
	/**
     * \brief Méthode permettant de supprimer toutes les versions d'une note
     */
    void supprimerVersions(const QString  id);
	/**
     * \brief Méthode permettant d'archiver une note
     */
    void archiverNote(Note* note){note->archiver();}
	/**
     * \brief Méthode permettant de supprimer toutes les notes de la corbeille.
     */
    void viderCorbeille();
	/**
     * \brief Méthode permettant de sauvegarder les notes
     */
    void save(Note *n, QString repertoire) const;    

public slots:
	/**
     * \brief Méthode permettant de supprimer la note actuelle
     */
    void supprimerNoteActuelle(const QString  id);
};

#endif // NOTEMANAGER_H
