#include <QApplication>
#include "couple.h"

using namespace std;

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    PluriNotes* win = new PluriNotes();
    win->show();
    return app.exec();
}
