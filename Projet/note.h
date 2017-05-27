#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED

#include <iostream>
#include <string>
#include <stdio.h>
#include "date.h"

enum Statut {En_attente, En_cours, Terminee};
enum mType{image,audio,video};

class Note {
protected: //protected car héritage non ?
    unsigned int identificateur;
    std::string titre;
    TIME::Date dateCreation;
    TIME::Date dateDerniereModif;
    bool active;
    bool corbeille;
public :
    Note (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm,bool active,bool corbeille) : identificateur(id),titre(t), dateCreation(dc), dateDerniereModif(ddm),active(false),corbeille(false) {} //le constructeur ne doit pas être virtuel
    virtual ~Note(); //par contre pour le destructeur c'est mieux je crois
    unsigned int getId() const {return identificateur;}
    std::string getTitre() const {return titre;}
    TIME::Date getDate() const {return dateCreation;}
    TIME::Date getDateM() const {return dateDerniereModif;}
};

class Article : public Note {
private :
    std::string texte;
public:
    //MODIFICATION
    //ici aussi il faut ajouter les attributs active et corbeille puisque Article hérite de Note et car le constructeur de Note utilise ces attributs
    Article (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm,std::string te, bool active=false, bool corbeille=false) : Note(id,t,dc,ddm,active,corbeille), texte(te) {}
    std::string getTexte() const {return texte;}

};

class Tache : public Note {
private :
    std::string action;
    unsigned int priorite;
    TIME::Date echeance;
    Statut etat;
public:
    Tache (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm,unsigned int p, TIME::Date e, Statut s, std::string a, bool active=false, bool corbeille=false) : Note(id,t,dc,ddm,active,corbeille), action (a), priorite(p), echeance(e), etat(s) {}
    std::string getAction()  const {return action;}
    unsigned int getPriorite() const {return priorite;}
    TIME::Date getEcheance() const {return echeance;}
    Statut getStatut() const {return etat;}
};

class Media : public Note {
private :
    std::string description;
    std::string chemin;
    mType typeMedia;
public :
    Media(unsigned int id, std::string t, TIME::Date dc, TIME::Date ddm, std::string d, std::string c, mType ty, bool active=false, bool corbeille=false) : Note(id,t,dc,ddm,active,corbeille), description(d), chemin(c), typeMedia(ty) {}
    std::string getDescription() const {return description;}
    std::string getChemin() const {return chemin;}
    mType getTypeMedia() const {return typeMedia;}
};

class Couple {
private:
    std::string label;
    const Note& noteSource;
    const Note& noteDestination;
public:
    Couple(const std::string& l, const Note& n1, const Note& n2): label(l), noteSource(n1), noteDestination(n2){}
    ~Couple();
    std::string getLabel() const {return label;}
    const Note& getNoteSource() const {return noteSource;}
    const Note& getNoteDestination() const {return noteDestination;}
    Couple& editLabel(Couple& c);
};

class Relation {
protected:
    std::string titre;
    std::string description;
    Couple** ensembleCouples;
    bool orientation;
public:
    Relation(const std::string& t, const std::string& d, bool o): titre(t), description(d), orientation(true), ensembleCouples(0){}
    virtual ~Relation();
    std::string getTitre() const {return titre;}
    std::string getDescription() const {return description;}
    std::string getOrientation() const {
        if (orientation) return "Relation orientee";
        else return "Relation non orientee";
    }
    void setTitre(const std::string& t);
	void setDescription(const std::string& d);
	void setOrientation(bool o);
};

class Reference : public Relation {
private:
public:
    Reference(const std::string& t, const std::string& d, bool o): Relation(t, d, o){}
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
    Relation& getNewRelation(const std::string& t); //creer une nouvelle relation
    Relation& getRelation(const std::string& t); //recuperer une relation a l'aide de son titre
    void arborescence(const Note& n); //visualiser l'arborescence des relations d'une note
};

#endif // NOTE_H_INCLUDED
