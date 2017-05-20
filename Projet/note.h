#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED

#include <iostream>
#include <string>
#include "date.h"

enum Statut {En_attente, En_cours, Terminee};

class Note {
private:
    unsigned int identificateur;
    std::string titre;
    TIME::Date dateCreation;
    TIME::Date dateDerniereModif;
    bool active;
    bool corbeille;
public :
    Note (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm,bool active=false,bool corbeille=false) : identificateur(id),titre(t), dateCreation(dc), dateDerniereModif(ddm),active(false),corbeille(false) {}
    ~Note();
    unsigned int getId() const {return identificateur;}
    std::string getTitre() const {return titre;}
    TIME::Date getDate() const {return dateCreation;}
    TIME::Date getDateM() const {return dateDerniereModif;}
};

class Article : public Note {
private :
    std::string texte;
public:
    Article (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm, std::string te) : Note(id,t,dc,ddm), texte(te) {}
    std::string getTexte() const {return texte;}
};

class Tache : public Note {
private :
    std::string action;
    unsigned int priorite;
    TIME::Date echeance;
    Statut etat;
public:
    Tache (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm, std::string a,unsigned int p, TIME::Date e, Statut s) : Note(id,t,dc,ddm), action (a), priorite(p), echeance(e), etat(s) {}
    std::string getAction() const {return action;}
    unsigned int getPriorite() const {return priorite;}
    TIME::Date getEcheance() const {return echeance;}
    Statut getStatut() const {return etat;}

};


#endif // NOTE_H_INCLUDED
