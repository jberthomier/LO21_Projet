#ifndef VISITOR_H
#define VISITOR_H

#include "note.h"


using namespace std;

/*
 * Interface for the implementation that contains the functional algorithms.
 */

class Visitor {
public:
    virtual ~Visitor();
    virtual void visit(Article*) =0;
    virtual void visit(Tache*) =0;
    virtual void visit(Media*) =0;

protected:
    Visitor();
};


#endif // VISITOR_H
