#ifndef RELATION_H
#define RELATION_H

#include "relationmanager.h"
class Couple;

class Relation {

private:
    QString titre;
    QString description;
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    bool orientation;
    friend bool RelationManager::noteReference(const Note& n, const QString& t);

public:
    //constructeur et destructeur
    Relation(const QString& t, const QString& d): titre(t), description(d), couples(nullptr), nbCouples(0), nbMaxCouples(0), orientation(true){}
    virtual ~Relation();

    //accesseurs en lecture
    const QString getTitre() const {return titre;}
    const QString getDescription() const {return description;}
    unsigned int getNbCouples() const {return nbCouples;}
    const QString getOrientation() const {
        if (orientation) return "Relation orientee";
        else return "Relation non orientee";
    }
    void getCouples() const; //récupérer tous les couples possédant une certaine relation

    //accesseurs en écriture
    void setTitre(const QString& t){titre=t;}
    void setDescription(const QString& d){description=d;}
    void setOrientation(bool o){orientation=o;}

    //ajouter et enlever un couple d'une relation
    void addCouple(const Note &ns, const Note &nd); //pour créer une relation entre deux éléments (cf document explication)
    void removeCouple(Couple& c); //enlever un couple d'une relation (cf document explication)

};

#endif // RELATION_H
