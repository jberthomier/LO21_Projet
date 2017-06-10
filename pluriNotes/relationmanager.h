#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

class Relation;

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
    void visualiserRelation(const Relation& r)const;

    //pour savoir si une note est référencé
    bool noteReference(const Note& n, const QString& t);
};

#endif // RELATIONMANAGER_H
