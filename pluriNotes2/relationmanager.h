#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

class Relation;

class RelationManager {

private:
    //Attributs
    static RelationManager* instance;
    Relation** relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    QDir directory;
	
    //Constructeurs, destructeur et opérateur d'affectation
    RelationManager();
    RelationManager(const RelationManager& rm); //ne pas implémenter pour ne pas avoir de copies du singleton
    virtual ~RelationManager();
    void operator=(const RelationManager& rm); //ne pas implémenter pour ne pas avoir de copies du singleton

    //Méthodes
    void addRelation (Relation* r); //ajouter une relation a au tableau des relations

public:

    static RelationManager& getInstance(); //creer un instance unique RelationManager
    static void freeInstance(); //liberer l'instance RelationManager
    void deleteRelation(Relation& r); //supprimer une relation
    const Relation& getNewRelation(const QString& t); //creer une nouvelle relation

    //Accesseur en lecture
    const Relation& getRelation(const QString& t)const; //recuperer une relation a l'aide de son titre
	QDir getDirectory() const {return directory;}
	
	//Accesseur en écriture
    void setDirectory(const QString d) { directory = d;}
	
    //Visualisation
    void visualiserRelation(const Relation& r)const;

    //Pour savoir si une note est référencé
    bool noteReference(const Note& n, const QString& t);

	bool existRelation(const QString& t) const;
	
	class Iterator {
        public:
            Relation* operator *(){return *current;}

            Relation* operator ++(){
                if(last == 0)
                    throw NotesException(QString("Erreur, arrive au bout."));
                --last;
                return *(++current);
            }
            Relation* operator ++(int){
                if(last == 0)
                    throw NotesException(QString("Erreur, arrive au bout."));
                Relation* save = *current;
                ++current;
                --last;
                return save;
            }
        bool isdone(){return last == 0;}
        private:
            Relation** current;
            unsigned int last;
            friend class RelationManager;
            Iterator(Relation** _tab, unsigned int _nb_max): current(_tab), last(_nb_max) {}
        };
    Iterator getIterator() {
            return Iterator(relations, nbRelations);
   }
   
};

#endif // RELATIONMANAGER_H
