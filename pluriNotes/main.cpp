#include <QApplication>
#include "couple.h"
#include "plurinotes.h"

using namespace std;

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    PluriNotes p;
    p.show();

    return app.exec();
}
