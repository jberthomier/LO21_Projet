#include <QApplication>
#include "couple.h"
#include "plurinotes.h"
#include "iostream"
#include <qDebug>


using namespace std;

int main(int argc, char* argv[]){

    //attention maintenant getNote retourne un pointeur sur une note au lieu d'une référence (quelques changements à effectuer
    //dans le reste des fonctions

   /*
    Article* a1=m.makeArticle();

    a1->setText("Je suis un article");

    Article* a2=m.makeArticle();
    m.archiverNote(a2);
    Article* a3=m.makeArticle();
    m.archiverNote(a3);

    QString id = a1->getId();
    Note* a1_bis = m.getNote(id);

    QList<Note*>ActiveNotes;
    QList<Note*>ArchiveNotes;

    ActiveNotes = m.getActiveNotes();
    ArchiveNotes = m.getArchiveNotes();*/

    /*for (QVector<QVector<Note*>>::iterator ite = versions.begin(); ite != versions.end(); ++ite) {
        for (QVector<Note*>::iterator ite2 = (*ite).begin(); ite2 != (*ite).end(); ++ite2) {
            QString idNote = (*ite2)->getId();
            qDebug(idNote);
        }
     }*/

    NoteManager& m= NoteManager::getInstance();
    QDate date = QDate::currentDate();

    Article* a1=m.makeArticle();

    a1->setTitre("Un article");
    a1->setText("Je suis un article");

    Article* a2=m.makeArticle();
    m.archiverNote(a2);
    m.pushToVersions(a2);

    Article* a3=m.makeArticle();
    m.archiverNote(a3);
    m.pushToVersions(a3);


    QApplication app(argc, argv);
    PluriNotes p;
    p.show();
    return app.exec();


}
