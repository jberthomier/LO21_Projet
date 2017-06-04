#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include "date.h"

using namespace std;

enum Statut {En_attente, En_cours, Terminee};
enum mType {image,audio,video};

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Note {
protected:
    unsigned int identificateur;
    QString titre;
    TIME::Date dateCreation;
    TIME::Date dateDerniereModif;
    bool active;
    bool corbeille;
    list<list<Note>> versions;
public :
    Note (unsigned int id, const QString& t, TIME::Date dc, TIME::Date ddm) : identificateur(id),titre(t), dateCreation(dc), dateDerniereModif(ddm), active(false), corbeille(false) {}
    virtual ~Note();
    unsigned int getId() const {return identificateur;}
    QString getTitre() const {return titre;}
    TIME::Date getDate() const {return dateCreation;}
    TIME::Date getDateM() const {return dateDerniereModif;}
    void setTitre(const QString& t){titre=t;}
    void setActive(bool a){active=a;}
    void setCorbeille(bool c){corbeille=c;}
};

class NoteManager {
private:
    static NoteManager* instance;
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    NoteManager();
    NoteManager(const NoteManager& nm);
    virtual ~NoteManager();
    void operator=(const NoteManager& nm);
    void addNote (Note* n);
public:
    static NoteManager& getInstance();
    static void freeInstance();
    void deleteNote(Note& n);
    const Note& getNewNote(const unsigned int id);
    const Note& getNote(const unsigned int id);
};

class Article : public Note {
private :
    QString texte;
public:
    //MODIFICATION
    //ici aussi il faut ajouter les attributs active et corbeille puisque Article hérite de Note et car le constructeur de Note utilise ces attributs
    Article (unsigned int id, const QString& t, TIME::Date dc, TIME::Date ddm, const QString& te) : Note(id,t,dc,ddm), texte(te) {}
    QString getTexte() const {return texte;}

};

class Tache : public Note {
private :
    QString action;
    unsigned int priorite;
    TIME::Date echeance;
    Statut etat;
public:
    Tache (unsigned int id, const QString& t, TIME::Date dc, TIME::Date ddm, unsigned int p, TIME::Date e, Statut s, const QString& a) : Note(id,t,dc,ddm), action (a), priorite(p), echeance(e), etat(s) {}
    QString getAction()  const {return action;}
    unsigned int getPriorite() const {return priorite;}
    TIME::Date getEcheance() const {return echeance;}
    Statut getStatut() const {return etat;}
};

class Media : public Note {
private :
    QString description;
    QString chemin;
    mType typeMedia;
public :
    Media(unsigned int id, const QString& t, TIME::Date dc, TIME::Date ddm, const QString& d, const QString& c, mType ty) : Note(id,t,dc,ddm), description(d), chemin(c), typeMedia(ty) {}
    const QString getDescription() const {return description;}
    const QString getChemin() const {return chemin;}
    mType getTypeMedia() const {return typeMedia;}
};

#endif // NOTE_H
