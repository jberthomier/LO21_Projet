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
#include "affichagenote.h"


class PluriNotes : public QMainWindow
{
    Q_OBJECT

public:
    PluriNotes(QWidget *parent = 0);
    virtual ~PluriNotes();

private:
    Ui::Plurinotes ui;

    QString FilePath;



public slots :
    void ouvrirNote(QListWidgetItem *item);

    void newArticle();
    void newTache();
    void newMedia();
    void getChemin(QListWidgetItem *id);

    void updateActiveNotes();
    void updateArchiveNotes();
    void updateSortedTasks();
private slots:

};

#endif // PluriNotes_H
