#ifndef RELATIONEDITEUR_H
#define RELATIONEDITEUR_H

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QHboxLayout>
#include <QFileDialog>
#include <iostream>
#include <QObject>
#include <QMessageBox>
#include <QComboBox>
#include <QListWidget>
#include <QCheckBox>

#include "Note.h"
#include "notemanager.h"
#include "relation.h"
#include "relationmanager.h"
#include "qwidget.h"

class RelationEditeur : public QWidget
{
    Q_OBJECT
	
private :

	//Attributs
    QVBoxLayout* couche;
    QHBoxLayout* crel;
    QHBoxLayout* cdesc;
    QHBoxLayout* buttons;

    QPushButton* button_create;
    QPushButton* button_close;
    QPushButton* button_save;
    //QPushButton* button_delete;

    QLabel* rel1;
    QLabel* description1;

    QLineEdit* titre;
    QTextEdit* description;

    QList<QString> tab_id_x;
    QList<QString> tab_id_y;

    QCheckBox* orientation;

    QString ancienTitre;

public:

	//Constructeurs et destructeur
    RelationEditeur(QWidget* parent=0);
    RelationEditeur(Relation* r,QWidget* parent=0);
	~RelationEditeur();
	
	//Accesseurs en lecture
    QPushButton* getButtonCreate() {return button_create;}
    //QPushButton* getButtonDelete() {return button_delete;}
    QPushButton* getButtonClose() {return button_close;}
    QLineEdit* getTitre() {return titre;}


public slots:

	//Méthodes
    void create();
    void save();
    //void deleteRelation();
};

class ExplorationRelations : public QWidget {
    Q_OBJECT

public:

	//Consctructeur
    ExplorationRelations(QWidget* parent=0);
	
	//Accesseurs en lecture
    QPushButton* getButtonSuppr() {return button_suppr;}
    QListWidget* getListe() {return liste;}

private:

	//Attributs
    QVBoxLayout* couche;
    QHBoxLayout* buttons;

    QLabel* titre;

    QListWidget* liste;
    QPushButton* button_close;
    QPushButton* button_suppr;

};

class FenetreCouple: public QWidget {
    Q_OBJECT

public:

	//Consctructeur
    FenetreCouple(Relation* r, QWidget* parent=0);
	
	//Accesseurs en lecture
    QPushButton* getButtonCreate() {return button_create;}

private:

	//Attributs
    QVBoxLayout* couche;
    QHBoxLayout* notes;
    QHBoxLayout* buttons;

    QLabel* titreR;
    QLabel* titreC;

    QLineEdit* couple;

    QList<QString> tab_id_x;
    QList<QString> tab_id_y;

    QListWidget* liste_x;
    QListWidget* liste_y;

    QPushButton* button_create;

public slots:

	//Méthodes
    void save();

};


class VoirRelations : public QWidget {
    Q_OBJECT

public:

	//Consctructeur
    VoirRelations(QWidget* parent=0);
	
	//Accesseurs en lecture
    QPushButton* getButtonDeletion() {return button_deletion;}
    QListWidget* getListeCouple() {return liste_couples;}
	
	//Méthodes
    void afficherCouplesR(QString relation);

private:

	//Attributs
    QVBoxLayout* couche;
    QHBoxLayout* buttons;
    QHBoxLayout* notes;

    QLabel* label1;
    QLineEdit* label;

    QComboBox* rel;

    QListWidget* liste_couples;

    QPushButton* button_deletion;
    QPushButton* button_close;
    QPushButton* save_label;

public slots:

	//Méthodes
    void afficherCouples();
    void CoupleEditer();
    void saveLabel();
    void SupprimerCouple();
    void activeDelete();

};

#endif // RELATIONEDITEUR_H
