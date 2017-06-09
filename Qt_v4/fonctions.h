#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "Visitor.h"

using namespace std;


/*
 * Visitor implementation containing security check algorithms.
 */
class Edit: public Visitor {
public:
    Edit();
    virtual ~Edit();
    void visit(Article*);
    void visit(Tache*);
    void visit(Media*);
};

class Print: public Visitor {

public:
    Print();
    virtual ~Print();
    void visit(Article*, QTextStream &f);
    void visit(Tache*);
    void visit(Media*);
};


class Save: public Visitor {

public:
    Save();
    virtual ~Save();
    void visit(Article*);
    void visit(Tache*);
    void visit(Media*);
};


#endif // FONCTIONS_H
