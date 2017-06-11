#include "note.h"

using namespace std;

/*------------------------------------------------------Méthodes de la classe Note-------------------------------------------------------*/

Note& Note::operator=(Note const& note) {
    if (this != &note) {
        identificateur = note.identificateur;
        titre = note.titre;
        dateCreation = note.dateCreation;
        dateDerniereModif = note.dateDerniereModif;
        active = note.active;
        corbeille = note.corbeille;
    }
    return *this;
}

/*------------------------------------------------------Méthodes des classes filles-------------------------------------------------------*/

Article* Article::edit(){
    Article* newArticle = new Article(*this);
    this->archiver();
    TIME::Date d;
    newArticle->setDdm(d);
    QString t;
    qDebug()<< "Entrez le nouveau texte : " << endl;
    //qtin>> t;
    newArticle->setText(t);
    return newArticle;
}

Tache* Tache::edit() {
    QString a;
    unsigned int p, day, month, year;
    TIME::Date d_echeance(day,month,year);
    TIME::Date d; //date actuelle
    int e;

    Tache* newTask = new Tache(*this);
    this->archiver();
    newTask->setDdm(d);

    qDebug()<< "Entrez l'action de la tache : " << endl;
    //qtin>> a;
    newTask->setAction(a);
    qDebug()<< "Entrez la priorite de la tache : " << endl;
    //qtin>> p;
    newTask->setPriorite(p);

    qDebug()<< "Entrez le jour d'echeance de la tache : " << endl;
    //qtin>> day;
    qDebug()<< "Entrez le mois d'echeance de la tache : " << endl;
    //qtin>> month;
    qDebug()<< "Entrez l'annee d'echeance de la tache : " << endl;
    //qtin>> year;
    d_echeance.setDate(day, month, year);
    newTask->setEcheance(d_echeance);

    qDebug()<< "Entrez le statut de la tache : " << endl;
    //qtin>> e;
    switch (e) {
    case 0:
        newTask->setEtat(En_attente);
        break;
    case 1:
        newTask->setEtat(En_cours);
        break;
    case 2:
        newTask->setEtat(Terminee);
        break;
    default:
        qDebug()<< "Statut inconnu." << endl;
    }
    return newTask;
}

Media* Media::edit(){
    return this;
}

bool Tache::operator<(const Tache &tache) const{
  return (priorite < tache.getPriorite());
}
