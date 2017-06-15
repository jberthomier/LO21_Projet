#ifndef NOTE_H
#define NOTE_H

#include "date.h"

#include <QTextCodec>
#include <QtXml>
#include <QDate>

using namespace std;

/**
 * \brief Enumération pour spécifier l'état d'une tâche
 */

enum Statut {En_attente, En_cours, Terminee};

/**
 * \brief Enumération pour spécifier le type d'un média
 */

enum mType {image,audio,video};

/*------------------------------------------------Gestion des Exceptions------------------------------------------------------*/

/**
 * \brief Exception pour les notes
 */
class NotesException{
private:
    QString info;
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

/**
 * \brief Exception pour l'archivage des notes
 */
class ArchiveException {
private:
    QString info;
public:
    ArchiveException(const QString& message) : info(message) {}
    const QString getInfo() const { return info; }
};

/*------------------------------------------------Classe Note-----------------------------------------------------*/

/**
 * \details Classe mère de la classe Article, Tache et Media.
 * C'est une classe \b abstraite. En effet, il est seulement possible de créer un article, une tâche ou un média.
 * Elle possède pour cela une fonctions virtuelle pure, une fonction d'édition de note (Note::edit).
 */
class Note {

private:

	//Attributs
    QString identificateur;
    QString titre;
	/**
	 * \details Nom du fichier dans lequel on veut sauvegarder notre note
	 */
	QString filename;
    TIME::Date dateCreation;
    TIME::Date dateDerniereModif;
    /**
     * \details Attribut booléen permettant de déterminer si une note est active ou archivée
     */
    bool active;
    /**
     * \details Attribut booléen permettant de déterminer si une note est dans la corbeille, c'est-à-dire une note
     * qui a été supprimée mais qui peut encore être restaurée.
     */
    bool corbeille;
	
	//Méthode
	/**
     * \brief Méthode pour sauvegarder les attributs spécifiques à chaque type de note
		\details La classe Note étant abstraire, cette méthode n'est pas défini pour Note, c'est une méthode virtuelle pure.
     */
	virtual void save(QXmlStreamWriter& stream) const = 0;

	//Classes amies
    /**
     * \brief Classe amie
     * \details La classe NoteManager est déclaré comme étant amie de la classe Note.
     * Cela permet à NoteManager d'accéder aux méthodes de Note déclarées \a protected.
     * La plupart des méthodes de Note étant déclarées protected, cela assure que seules les classes amie, ici la classe NoteManager est capable
     * d'effectuer des actions sur les objets de type Note.
     */
    friend class NoteManager;
	/**
     * \brief Classe amie
     * \details La classe NoteEditeur est déclaré comme étant amie de la classe Note.
     * Cela permet à NoteManager d'accéder aux méthodes de Note déclarées \a protected.
     * La plupart des méthodes de Note étant déclarées protected, cela assure que seules les classes amie, ici la classe NoteManager, est capable
     * d'effectuer des actions sur les objets de type Note.
     */
	friend class NoteEditeur;
	/**
     * \brief Classe amie
     * \details La classe NoteEditeur est déclaré comme étant amie de la classe Note.
     * Cela permet à NoteManager d'accéder aux méthodes de Note déclarées \a protected.
     * La plupart des méthodes de Note étant déclarées protected, cela assure que seules les classes amie, ici la classe NoteManager, est capable
     * d'effectuer des actions sur les objets de type Note.
     */
	friend class FenetreCouple;
	/**
     * \brief Classe amie
     * \details La classe NoteEditeur est déclaré comme étant amie de la classe Note.
     * Cela permet à NoteManager d'accéder aux méthodes de Note déclarées \a protected.
     * La plupart des méthodes de Note étant déclarées protected, cela assure que seules les classes amie, ici la classe NoteManager, est capable
     * d'effectuer des actions sur les objets de type Note.
     */
    friend class VoirRelations;
	/**
     * \brief Classe amie
     * \details La classe NoteEditeur est déclaré comme étant amie de la classe Note.
     * Cela permet à NoteManager d'accéder aux méthodes de Note déclarées \a protected.
     * La plupart des méthodes de Note étant déclarées protected, cela assure que seules les classes amie, ici la classe NoteManager, est capable
     * d'effectuer des actions sur les objets de type Note.
     */
    friend class Arborescence;

protected:
	
