#ifndef RELATION_H
#define RELATION_H

class Couple;

class Relation {

protected:
    QString titre;
    QString description;
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    bool orientation;

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
    void getCouples(QDebug f) const; //récupérer tous les couples possédant une certaine relation

    //accesseurs en écriture
    void setTitre(const QString& t){titre=t;}
    void setDescription(const QString& d){description=d;}
    void setOrientation(bool o){orientation=o;}

    //ajouter et enlever un couple d'une relation
    void addCouple(const Note &ns, const Note &nd); //pour créer une relation entre deux éléments (cf document explication)
    void removeCouple(Couple& c); //enlever un couple d'une relation (cf document explication)

};

class Reference : public Relation {
private:
public:
    Reference(const QString& t, const QString& d): Relation(t, d){}
};

class RelationManager {

private:
    //attributs
    static RelationManager* instance;
    Relation** relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;

    //constructeurs, destructeur et opérateur d'affectation
    RelationManager();
    RelationManager(const RelationManager& rm); //ne pas implémenter pour ne pas avoir de copies du singleton
    virtual ~RelationManager();
    void operator=(const RelationManager& rm); //ne pas implémenter pour ne pas avoir de copies du singleton

    //méthodes
    void addRelation (Relation* r); //ajouter une relation a au tableau des relations

public:
    static RelationManager& getInstance(); //creer un instance unique RelationManager
    static void freeInstance(); //liberer l'instance RelationManager
    void deleteRelation(Relation& r); //supprimer une relation
    const Relation& getNewRelation(const QString& t); //creer une nouvelle relation

    //accesseur en lecture
    const Relation& getRelation(const QString& t)const; //recuperer une relation a l'aide de son titre

    //visualisation
    void visualiserRelation(const Relation& r, QDebug f)const;
};

#endif // RELATION_H
