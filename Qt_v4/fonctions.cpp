#include "fonctions.h"
#include "notemanager.h"
#include <iostream>
#include<QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>


using namespace std;


Edit::Edit() {}

Edit::~Edit() {}

void Edit::visit(Article* a) {
    Article* newArticle = new Article(*this);
    this->Note::archiver();
    TIME::Date d;
    newArticle->setDdm(d);
    QString t;
    qtout<< "Entrez le nouveau texte : " << endl;
    qtin>> t;
    newArticle->setText(t);
    //return newArticle;
}

void Edit::visit(Tache* t) {
    QString a;
    unsigned int p, day, month, year;
    TIME::Date d_echeance(day,month,year);
    TIME::Date d; //date actuelle
    int e;

    Tache* newTask = new Tache(*this);
    this->archiver();
    newTask->setDdm(d);

    qtout<< "Entrez l'action de la tache : " << endl;
    qtin>> a;
    newTask->setAction(a);
    qtout<< "Entrez la priorite de la tache : " << endl;
    qtin>> p;
    newTask->setPriorite(p);

    qtout<< "Entrez le jour d'echeance de la tache : " << endl;
    qtin>> day;
    qtout<< "Entrez le mois d'echeance de la tache : " << endl;
    qtin>> month;
    qtout<< "Entrez l'annee d'echeance de la tache : " << endl;
    qtin>> year;
    d_echeance.setDate(day, month, year);
    newTask->setEcheance(d_echeance);

    qtout<< "Entrez le statut de la tache : " << endl;
    qtin>> e;
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
        qtout<< "Statut inconnu." << endl;
    }
    //return newTask;
}

void Edit::visit(Media* m) {
    //return this;
}


Print::Print() {}

Print::~Print() {}

void Print::visit(Article* a,QTextStream& f) {
    f<< "Article : " << Article::a->getTitre() << "\n" << "texte:\n" << Article::a->getTexte() << "\n";
}

void Print::visit(Tache* t,QTextStream& f) {
    f<< "Tache : " << t->getTitre() << "\n" << "Action :\n" << t->getAction() << "\n" << "Priorite :\n" << t->getPriorite() << "\n" << "Statut :\n" << t->getStatut() << "\n";
    f<< "Echeance :\n";
    TIME::Date d = t->getEcheance();
    d.afficher(f);
}

void Print::visit(Media* m,QTextStream& f) {
    f<< "Media :" << m->getDescription() << "\n" << "Chemin: \n" << m->getChemin() << "\n" << "TypeMedia: \n" << getTypeMedia() <<  "\n";
}

Save::Save() {}
Save::~Save() {}

void Save::visit(Article *a){
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for (QVector<QVector<Note>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2)
        {
        stream.writeStartElement("note");
        stream.writeTextElement("id",(*ite2).getId());
        stream.writeTextElement("titre",(*ite2).getTitre());
        stream.writeTextElement("texte",(*ite2).getTexte());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
    }
}

