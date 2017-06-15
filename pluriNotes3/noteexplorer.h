#ifndef NOTEEXPLORER_H
#define NOTEEXPLORER_H

#include "qwidget.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QHboxLayout>
#include <QFileDialog>
#include <iostream>
#include <QObject>
#include <QMessageBox>
#include "Note.h"

class NoteExplorer : public QWidget
{
    Q_OBJECT
public:
    NoteExplorer();
private:
    QListWidget* NoteList;
};

#endif // NOTEEXPLORER_H

