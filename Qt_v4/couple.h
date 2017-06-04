#ifndef COUPLE_H
#define COUPLE_H

#include "note.h"
#include "relation.h"

class Couple {

private:
    //attributs
    QString label;
    const Note& noteSource;
    const Note& noteDestination;
    Relation** relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;

    //méthodes
    void addRelation(Relation* r);
    void removeRelation(Relation* r);

    //méthodes amies
    friend void Relation::addCouple(const Note& ns, const Note& nd);
    friend void Relation::removeCouple(Couple& c);

public:
    //constructeur
    Couple(const QString& l, const Note& n1, const Note& n2): label(l), noteSource(n1), noteDestination(n2){}

    //accesseurs en lecture
    const QString getLabel() const {return label;}
    const Note& getNoteSource() const {return noteSource;}
    const Note& getNoteDestination() const {return noteDestination;}
    void getRelations()const{ //récupérer toutes les relations mises en place pour un couple de notes
        for (unsigned int i=0; i<nbRelations; i++){
            qtout<<"Label: "<<relations[i]->getTitre();
        }
    }

    //accesseur en écriture
    void setLabel(const QString& l){label=l;}

};

class CoupleManager {

private:
    //attributs
    static CoupleManager* instance;
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;

    //constructeurs, destructeur et opérateur d'affectation
    CoupleManager();
    CoupleManager(const CoupleManager& cm);
    virtual ~CoupleManager();
    void operator=(const CoupleManager& cm);

    //méthodes
    Couple& getNewCouple(const QString& t, const Note &ns, const Note &nd);
    void addCouple(Couple *c);
    void deleteCouple(Couple& c);

    //méthodes amies
    friend void Relation::addCouple(const Note& ns, const Note& nd);
    friend void Relation::removeCouple(Couple& c);

public:
    static CoupleManager& getInstance();
    static void freeInstance();

    //accesseur en écriture
    unsigned int getNbCouples()const {return nbCouples;}
    Couple& getCouple(const QString& t)const;
    Couple& getCouple(const Note &ns, const Note &nd) const;

    //visualisation
    void arborescence(const Note& n); //visualiser l'arborescence des relations d'une note
    void afficherAscendants(const Note& n);
    void afficherDescendants(const Note& n);

};

#endif // COUPLE_H
