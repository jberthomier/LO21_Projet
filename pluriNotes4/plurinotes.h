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
#include <QDirIterator>
#include <QHBoxLayout>

#include "Note.h"
#include "NoteManager.h"
#include "ui_PluriNotes.h"
#include "affichagenote.h"
#include "relationediteur.h"
#include "arborescence.h"


class PluriNotes : public QMainWindow
{
    Q_OBJECT

public:

	//Constructeur et destructeur
    PluriNotes(QWidget *parent = 0);
    virtual ~PluriNotes();
	
	//Méthode
	void loadSettings();

private:

	//Attributs
    Ui::Plurinotes ui;
    QString FilePath;
	QHBoxLayout* centralLayout;
    QString m_sSettingsFile;
    ExplorationRelations* window_exploration;
    RelationEditeur* window_relation;
    FenetreCouple* window_couple;
    VoirRelations* window_voir;
    Arborescence* arbo;


public slots :

	//Accesseur en lecture
	void getChemin(QListWidgetItem *id);

	//Méthodes
    void ouvrirNote(QListWidgetItem *item);
	
	void newArticle();
    void newTache();
    void newMedia();
	
    void updateActiveNotes();
    void updateArchiveNotes();
    void updateSortedTasks();
	
	void CreationRelation();
    void ParcoursRelation();
    void OuvertureCouple();
    void VisualisationRelation();

    void OuvrirRelation();

    void ouvrir_arbo();
    void ouvre_note_desc();
    void ouvre_note_asc();
	
	void load();

    void supprimer();

};

#endif // PluriNotes_H
