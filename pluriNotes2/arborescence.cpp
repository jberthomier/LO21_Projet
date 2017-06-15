#include "arborescence.h"
#include "note.h"
#include "relation.h"
#include "notemanager.h"

/*------------------------------------------------------Méthodes publiques de la classe Arborescence-------------------------------------------------------*/

Arborescence::Arborescence(Note& note, QWidget *parent): QWidget(parent)
{

    couche = new QVBoxLayout;

    label_hbox = new QHBoxLayout;
    id_label = new QLabel(note.getId());
    titre_label = new QLabel(note.getTitre());

    label_hbox->addWidget(id_label);
    label_hbox->addWidget(titre_label);

    ascendants = new QTreeWidget;
    setAscendantsRacine(note);
    ascendants->setHeaderLabel("ascendants");

    descendants = new QTreeWidget;
    setDescendantsRacine(note);
    descendants->setHeaderLabel("descendants");

    button_layout = new QHBoxLayout;
    button_asc = new QPushButton("Ascendant");
    button_desc = new QPushButton("Descendant");

    button_layout->addWidget(button_asc);
    button_layout->addWidget(button_desc);

    couche->addWidget(ascendants);
    couche->addLayout(label_hbox);
    couche->addWidget(descendants);
    couche->addLayout(button_layout);


    this->setLayout(couche);
}

/*------------------------------------------------------Méthodes privées de la classe Arborescence-------------------------------------------------------*/

/*------------------------------------------------------Accesseurs en écriture-------------------------------------------------------*/

void Arborescence::setAscendantsRacine(Note& note){
    NoteManager& m = NoteManager::getInstance();
    RelationManager& rm = RelationManager::getInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = rm.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            QString n1 = cpl->getNoteDestination().getId();
            QString n2 = cpl->getNoteSource().getId();
            QString n3 = cpl->getNoteDestination().getTitre();
            QString n4 = cpl->getNoteSource().getTitre();
            if(n1==note.getId() && !id_asc_root.contains(n2)){
                if((m.getNote(n4)->active == true )){
                    id_asc_root.append(n2);
                    setAscendants( n4, addRoot(ascendants, n4) );
                }
            }
        }
    }
}

void Arborescence::setAscendants(QString id, QTreeWidgetItem* tree){
    id_asc.append(id);
    NoteManager& m = NoteManager::getInstance();
    RelationManager& rm = RelationManager::getInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = rm.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            QString n1 = cpl->getNoteDestination().getId();
            QString n2 = cpl->getNoteSource().getId();
            QString n3 = cpl->getNoteDestination().getTitre();
            QString n4 = cpl->getNoteSource().getTitre();
            if(n1==id && !id_asc.contains(n2)){
                if((m.getNote(n4)->active==true)){
                    setAscendants(n4, addChild(tree,n4) );
                }
            }
        }
    }
}

void Arborescence::setDescendantsRacine(Note& note){
    NoteManager& m = NoteManager::getInstance();
    RelationManager& rm = RelationManager::getInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = rm.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            QString n1 = cpl->getNoteDestination().getId();
            QString n2 = cpl->getNoteSource().getId();
            QString n3 = cpl->getNoteDestination().getTitre();
            QString n4 = cpl->getNoteSource().getTitre();
            if(n2==note.getId() && !id_asc_root.contains(n1)){
                if((m.getNote(n3)->active == true )){
                    id_asc_root.append(n1);
                    setDescendants( n3, addRoot(descendants, n3) );
                }
            }
        }
    }
}

void Arborescence::setDescendants(QString id, QTreeWidgetItem* tree){
    id_dsc.append(id);
    NoteManager& m = NoteManager::getInstance();
    RelationManager& rm = RelationManager::getInstance();
    Relation* rel;
    Couple* cpl;

    for( RelationManager::Iterator r_it = rm.getIterator() ; !r_it.isdone() ; r_it++)
    {
        rel = *r_it;

        for( Relation::Iterator c_it = rel->getIterator() ; !c_it.isdone() ; c_it++)
        {
            cpl = *c_it;
            QString n1 = cpl->getNoteDestination().getId();
            QString n2 = cpl->getNoteSource().getId();
            QString n3 = cpl->getNoteDestination().getTitre();
            QString n4 = cpl->getNoteSource().getTitre();
            if(n2==id && !id_asc.contains(n1)){
                if((m.getNote(n3)->active==true)){
                    setDescendants(n3, addChild(tree, n3));
                }
            }
        }
    }
}

/*------------------------------------------------------Méthodes-------------------------------------------------------*/

QTreeWidgetItem* Arborescence::addRoot(QTreeWidget *parent, QString nom){
    QTreeWidgetItem* itm = new QTreeWidgetItem(parent);
    itm->setText(0, nom);

    parent->addTopLevelItem(itm);
    return itm;
}

QTreeWidgetItem* Arborescence::addChild(QTreeWidgetItem *parent, QString nom){
    QTreeWidgetItem* itm = new QTreeWidgetItem(parent);
    itm->setText(0, nom);

    parent->addChild(itm);
    return itm;
}