	//Constructeurs, destructeur et opérateur d'affectation
    /**
     * \brief Constructeur sans argument de Note
	 * \details Le constructeur est dans la partie protected afin que seul NoteManager et les classes filles de Note puissent y accéder
     */
    Note();
    /**
     * \brief Constructeur de Note
     */
    Note (QString id, const QString& t, TIME::Date dc, TIME::Date ddm) : identificateur(id),titre(t), dateCreation(dc), dateDerniereModif(ddm), active(false), corbeille(false) {}
    /**
     * \brief Constructeur de recopie de Note
     */
    Note(const Note& n) : identificateur(n.identificateur), titre(n.titre), dateCreation(n.dateCreation), dateDerniereModif(n.dateDerniereModif), active(n.active), corbeille(n.corbeille) {}
    /**
     * \brief Opérateur d'affectation de Note
     */
    Note& operator=(Note const& note);
    /**
     * \brief Destructeur de note
     * \details Le destructeur est sensé être virtuel pour respecter le principe de substitution.
     * Cependant nous avons eu des erreurs à la compilation donc nous avons décidé de l'enlever.
     */
    ~Note();

    //Accesseurs en écriture
    /**
     * \brief Accesseur en écriture du titre d'une note
     * \details Cette méthode est définie en protected afin que seules les classes filles et NoteManager puissent l'utiliser
     */
    void setTitre(QString& t) {titre=t;}
    /**
     * \brief Accesseur en écriture de la date de dernière modification d'une note
     * \details Cette méthode est définie en protected afin que seules les classes filles et NoteManager puissent l'utiliser
     */
	void setDdm(TIME::Date d) {dateDerniereModif = d;}
    /**
     * \brief Accesseur en écriture de l'attribut active d'une note
     * \details Cette méthode est définie en protected afin que seules les classes filles et NoteManager puissent l'utiliser
     */
    //void setActive(bool a) {active=a;}
    /**
     * \brief Accesseur en écriture de l'attribut corbeille d'une note
     * \details Cette méthode est définie en protected afin que seules les classes filles et NoteManager puissent l'utiliser
     */
    //void setCorbeille(bool c) {corbeille=c;}
	/**
     * \brief Accesseur en écriture du nom du fichier pour stocker les notes 
     * \details Cette méthode est définie en protected afin que seules les classes filles et NoteManager puissent l'utiliser
     */
	void setFilename(const QString& f) { filename=f; }
	
	void setId(QString id) {identificateur=id;}

    //Méthodes
    /**
     * \brief Permet d'archiver une note
     * \details Pour archiver une note, on modifie uniquement l'attribut booléen active de la note
     */
    void archiver() { active = false; }
    /**
     * \brief Permet de restaurer une note
     * \details On peut restaurer une note archivé ou une note de la corbeille. On modifie pour cela l'attribut booléen active de la note et éventuellement l'attribut corbeille
     */
    void restaurer() { active = true; if (corbeille == true) corbeille = false; }
    /**
     * \brief Permet de supprimer une note
     * \details Pour supprimer une note, on modifie uniquement l'attribut booléen corbeille de la Note
     */
    void jeter() { corbeille = false; }

public :

