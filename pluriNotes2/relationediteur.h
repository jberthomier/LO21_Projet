#ifndef RELATIONEDITEUR_H
#define RELATIONEDITEUR_H

#include "qwidget.h"
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
#include <notemanager.h>
#include "relation.h"
#include "relationmanager.h"

class RelationEditeur : public QWidget
{

    Q_OBJECT
private :



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
    RelationEditeur(QWidget* parent=0);
    RelationEditeur(Relation* r,QWidget* parent=0);
    QPushButton* getButtonCreate() {return button_create;}
    //QPushButton* getButtonDelete() {return button_delete;}
    QPushButton* getButtonClose() {return button_close;}
    QLineEdit* getTitre() {return titre;}
    ~RelationEditeur();

public slots:
    void create();
    void save();
    //void deleteRelation();
};

class ExplorationRelations : public QWidget {
    Q_OBJECT

public:
    ExplorationRelations(QWidget* parent=0);
    QPushButton* getButtonSuppr() {return button_suppr;}
    QListWidget* getListe() {return liste;}

private:
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
    FenetreCouple(Relation* r, QWidget* parent=0);
    QPushButton* getButtonCreate() {return button_create;}

private:
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
    void save();

};


class VoirRelations : public QWidget {
    Q_OBJECT

public:
    VoirRelations(QWidget* parent=0);
    QPushButton* getButtonDeletion() {return button_deletion;}
    QListWidget* getListeCouple() {return liste_couples;}
    void afficherCouplesR(QString relation);

private:
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
    void afficherCouples();
    void CoupleEditer();
    void saveLabel();
    void SupprimerCouple();
    void activeDelete();

};

#endif // RELATIONEDITEUR_H
