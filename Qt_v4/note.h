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

class Couple {
private:
    QString label;
    const Note& noteSource;
    const Note& noteDestination;
public:
    Couple(const QString& l, const Note& n1, const Note& n2): label(l), noteSource(n1), noteDestination(n2){}
    const QString getLabel() const {return label;}
    const Note& getNoteSource() const {return noteSource;}
    const Note& getNoteDestination() const {return noteDestination;}
    void setLabel(const QString& l){label=l;}
};

class Relation {
protected:
    QString titre;
    QString description;
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    bool orientation;
public:
    Relation(const QString& t, const QString& d): titre(t), description(d), couples(nullptr), nbCouples(0), nbMaxCouples(0), orientation(true){}
    virtual ~Relation();
    const QString getTitre() const {return titre;}
    const QString getDescription() const {return description;}
    const QString getOrientation() const {
        if (orientation) return "Relation orientee";
        else return "Relation non orientee";
    }
    void getCouples(QDebug f) const {
        for (unsigned int i=0; i<nbCouples; i++){
            f<<"Label: "<<couples[i]->getLabel();
            if (orientation){
                f<<"Note source: "<<couples[i]->getNoteSource().getTitre()<<" Note destination: "<<couples[i]->getNoteDestination().getTitre()<<"\n";
            }
        }
    }
    void setTitre(const QString& t){titre=t;}
    void setDescription(const QString& d){description=d;}
    void setOrientation(bool o){orientation=o;}
    void addCouple(const Note &ns, const Note &nd); //pour créer une relation entre deux éléments d'un couple
    void removeCouple(Couple& c); //enlever un couple d'une relation
};

class Reference : public Relation {
private:
public:
    Reference(const QString& t, const QString& d): Relation(t, d){}
};

class CoupleManager {
private:
    static CoupleManager* instance;
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    CoupleManager();
    CoupleManager(const CoupleManager& cm);
    virtual ~CoupleManager();
    void operator=(const CoupleManager& cm);
    void addCouple(Couple *c);
    Couple& getNewCouple(const QString& t, const Note &ns, const Note &nd);
    void deleteCouple(Couple& c);
    friend void Relation::addCouple(const Note& ns, const Note& nd);
public:
    static CoupleManager& getInstance();
    static void freeInstance();
    unsigned int getNbCouples(){return nbCouples;}
    Couple& getCouple(const QString& t);
    Couple& getCouple(const Note &ns, const Note &nd);
    void arborescence(const Note& n, QDebug f); //visualiser l'arborescence des relations d'une note
    void afficherAscendants(const Note& n, QDebug f);
    void afficherDescendants(const Note& n, QDebug f);
};

class RelationManager {
private:
    static RelationManager* instance;
    Relation** relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    RelationManager();
    RelationManager(const RelationManager& rm); //ne pas implémenter pour ne pas avoir de copies du singleton
    virtual ~RelationManager();
    void operator=(const RelationManager& rm); //ne pas implémenter pour ne pas avoir de copies du singleton
    void addRelation (Relation* r); //ajouter une relation a l'ensemble des relations
public:
    static RelationManager& getInstance(); //creer un instance unique RelationManager
    static void freeInstance(); //liberer l'instance RelationManager
    void deleteRelation(Relation& r); //supprimer une relation
    const Relation& getNewRelation(const QString& t); //creer une nouvelle relation
    const Relation& getRelation(const QString& t); //recuperer une relation a l'aide de son titre
};

#endif // NOTE_H
