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

void Article::print() const {
    qDebug()<< "Article : " << getTitre() << "\n" << "texte:\n" << getTexte() << "\n";
}

void Tache::print() const {
    qDebug()<< "Tache : " << getTitre() << "\n" << "Action :\n" << getAction() << "\n" << "Priorite :\n" << getPriorite() << "\n" << "Statut :\n" << getStatut() << "\n";
    qDebug()<< "Echeance :\n";
    TIME::Date d = getEcheance();
    d.afficher();
}

void Media::print() const{
    qDebug()<< "Media :" << getDescription() << "\n" << "Chemin: \n" << getChemin() << "\n" << "TypeMedia: \n" << getTypeMedia() <<  "\n";
}


bool Tache::operator<(const Tache &tache) const{
    return (priorite < tache.getPriorite());
}

void Note::saveNote() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    stream.writeStartElement(getType());
    stream.writeTextElement("id",identificateur);
    stream.writeTextElement("title",titre);

    save(stream);

    stream.writeEndElement();
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();

    qDebug() <<"Note "<<identificateur<<" sauvegardee.";
}

void Article::save(QXmlStreamWriter & stream) const
{
    stream.writeTextElement("text", texte);
}

void Tache::save(QXmlStreamWriter & stream) const
{
    stream.writeTextElement("action", action);
    stream.writeTextElement("priorite", QVariant(priorite).toString());
    stream.writeTextElement("etat", QVariant(etat).toString());

}

void Media::save(QXmlStreamWriter & stream) const
{
    stream.writeTextElement("description", description);
    stream.writeTextElement("chemin", chemin);
}
