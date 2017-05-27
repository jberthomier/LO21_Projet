#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include "date.h"

using namespace std;

enum Statut {En_attente, En_cours, Terminee};
enum mType {image,audio,video};

class Note {
protected:
    unsigned int identificateur;
    QString titre;
    TIME::Date dateCreation;
    TIME::Date dateDerniereModif;
    bool active;
    bool corbeille;
public :
    Note (unsigned int id, QString t, TIME::Date dc, TIME::Date ddm) : identificateur(id),titre(t), dateCreation(dc), dateDerniereModif(ddm), active(false), corbeille(false) {}
    virtual ~Note();
    unsigned int getId() const {return identificateur;}
    QString getTitre() const {return titre;}
    TIME::Date getDate() const {return dateCreation;}
    TIME::Date getDateM() const {return dateDerniereModif;}
};

class Article : public Note {
private :
    QString texte;
public:
    //MODIFICATION
    //ici aussi il faut ajouter les attributs active et corbeille puisque Article hérite de Note et car le constructeur de Note utilise ces attributs
    Article (unsigned int id, QString t, TIME::Date dc, TIME::Date ddm, QString te) : Note(id,t,dc,ddm), texte(te) {}
    QString getTexte() const {return texte;}

};

class Tache : public Note {
private :
    QString action;
    unsigned int priorite;
    TIME::Date echeance;
    Statut etat;
public:
    Tache (unsigned int id, QString t, TIME::Date dc, TIME::Date ddm, unsigned int p, TIME::Date e, Statut s, QString a) : Note(id,t,dc,ddm), action (a), priorite(p), echeance(e), etat(s) {}
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
    Media(unsigned int id, QString t, TIME::Date dc, TIME::Date ddm, QString d, QString c, mType ty) : Note(id,t,dc,ddm), description(d), chemin(c), typeMedia(ty) {}
    QString getDescription() const {return description;}
    QString getChemin() const {return chemin;}
    mType getTypeMedia() const {return typeMedia;}
};

class Couple {
private:
    QString label;
    const Note& noteSource;
    const Note& noteDestination;
public:
    Couple(const QString& l, const Note& n1, const Note& n2): label(l), noteSource(n1), noteDestination(n2){}
    ~Couple();
    QString getLabel() const {return label;}
    const Note& getNoteSource() const {return noteSource;}
    const Note& getNoteDestination() const {return noteDestination;}
    Couple& editLabel(Couple& c);
};

class Relation {
protected:
    QString titre;
    QString description;
    Couple** ensembleCouples;
    bool orientation;
public:
    Relation(const QString& t, const QString& d): titre(t), description(d), ensembleCouples(0), orientation(true){}
    virtual ~Relation();
    QString getTitre() const {return titre;}
    QString getDescription() const {return description;}
    QString getOrientation() const {
        if (orientation) return "Relation orientee";
        else return "Relation non orientee";
    }
    void setTitre(const QString& t);
    void setDescription(const QString& d);
    void setOrientation(bool o);
};

class Reference : public Relation {
private:
public:
    Reference(const QString& t, const QString& d): Relation(t, d){}
    ~Reference(){printf("La relation reference ne peut pas être supprime!");}
};

class RelationManager {
private:
    RelationManager& instance;
    Relation** ensembleRelations;
    RelationManager();
    RelationManager(const RelationManager& rm);
    ~RelationManager();
    RelationManager& operator=(const RelationManager& rm);
    void addRelation (Relation& r); //ajouter une relation a l'ensemble des relations
public:
    static RelationManager& getInstance(); //creer un instance unique RelationManager
    static void freeInstance(); //liberer l'instance RelationManager
    void deleteRelation(Relation& r); //supprimer un relation
    void addCouple(Couple& c, Relation& r); //ajouter un couple dans une relation
    void removeCouple(Couple& c, Relation& r); //enlever un couple d'une relation
    Relation& getNewRelation(const QString& t); //creer une nouvelle relation
    Relation& getRelation(const QString& t); //recuperer une relation a l'aide de son titre
    void arborescence(const Note& n); //visualiser l'arborescence des relations d'une note
};

#endif // NOTE_H
