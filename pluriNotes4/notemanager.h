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
    NoteManager(const NoteManager& m);
    NoteManager& operator=(const NoteManager& m);

    //Stockage des versions
    QVector<QVector<Note*> > versions;

    //Gestion de l'identificateur des versions
    QString id;
    QString newId();

    QDir directory; //répertoire où sont rangées toutes les notes

    mutable QString filename;

public:
    static NoteManager& getInstance();
    Note* makeNote(); //comme on retourne un pointeur sur Note, ok même si la classe Note est abstraite
    Article* makeArticle();
    Tache* makeTache();
    Media* makeMedia();

    void setNoteId(Note* note, QString id){note->setId(id);}
    void setNoteTitle(Note * n, QString title){n->setTitre(title);}
    Note* getNote(const QString id); //récupérer n'importe quelle note, même archivée ou dans la corbeille
    Note& getNoteActuelle(const QString  id);
    void setDirectory(QString path){directory=path;}
    QString getDirectory(){return directory.path();}
    void pushToVersions(Note* note);

    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void setMediaDescription(QString d, Media*m){m->setDescription(d);}
    void setArticleText(Article*a,QString t){a->setText(t);}
    void setMediaPath(QString path, Media* m){m->setChemin(path);}
    void restaurerNote(const QString  id);
    void supprimerVersions(const QString  id);
    void archiverNote(Note* note){note->archiver();}
    void viderCorbeille();
    void save(Note *n, QString repertoire) const; //à faire !
    //void saveAll() const;
    QList<Note*> getActiveNotes(); //retourne la liste des notes actives
    QList<Note*> getArchiveNotes(); //retourne la liste des notes archivées
    QList<Tache*> getSortedTasks();
    void load();
    QVector<Note*> getVector(QString id);

public slots:

    void supprimerNoteActuelle(const QString  id);
};

#endif // NOTEMANAGER_H
