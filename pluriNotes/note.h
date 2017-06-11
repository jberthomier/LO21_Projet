#ifndef NOTE_H
#define NOTE_H

#include "date.h"

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
class NoteException{
private:
    QString info;
public:
    NoteException(const QString& message):info(message){}
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

    /**
     * \brief Permet d'éditer une note
     * \details La méthode est virtuel pure, elle n'est donc pas défini dans le classe mère Note mais dans les classes filles.
     * Cette méthode est privé pour ne permettre son exécution que par le biai de NoteManager.
     */
    virtual Note* edit() = 0;

    /**
     * \brief Classe amie
     * \details La classe NoteManager est déclaré comme étant amie de la classe Note.
     * Cela permet à NoteManager d'accéder aux méthodes de Note déclarées \a protected.
     * La plupart des méthodes de Note étant déclarées protected, cela assure que seul la class NoteManager est capable
     * d'effectuer des actions sur les objets de type Note.
     */
    friend class NoteManager;

protected:

    //Attributs
    QString identificateur;
    QString titre;
    TIME::Date dateCreation;
    TIME::Date dateDerniereModif;
    QString type;
    /**
     * \details Attribut booléen permettant de déterminer si une note est active ou archivée
     */
    bool active;
    /**
     * \details Attribut booléen permettant de déterminer si une note est dans la corbeille, c'est-à-dire une note
     * qui a été supprimée mais qui peut encore être restaurée.
     */
    bool corbeille;

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
    void setDdm(QDate d) {dateDerniereModif=d;}
    /**
     * \brief Accesseur en écriture de l'attribut active d'une note
     * \details Cette méthode est définie en protected afin que seules les classes filles et NoteManager puissent l'utiliser
     */
    void setActive(bool a) {active=a;}
    /**
     * \brief Accesseur en écriture de l'attribut corbeille d'une note
     * \details Cette méthode est définie en protected afin que seules les classes filles et NoteManager puissent l'utiliser
     */
    void setCorbeille(bool c) {corbeille=c;}

    //Méthodes
    /**
     * \brief Permet d'archiver une note
     * \details Pour archiver une note, on modifie uniquement l'attribut booléen active de la Note
     */
    void archiver() { active = false; }
    /**
     * \brief Permet de restaurer une note
     * \details On peut restaurer une note archivé ou une note de la corbeille. On modifie pour cela l'attribut booléen active de la Note et éventuellement l'attribut corbeille
     */
    void restaurer() { active = true; if (corbeille == true) corbeille = false; }
    /**
     * \brief Permet de supprimer une note
     * \details Pour supprimer une note, on modifie uniquement l'attribut booléen corbeille de la Note
     */
    void jeter() { corbeille = false; }
    /**
     * \brief Permet de modifier la date de dernière modification d'une note
     */
    void setDdm(TIME::Date d) { dateDerniereModif = d; }

public :
    //Constructeurs, destructeur et opérateur d'affectation
    /**
     * \brief Constructeur sans argument de Note
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
    const QString getType()const { return type; }

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
    QString type = "article";

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
    /**
     * \brief Permet d'éditer un article
     * \details Cette méthode est privé pour ne permettre son exécution que par le biai de NoteManager.
     */
    Article* edit();

    //Classe amie
    /**
     * \brief Classe amie
     */
    friend class NoteManager;

public:
    //Accesseur en lecture
    /**
     * \brief Accesseur en lecture du texte d'un article
     */
    QString getTexte() const {return texte;}

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
    QString type = "tache";

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
    /**
     * \brief Permet d'éditer une tâche
     * \details Cette méthode est privé pour ne permettre son exécution que par le biai de NoteManager
     */
    Tache* edit();

    //Classe amie
    /**
     * \brief Classe amie
     */
    friend class NoteManager;

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

    //Opérateur de comparaison de la priorité des taches
    /**
     * \brief Opérateur de comparaison de la priorité des tâches
     */
    bool operator<(const Tache &tache) const; //nécessaire pour permettre le tri des taches avec l'algorithme sort
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
     * \details Attribut permettant d'associer un état à une tache (cf #mType)
     */
    mType typeMedia;
    QString type = "media";

    //Constructeurs
    /**
     * \brief Constructeur sans argument de Tache
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
    Media();
    /**
     * \brief Constructeur de Tache
     * \details Le constructeur est dans la partie privée afin que seul NoteManager puisse créer un article
     */
     Media(QString id, const QString& t, TIME::Date dc, TIME::Date ddm, const QString& d, const QString& c, mType ty) : Note(id,t,dc,ddm), description(d), chemin(c), typeMedia(ty) {}
    /**
     * \brief Constructeur de recopie de Tache
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
     * \brief Accesseur en écriture de l'état d'une tache
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setChemin(QString c) { chemin = c;}
    /**
     * \brief Accesseur en écriture de l'état d'une tache
     * \details Cette méthode est définie en privé afin que seul NoteManager puisse l'utiliser
     */
    void setTypeMedia(mType m) { typeMedia = m;}

    //Méthode
    /**
     * \brief Permet d'éditer un média
     * \details Cette méthode est privé pour ne permettre son exécution que par le biai de NoteManager.
     */
    Media* edit();

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

};

#endif // NOTE_H
