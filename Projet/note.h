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

    //MODIFICATION
    //ici aussi il faut ajouter les attributs active et corbeille puisque Article hérite de Note et car le constructeur de Note utilise ces attributs
    Article (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm, bool active=false, bool corbeille=false, std::string te) : Note(id,t,dc,ddm,active,corbeille), texte(te) {}
    std::string getTexte() {return texte;}

};

class Tache : public Note {
private :
    std::string action;
    unsigned int priorite;
    TIME::Date echeance;
    Statut etat;
public:

    Tache (unsigned int id, std:: string t, TIME::Date dc, TIME::Date ddm, bool active=false, bool corbeille=false std::string a,unsigned int p, TIME::Date e, Statut s) : Note(id,t,dc,ddm,active,corbeille), action (a), priorite(p), echeance(e), etat(s) {}
    std::string getAction()  {return action;}
    unsigned int getPriorite() {return priorite;}
    TIME::Date getEcheance() {return echeance;}
    Statut getStatut() {return etat;}
};


#endif // NOTE_H_INCLUDED
