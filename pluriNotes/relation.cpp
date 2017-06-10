#include "couple.h"

//méthodes classe Relation

Relation::~Relation(){
    for (unsigned int i=0; i<nbCouples; i++){
        delete couples[i];
    }
    delete[] couples;
}

void Relation::getCouples() const {
    for (unsigned int i=0; i<nbCouples; i++){
        qDebug()<<"Label: "<<couples[i]->getLabel();
        if (orientation){
            qDebug()<<"Note source: "<<couples[i]->getNoteSource().getTitre()<<" Note destination: "<<couples[i]->getNoteDestination().getTitre()<<"\n";
        }
    }
}

void Relation::addCouple(const Note& ns, const Note& nd){
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getNoteSource().getTitre()==ns.getTitre() && couples[i]->getNoteDestination().getTitre()==nd.getTitre()){
            throw NotesException("Erreur: la relation entre ces deux notes existe déjà existe déjà.");
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
    bool res=false;
    for (unsigned int i=0; i<CoupleManager::instance->getNbCouples(); i++){
        if (CoupleManager::instance->couples[i]==&CoupleManager::instance->getCouple(ns,nd)){ //il existe déjà un couple entre ces deux notes
            res=true;
        }
    }
    if (res) couples[nbCouples]=&CoupleManager::instance->getCouple(ns,nd);
    else couples[nbCouples]=&CoupleManager::instance->getNewCouple("", ns, nd);
    nbCouples++;
    couples[nbCouples]->addRelation(this);
}

void Relation::removeCouple(Couple& c){
    for (unsigned int i=0; i<nbCouples; i++){
        if (couples[i]==&c){
            for (unsigned int j=i; j<nbCouples; j++){
                couples[j]=couples[j+1];
            }
            nbCouples--;
        }
    }
    c.removeRelation(this);
    if (c.nbRelations==0){
        CoupleManager::instance->deleteCouple(c);
    }
}

//méthodes privées classe RelationManager

RelationManager* RelationManager::instance=0;

RelationManager::RelationManager():relations(0), nbRelations(0), nbMaxRelations(){}

RelationManager::~RelationManager(){
    for (unsigned int i=0; i<nbRelations; i++){
        delete relations[i];
    }
    delete[] relations;
}

void RelationManager::addRelation (Relation* r){
    for (unsigned int i=0; i<nbRelations; i++){
        if (relations[i]->getTitre()==r->getTitre()){
            throw NotesException("Erreur: la relation existe déjà.");
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

//méthodes publiques classe RelationManager

RelationManager& RelationManager::getInstance(){
    if (instance==nullptr) {
        instance= new RelationManager();
    }
    return *instance;
}

void RelationManager::freeInstance(){
    if (instance!=nullptr) {delete instance;}
    else {instance=nullptr;}
}

void RelationManager::deleteRelation(Relation& r){
    for (unsigned int i=0; i<nbRelations; i++){
        if (relations[i]==&r){
            for (unsigned int j=i; j<nbRelations; j++){
                relations[j]=relations[j+1];
            }
            nbRelations--;
            delete &r;
        }
    }
}

const Relation& RelationManager::getNewRelation(const QString& t){
    Relation* r=new Relation(t,"");
    addRelation(r);
    return *r;
}

const Relation& RelationManager::getRelation(const QString& t) const{
    for (unsigned int i=0; i<nbRelations; i++){
        if (relations[i]->getTitre()==t){
            return *relations[i];
        }
    }
    throw NotesException("Erreur: il n'existe pas de relation avec ce titre.");
}

void RelationManager::visualiserRelation(const Relation& r)const{
    qDebug()<<"Titre: "<<r.getTitre()<<"\nDescription: "<<r.getDescription()<<"\nCouples: ";
    for (unsigned int i=0; i<r.getNbCouples(); i++){
        r.getCouples();
    }
}

bool RelationManager::noteReference(const Note& n, const QString& t){
    bool res=false;
    for (unsigned int i=0; i<getRelation(t).getNbCouples(); i++){
        if (getRelation(t).couples[i]->getNoteSource().getId()==n.getId() || getRelation(t).couples[i]->getNoteDestination().getId()==n.getId()){
            res=true;
        }
    }
    return res;
}
