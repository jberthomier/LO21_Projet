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

class AffichageNote : public QWidget {
    
	Q_OBJECT

private:

	//Attributs
    QHBoxLayout*layout;
    QTabWidget* tabWidget;
	
	//Méthodes
    void fermeTab(int);
    NoteEditeur* createEditeur(Note* n);
	ArticleEditeur* createArticleEditeur(Note* n);	
	
public:

	//Constructeur et destructeur
    explicit AffichageNote(QWidget *parent = 0);
	~AffichageNote();

	
	//Méthodes
	void afficheNote(Note* note);
	void afficheArticle(Article* article);
    void afficheTache(Tache* tache);
    void afficheMedia(Media* media);
    void fermeNote(const QString& id);
    void refreshNote(const QString& id);
    bool ouverte(const QString& id);
 
public slots :

    void unsavedChanges(NoteEditeur* e);
    void savedChanges(NoteEditeur* e);
	
};

#endif // AFFICHAGENOTE_H