    //Accesseurs en lecture
    /**
     * \brief Accesseur en lecture de l'identificateur d'une note
     */
    QString getId() const {return identificateur;}
    /**
     * \brief Accesseur en lecture du titre d'une note
     */
    QString getTitre() const {return titre;}
    /**
     * \brief Accesseur en lecture de la date de création d'une note
     */
    TIME::Date getDate() const {return dateCreation;}
	/**
     * \brief Accesseur en lecture du nom du fichier permettant de stocker les notes
     */
	QString getFilename() const { return filename; }
    /**
     * \brief Accesseur en lecture de la date de dernière modification d'une note
     */
    TIME::Date getDateM() const {return dateDerniereModif;}
    /**
     * \brief Accesseur en lecture pour savoir si une note est active ou archivée
     */
    bool isActive() const { return active; }
    /**
     * \brief Accesseur en lecture pour savoir si une note est dans la corbeille ou pas
     */
    bool inCorbeille() const { return corbeille; }
    /**
     * \brief Accesseur en lecture du type de note
     */
    virtual const QString getType()const =0;
	
	//Méthode
	//void saveNote() const;

};

/*------------------------------------------------Classe Article-----------------------------------------------------*/

/**
 * \details Classe fille héritant de la classe Note.
 * Les articles sont des notes qui possèdent en plus un attribut texte
 */
class Article : public Note {

private :

    //Attribut
    QString texte;

    //Contructeurs
    /**
     * \brief Constructeur sans argument de Article
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
    Article();
    /**
     * \brief Constructeur de Article
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
    Article (QString id, const QString& t, TIME::Date dc, TIME::Date ddm, const QString& te) : Note(id,t,dc,ddm), texte(te) {}
    /**
     * \brief Constructeur de recopie de Article
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
    Article(const Article& a) : Note(a), texte(a.texte) {}

    //Accesseur en écriture
    /**
     * \brief Accesseur en écriture du texte d'un article
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setText(QString t) {texte = t;}

	//Méthode
	void saveNote(QString repertoire) const;
	
    //Classe amie
    /**
     * \brief Classe amie
     */
    friend class NoteManager;
	/**
     * \brief Classe amie
     */
	friend class ArticleEditeur;

public:
    //Accesseur en lecture
    /**
     * \brief Accesseur en lecture du texte d'un article
     */
    QString getTexte() const {return texte;}
	
	const QString getType()const {return QString("article");}
	
	//Méthode
	/**
     * \brief Méthode pour sauvegarder les attributs spécifiques à chaque type de note 
     */
	void save(QXmlStreamWriter& stream) const;

};

/*------------------------------------------------Classe Tache-----------------------------------------------------*/

/**
 * \details Classe fille héritant de la classe Note.
 * Les tâches sont des notes qui possèdent en plus un attribut action permettant de décrire la tâche à effectuer,
 * un attribut priorité optionnel, un date d'échéance et un état (cf #Statut)
 */
class Tache : public Note {

private :

    //Attributs
    /**
     * \details Attribut décrivant l'action à effectuer pour la tâche
     */
    QString action;
    /**
     * \details Attribut permettant d'associer une tâche à une éventuelle priorité
     */
    unsigned int priorite;
    /**
     * \details Attribut permettant de déterminer une éventuelle date à laquelle la tâche doit être terminée
     */
    TIME::Date echeance;
    /**
     * \details Attribut permettant d'associer un état à une tâche (cf #Statut)
     */
    Statut etat;

    //Constructeurs
    /**
     * \brief Constructeur sans argument de Tache
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer une tâche
     */
    Tache();
    /**
     * \brief Constructeur de Tache
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer une tâche
     */
    Tache(QString id, const QString& t, TIME::Date dc, TIME::Date ddm, unsigned int p, TIME::Date e, Statut s, const QString& a) : Note(id,t,dc,ddm), action (a), priorite(p), echeance(e), etat(s) {}
    /**
     * \brief Constructeur de recopie de Tache
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer une tâche
     */
    Tache(const Tache& t) : Note(t), action(t.action), priorite(t.priorite), echeance(t.echeance), etat(t.etat) {}

