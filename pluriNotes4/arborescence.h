#ifndef ARBORESCENCE_H
#define ARBORESCENCE_H

#include<QWidget>
#include<QTreeWidget>
#include<QTreeView>
#include<QLabel>
#include<QLayout>
#include<QList>
#include<QPushButton>

#include"Note.h"

class Arborescence : public QWidget{

    Q_OBJECT

public:

	//Constructeur
    Arborescence(Note& note, QWidget *parent = 0);

	
	//Accesseurs en lecture
    QTreeWidget* getDescendants() {return descendants; }
    QTreeWidget* getAscendants() {return ascendants; }

    QPushButton* getButtonAsc() {return button_asc; }
    QPushButton* getButtonDesc() {return button_desc; }

private:

	//Attributd
    QVBoxLayout *couche;

    QHBoxLayout *label_hbox;
    QLabel *id_label;
    QLabel *titre_label;

    QHBoxLayout *button_layout;
    QPushButton *button_asc;
    QPushButton *button_desc;

    QTreeWidget *descendants;
    QTreeWidget *ascendants;

    QList<QString> id_asc;
    QList<QString> id_dsc;

    QList<QString> id_asc_root;
    QList<QString> id_dsc_root;

	//Accesseurs en écriture
    void setAscendantsRacine(Note& note);
    void setAscendants(QString id, QTreeWidgetItem* tree);
    void setDescendantsRacine(Note& note);
    void setDescendants(QString id, QTreeWidgetItem* tree);

	//Méthodes
    QTreeWidgetItem* addRoot(QTreeWidget * parent, QString nom);
    QTreeWidgetItem* addChild(QTreeWidgetItem * parent, QString nom);

public slots:

};


#endif // ARBORESCENCE_H
