#ifndef PluriNotes_H
#define PluriNotes_H

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QListWidget>
#include "Note.h"
#include <QDirIterator>
#include "NoteManager.h"
#include "ui_PluriNotes.h"


class PluriNotes : public QMainWindow
{
    Q_OBJECT

public:
    PluriNotes(QWidget *parent = 0);
    virtual ~PluriNotes();
    //void loadSettings();

private:
    Ui::Plurinotes ui;
    //void closeEvent(QCloseEvent *event);

    QString FilePath;

public slots :
    //void openSettings();
    //void ouvrirNote(QListWidgetItem *item);
    //void nouvelleNote();
    void updateActiveNotes();
    void updateArchiveNotes();
    void updateSortedTasks();
private slots:

};

#endif // PluriNotes_H
