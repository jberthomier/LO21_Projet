#ifndef AFFICHAGENOTE_H
#define AFFICHAGENOTE_H

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
#include <QDirIterator>
#include "articleediteur.h"
#include "tacheediteur.h"
#include "mediaediteur.h"
#include "noteediteur.h"



namespace Ui {
class AffichageNote;
}

class AffichageNote : public QWidget
{
    Q_OBJECT

public:
    explicit AffichageNote(QWidget *parent = 0);
    void afficheNote(Note* note);
    void afficheArticle(Article* article);
    void afficheTache(Tache* tache);
    void afficheMedia(Media* media);
    void fermeNote(const QString& id);
    void refreshNote(const QString& id);
    bool ouverte(const QString& id);
    ~AffichageNote();

private:
    QHBoxLayout*layout;
    QTabWidget* tabWidget;
    void fermeTab(int);
    ArticleEditeur* createArticleEditeur(Note* n);
    NoteEditeur* AffichageNote::createEditeur(Note* n);

public slots :
    void unsavedChanges(NoteEditeur* e);
    void savedChanges(NoteEditeur* e);
};

#endif // AFFICHAGENOTE_H
