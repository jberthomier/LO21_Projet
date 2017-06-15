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

//Opérateur de comparaison des priorités des tâches
bool Tache::operator<(const Tache &tache) const{
  return (priorite < tache.getPriorite());
}

//Méthodes save
void Article::save(QXmlStreamWriter & stream) const{
    stream.writeTextElement("text", texte);
}

void Tache::save(QXmlStreamWriter & stream) const{
    stream.writeTextElement("action", action);
    stream.writeTextElement("priorite", QVariant(priorite).toString());
    stream.writeTextElement("etat", QVariant(etat).toString());

}

void Media::save(QXmlStreamWriter & stream) const{
    stream.writeTextElement("description", description);
    stream.writeTextElement("chemin", chemin);
}

//Méthode saveNote
void Article::saveNote(QString repertoire) const{
    QDir::setCurrent(repertoire);
    qDebug()<<"test6";
    QString filename = this->getTitre()+".xml";
    qDebug()<<"test7";
    QFile newfile(filename); //le nom du fichier correspond au titre de la note
    qDebug()<<"test7-1";
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
           throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
       qDebug()<<"test8";
       QDate ddm = QDate::currentDate();
       QString dateM = ddm.toString("dd/MM/yyyy");
       QString dateC = this->getDate().toString("dd/MM/yyyy");
       QXmlStreamWriter stream(&newfile);       
       stream.setAutoFormatting(true);
       stream.writeStartDocument();
       qDebug()<<"test9";
       stream.writeStartElement("Article");
       stream.writeTextElement("id",this->getId());       
       stream.writeTextElement("datecrea", dateC);
       stream.writeTextElement("datemodif", dateM);
       stream.writeTextElement("titre",this->getTitre());
       stream.writeTextElement("text", this->getTexte());
       stream.writeEndElement();
       qDebug()<<"test10";
       stream.writeEndDocument();
       qDebug()<<"test11";
       newfile.close();
       qDebug()<<"test12";

}

void Tache::saveNote(QString repertoire) const{
    QDir::setCurrent(repertoire);
    qDebug()<<"test6";
    QString filename = this->getTitre()+".xml";
    qDebug()<<"test7";
    QFile newfile(filename); //le nom du fichier correspond au titre de la note
       if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
           throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
       qDebug()<<"test8";

       QString datecrea = this->getDate().toString("dd/MM/yyyy");
       QDate ddm = QDate::currentDate();
       QString dateM = ddm.toString("dd/MM/yyyy");
       QString echeance = this->getEcheance().toString("dd/MM/yyyy");

       QString e;
       if (this->getStatut()==En_attente)
           e="En attente";
       if (this->getStatut()==En_cours)
           e="En cours";
       if (this->getStatut()==Terminee)
           e="Terminee";


       QString priorite = QString::number(this->getPriorite());

       QXmlStreamWriter stream(&newfile);
       stream.setAutoFormatting(true);
       stream.writeStartDocument();
       qDebug()<<"test9";
       stream.writeStartElement("Tache");
       stream.writeTextElement("datecrea",datecrea);
       stream.writeTextElement("datemodif", dateM);
       stream.writeTextElement("echeance", echeance);
       stream.writeTextElement("id",this->getId());
       stream.writeTextElement("titre",this->getTitre());
       stream.writeTextElement("action", getAction());
       stream.writeTextElement("etat", e);
       stream.writeTextElement("priorite",priorite);
       stream.writeEndElement();
       qDebug()<<"test10";
       stream.writeEndDocument();
       qDebug()<<"test11";
       newfile.close();
       qDebug()<<"test12";
}

void Media::saveNote(QString repertoire) const{
    QDir::setCurrent(repertoire);
    qDebug()<<"test6";
    QString filename = this->getTitre()+".xml";
    qDebug()<<"test7";
    QFile newfile(filename); //le nom du fichier correspond au titre de la note
    qDebug()<<"test7-1";
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
           throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
       qDebug()<<"test8";
       QDate ddm = QDate::currentDate();
       QString dateM = ddm.toString("dd/MM/yyyy");
       QString dateC = this->getDate().toString("dd/MM/yyyy");
       QXmlStreamWriter stream(&newfile);
       stream.setAutoFormatting(true);
       stream.writeStartDocument();
       qDebug()<<"test9";
       stream.writeStartElement("Media");
       stream.writeTextElement("id",this->getId());
       stream.writeTextElement("titre",this->getTitre());
       stream.writeTextElement("datecrea", dateC);
       stream.writeTextElement("datemodif", dateM);
       stream.writeTextElement("description",this->getDescription());
       stream.writeTextElement("Chemin", this->getFilename());
       stream.writeEndElement();
       qDebug()<<"test10";
       stream.writeEndDocument();
       qDebug()<<"test11";
       newfile.close();
       qDebug()<<"test12";
}