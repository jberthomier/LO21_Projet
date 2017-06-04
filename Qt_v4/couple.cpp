#include "couple.h"

//méthodes class Couple

void Couple::addRelation(Relation* r){
    for (unsigned int i=0; i<nbRelations; i++){
        if (relations[i]->getTitre()==r->getTitre()){
            throw NotesException("Erreur: la relation entre ces deux notes existe déjà existe déjà.");
        }
    }
    if (nbRelations==nbMaxRelations){
        Relation** newRelations=new Relation*[nbMaxRelations+10];
        for (unsigned int i=0; i<nbRelations; i++){
            newRelations[i]=relations[i];
        }
        Relation** oldRelations=relations;
        relations=newRelations;
        nbMaxRelations+=10;
        if (oldRelations){
            delete[] oldRelations;
        }
    }
    relations[nbRelations]=r;
    nbRelations++;
}

void Couple::removeRelation(Relation* r){
    for (unsigned int i=0; i<nbRelations; i++){
        if (relations[i]==r){
            for (unsigned int j=i; j<nbRelations; j++){
                relations[j]=relations[j+1];
            }
            nbRelations--;
        }
    }
}

//méthodes privées class CoupleManager

CoupleManager* CoupleManager::instance=0;

CoupleManager::CoupleManager():couples(nullptr), nbCouples(0), nbMaxCouples(0) {}

CoupleManager::~CoupleManager(){
    for (unsigned int i=0; i<nbCouples; i++){
        delete couples[i];
    }
    delete[] couples;
}

void CoupleManager::addCouple(Couple* c){
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getLabel()==c->getLabel()){
            throw NotesException("Erreur: la relation existe déjà.");
        }
    }
    if (nbCouples==nbMaxCouples){
        Couple** newCouples=new Couple*[nbMaxCouples+10];
        for (unsigned int i=0; i<nbCouples; i++){
            newCouples[i]=couples[i];
        }
        Couple** oldCouples=couples;
        couples=newCouples;
        nbMaxCouples+=10;
        if (oldCouples){
            delete[] oldCouples;
        }
    }
    couples[nbCouples]=c;
    nbCouples++;
}

void CoupleManager::deleteCouple(Couple& c){
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]==&c){
            for (unsigned int j=i; j<nbCouples; j++){
                couples[j]=couples[j+1];
            }
            nbCouples--;
            delete &c;
        }
    }
}

//méthodes publiques class CoupleManager

CoupleManager& CoupleManager::getInstance(){
    if (instance==nullptr) {
        instance= new CoupleManager();
    }
    return *instance;
}

void CoupleManager::freeInstance(){
    if (instance!=nullptr) {delete instance;}
    else {instance=nullptr;}
}

Couple& CoupleManager::getNewCouple(const QString& t, const Note& ns, const Note& nd){
    Couple* c=new Couple(t, ns, nd);
    addCouple(c);
    return *c;
}

Couple& CoupleManager::getCouple(const QString& l)const{
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getLabel()==l){
            return *couples[i];
        }
    }
    throw NotesException("Erreur: il n'existe pas de relation avec ce titre.");
}

Couple& CoupleManager::getCouple(const Note &ns, const Note &nd)const{
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getNoteSource().getTitre()==ns.getTitre() && couples[i]->getNoteDestination().getTitre()==nd.getTitre()){
            return *couples[i];
        }
    }
    throw NotesException("Erreur: il n'existe pas de relation entre ces deux notes.");
}

void CoupleManager::afficherAscendants(const Note& n, QDebug f){
    f<<"Ascendants: ";
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getNoteDestination().getTitre()==n.getTitre()){
            f<<couples[i]->getNoteSource().getTitre();
        }
    }
}

void CoupleManager::afficherDescendants(const Note& n, QDebug f){
    f<<"Descendants: ";
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getNoteSource().getTitre()==n.getTitre()){
            f<<couples[i]->getNoteDestination().getTitre();
        }
    }
}

void CoupleManager::arborescence(const Note& n, QDebug f){
    afficherAscendants(n,f);
    afficherDescendants(n, f);
}
