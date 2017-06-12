#ifndef NOTE_H
#define NOTE_H

#include "date.h"

#include <QTextCodec>
#include <QtXml>

using namespace std;

enum Statut {En_attente, En_cours, Terminee};
enum mType {image,audio,video};

/*------------------------------------------------Gestion des Exceptions------------------------------------------------------*/

class NotesException{
private:
    QString info;
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

class ArchiveException {
private:
    QString info;
public:
    ArchiveException(const QString& message) : info(message) {}
    const QString getInfo() const { return info; }
};

/*------------------------------------------------Note et ses classes filles-----------------------------------------------------*/

class Note { //Classe abstraite

private:
    QString identificateur;
    QString titre;
    QString filename;
    TIME::Date dateCreation;
    TIME::Date dateDerniereModif;
    bool active;
    bool corbeille;

    //Méthode Edit virtuelle pure à définir dans chaque classe fille. On la met en privé car seul NoteManager pourra utiliser cette méthode.
    virtual Note* edit() = 0;
    virtual void save(QXmlStreamWriter& stream) const = 0;

    friend class NoteManager;
    friend class NoteEditeur;


protected:
    //Méthodes Set en protected afin que seules les classes filles et NoteManager puissent les utiliser
    void archiver() { active = false; }
    void restaurer() { active = true; if (corbeille == true) corbeille = false; }
    void jeter() {}
    void setDdm(TIME::Date d) { dateDerniereModif = d; }

public :
    //Constructeurs et destructeur
    Note();
    Note (QString id, const QString& t, TIME::Date dc, TIME::Date ddm,QString f) : identificateur(id),titre(t), dateCreation(dc), dateDerniereModif(ddm),filename(f), active(false), corbeille(false) {}
    Note(const Note& n) : identificateur(n.identificateur), titre(n.titre), dateCreation(n.dateCreation), dateDerniereModif(n.dateDerniereModif), active(n.active), corbeille(n.corbeille) {}
    Note& operator=(Note const& note);

    //Le destructeur doit être virtuel pour respecter le principe de substitution.
    ~Note();

    //Accesseurs en lecture
    QString getId() const {return identificateur;}
    QString getTitre() const {return titre;}
    TIME::Date getDate() const {return dateCreation;}
    TIME::Date getDateM() const {return dateDerniereModif;}
    bool isActive() const { return active; }
    bool inCorbeille() const { return corbeille; }

    void setTitre(const QString& t) {titre = t;}

    //Méthode d'affichage virtuelle pure à définir dans les classes filles
    virtual void print() const = 0;
    void saveNote() const;

    virtual QString getType() const =0;
};

class Article : public Note {

private :
    QString texte;

    //Le constructeur est dans la partie privée afin que seul le NoteManager puisse créer un article.
    Article();
    Article (QString id, const QString& t, TIME::Date dc, TIME::Date ddm,QString f, const QString& te) : Note(id,t,dc,ddm,f), texte(te) {}
    Article(const Article& a) : Note(a), texte(a.texte) {}
    friend class NoteManager;

    //Accesseur en écriture

    Article* edit();
    friend class ArticleEditeur;

public:
    //Accesseur en lecture
    QString getTexte() const {return texte;}

    void setText(QString t) {texte = t;}

    //Définition de la méthode d'affichage
    void print() const;
    void save(QXmlStreamWriter& stream) const;
    QString getType() const {return QString("article");}

};

class Tache : public Note {

    friend class TacheEditeur;

private :
    Tache();
    Tache(QString id, const QString& t, TIME::Date dc, TIME::Date ddm,QString f, unsigned int p, TIME::Date e, Statut s, const QString& a) : Note(id,t,dc,ddm,f), action (a), priorite(p), echeance(e), etat(s) {}
    Tache(const Tache& t) : Note(t), action(t.action), priorite(t.priorite), echeance(t.echeance), etat(t.etat) {}
    friend class NoteManager;
    QString action;
    unsigned int priorite;
    TIME::Date echeance;
    Statut etat;
    Tache* edit();

    //Accesseurs en écriture
    void setAction(QString a) { action = a;}
    void setPriorite(unsigned int p) { priorite = p;}
    void setEcheance(TIME::Date d) { echeance = d;}
    void setEtat(Statut e) { etat = e;}

public:
    //Accesseurs en lecture
    QString getAction() const {return action;}
    unsigned int getPriorite() const {return priorite;}
    TIME::Date getEcheance() const {return echeance;}
    Statut getStatut() const {return etat;}

    //Définition de la méthode d'affichage
    void print() const;
    void save(QXmlStreamWriter& stream) const;
    QString getType() const {return QString("tache");}
    bool operator<(const Tache &tache) const; //nécessaire pour permettre le tri des taches avec l'algorithme sort
};

class Media : public Note {

private :
    Media();
    Media(QString id, const QString& t, TIME::Date dc, TIME::Date ddm,QString f, const QString& d, const QString& c, mType ty) : Note(id,t,dc,ddm,f), description(d), chemin(c), typeMedia(ty) {}
    Media(const Media& m) : Note(m), description(m.description), chemin(m.chemin), typeMedia(m.typeMedia) {}
    friend class NoteManager;
    QString description;
    QString chemin;
    mType typeMedia;
    Media* edit();

    //Accesseurs en écriture
    void setDescription(QString d) { description = d;}
    void setChemin(QString c) { chemin = c;}
    void setTypeMedia(mType m) { typeMedia = m;}

public :
    //Accesseurs en lecture
    const QString getDescription() const {return description;}
    const QString getChemin() const {return chemin;}
    mType getTypeMedia() const {return typeMedia;}

    //Définition de la méthode d'affichage
    void print() const;
    void save(QXmlStreamWriter& stream) const;
    QString getType() const {return QString("media");}

};

#endif // NOTE_H