    //Accesseurs en écriture
    /**
     * \brief Accesseur en écriture de l'action d'une tâche
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setAction(QString a) { action = a;}
    /**
     * \brief Accesseur en écriture de la priorité d'une tâche
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setPriorite(unsigned int p) { priorite = p;}
    /**
     * \brief Accesseur en écriture de la date d'échéance d'une tâche
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setEcheance(TIME::Date d) { echeance = d;}
    /**
     * \brief Accesseur en écriture de l'état d'une tâche
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setEtat(Statut e) { etat = e;}

    //Méthode
	void saveNote(QString repertoire) const;

    //Classe amie
    /**
     * \brief Classe amie
     */
    friend class NoteManager;
	friend class PluriNotes;
	friend class TacheEditeur;

public:
    //Accesseurs en lecture
    /**
     * \brief Accesseur en lecture de l'action d'une tâche
     */
    QString getAction() const {return action;}
    /**
     * \brief Accesseur en lecture de la priorité d'une tâche
     */
    unsigned int getPriorite() const {return priorite;}
    /**
     * \brief Accesseur en lecture de la date d'échéance d'une tâche
     */
    TIME::Date getEcheance() const {return echeance;}
    /**
     * \brief Accesseur en lecture de l'état d'une tâche
     */
    Statut getStatut() const {return etat;}
	/**
     * \brief Accesseur en lecture du type de la note
     */
	const QString getType()const {return QString("tache");}

    //Opérateur de comparaison de la priorité des taches
    /**
     * \brief Opérateur de comparaison de la priorité des tâches
     */
    bool operator<(const Tache &tache) const; //nécessaire pour permettre le tri des taches avec l'algorithme sort
	
	//Méthode
	/**
     * \brief Méthode pour sauvegarder les attributs spécifiques à chaque type de note 
     */
	void save(QXmlStreamWriter& stream) const;
};

/*------------------------------------------------Classe Media-----------------------------------------------------*/

/**
 * \details Classe fille héritant de la classe Note.
 * Les médias sont des notes qui possèdent en plus un attribut description, un chemin où se trouve le média et un type (cf #mType)
 */
class Media : public Note {

private :

    //Attributs
    QString description;
    /**
     * \details Attribut spécifiant le chemin d'accès au média
     */
    QString chemin;
    /**
     * \details Attribut permettant d'associer un type de média à un objet de type Media (cf #mType)
     */
    mType typeMedia;

    //Constructeurs
    /**
     * \brief Constructeur sans argument de Media
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
    Media();
    /**
     * \brief Constructeur de Media
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
     Media(QString id, const QString& t, TIME::Date dc, TIME::Date ddm, const QString& d, const QString& c, mType ty) : Note(id,t,dc,ddm), description(d), chemin(c), typeMedia(ty) {}
    /**
     * \brief Constructeur de recopie de Media
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
    Media(const Media& m) : Note(m), description(m.description), chemin(m.chemin), typeMedia(m.typeMedia) {}

    //Accesseurs en écriture
    /**
     * \brief Accesseur en écriture de la description d'un média
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setDescription(QString d) { description = d;}
    /**
     * \brief Accesseur en écriture du chemin d'un média
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setChemin(QString c) { chemin = c;}
    /**
     * \brief Accesseur en écriture du type d'un média
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setTypeMedia(mType m) { typeMedia = m;}

    //Méthode
	void saveNote(QString repertoire) const;
	
    //Classe amie
    /**
     * \brief Classe amie
     */
    friend class NoteManager;

public :
    //Accesseurs en lecture
    /**
     * \brief Accesseur en lecture de la description d'un média
     */
    const QString getDescription() const {return description;}
    /**
     * \brief Accesseur en lecture du chemin permettant d'accéder au média
     */
    const QString getChemin() const {return chemin;}
    /**
     * \brief Accesseur en lecture du type de média
     */
    mType getTypeMedia() const {return typeMedia;}
	
	const QString getType()const {return QString("media");}
	
	//Méthode
	/**
     * \brief Méthode pour sauvegarder les attributs spécifiques à chaque type de note 
     */
	void save(QXmlStreamWriter& stream) const;

};

#endif // NOTE_H
