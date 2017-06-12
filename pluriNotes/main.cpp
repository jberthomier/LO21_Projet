#include <QApplication>
#include "couple.h"
#include "plurinotes.h"

using namespace std;

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    PluriNotes p;
    //QDate date;
    //NoteManager& m= NoteManager::getInstance();
    //Article* n = new Article("1","test",date,date,"","");
    //ArticleEditeur* a= new ArticleEditeur(n);
    //a->show();
    p.show();
    return app.exec();
}
