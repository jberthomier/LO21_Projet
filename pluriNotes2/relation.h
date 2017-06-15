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
    bool getOri() const {return orientation;}
    void getCouples() const; //récupérer tous les couples possédant une certaine relation
    Couple getCouples(QString x, QString y) const;

    //accesseurs en écriture
    void setTitre(const QString& t){titre=t;}
    void setDescription(const QString& d){description=d;}
    void setOrientation(bool o){orientation=o;}

    //ajouter et enlever un couple d'une relation
    void addCouple(const Note &ns, const Note &nd,QString label); //pour créer une relation entre deux éléments (cf document explication)
    void removeCouple(Couple& c); //enlever un couple d'une relation (cf document explication)

    class Iterator {
        public:

            Couple* operator *(){return *current;}

            Couple* operator ++(){
                if(last == 0)
                    throw NotesException(QString("Erreur, arrive au bout."));
                --last;
                return *(++current);
            }

            Couple* operator ++(int){
                if(last == 0)
                    throw NotesException(QString("Erreur, arrive au bout."));
                Couple* save = *current;
                ++current;
                --last;
                return save;
            }

            bool isdone(){return last == 0;}
        private:
            Couple** current; /*!< pointeur sur le couple courant */
            unsigned int last; /*!< nombre de couples restant à parcourir */
            friend class Relation;

            Iterator(Couple** _tab, unsigned int _nb_max): current(_tab), last(_nb_max) {}
        };
        Iterator getIterator() {
            return Iterator(couples, nbCouples);
        }

};

#endif // RELATION_H
