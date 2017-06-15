#include "affichagenote.h"

/*------------------------------------------------------Méthodes privées de AffichageNote-------------------------------------------------------*/

void AffichageNote::fermeTab(int i) {
    tabWidget->setCurrentIndex(i);
    QWidget* old = tabWidget->widget(i);
    delete old;
}

NoteEditeur* AffichageNote::createEditeur(Note* n) {

    NoteEditeur* edit=NULL;
    QString type= n->getType();
    if (type=="article") {
        Article* a=dynamic_cast<Article*>(n);
        edit = new ArticleEditeur(a);
    }
    if (type=="tache") {
        Tache* t= dynamic_cast<Tache*>(n);
        edit = new TacheEditeur(t);
    }
    if (type=="media") {
        edit = new MediaEditeur(dynamic_cast<Media*>(n));
    }
    return edit;
}

ArticleEditeur* AffichageNote::createArticleEditeur(Note* n) {
    ArticleEditeur* edit=NULL;
    Article* a=dynamic_cast<Article*>(n);
        edit = new ArticleEditeur(a);
    return edit;
}

/*------------------------------------------------------Méthodes publiques de AffichageNote-------------------------------------------------------*/

/*------------------------------------------------------Constructeur et destructeur-------------------------------------------------------*/

AffichageNote::AffichageNote(QWidget *parent) :
    QWidget(parent)
{
    layout= new QHBoxLayout(this);
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    layout->addWidget(tabWidget);
    QObject::connect(tabWidget, &QTabWidget::tabCloseRequested,this,&AffichageNote::fermeTab);

}

AffichageNote::~AffichageNote()
{
    for(int i=tabWidget->count();i>0; i--)
        fermeTab(i);
}

/*------------------------------------------------------Méthodes-------------------------------------------------------*/

void AffichageNote::afficheNote(Note* note) {
    for (int i = 0;i<tabWidget->count(); i++){
        if (tabWidget->tabText(i)==note->getId() || tabWidget->tabText(i)=="*"+note->getId()) {
            tabWidget->setCurrentIndex(i);
            return;
        }
    }


    NoteEditeur* window=createEditeur(note);
    connect(window,&NoteEditeur::Editing,this,&AffichageNote::unsavedChanges);
    connect(window,&NoteEditeur::Editionfinished,this,&AffichageNote::savedChanges);

    tabWidget->addTab(window,window->getId());
    tabWidget->setCurrentWidget(window);
}

void AffichageNote::afficheArticle(Article* article) {
    int j = tabWidget->count();
    for (int i = 0;i<tabWidget->count(); i++){
        if (tabWidget->tabText(i)==article->getId() || tabWidget->tabText(i)=="*"+article->getId()) {
            tabWidget->setCurrentIndex(i);
    return;
    }
}
    ArticleEditeur* window=createArticleEditeur(article);
    connect(window,&NoteEditeur::Editing,this,&AffichageNote::unsavedChanges);
    connect(window,&NoteEditeur::Editionfinished,this,&AffichageNote::savedChanges);
    tabWidget->addTab(window,window->getId());
    tabWidget->setCurrentWidget(window);
}

void AffichageNote::afficheTache(Tache* tache) {
    int j = tabWidget->count();
    for (int i = 0;i<tabWidget->count(); i++){
        if (tabWidget->tabText(i)==tache->getId() || tabWidget->tabText(i)=="*"+tache->getId()) {
            tabWidget->setCurrentIndex(i);
    return;
    }
}
    NoteEditeur* window=createEditeur(tache);
    connect(window,&NoteEditeur::Editing,this,&AffichageNote::unsavedChanges);
    connect(window,&NoteEditeur::Editionfinished,this,&AffichageNote::savedChanges);
    tabWidget->addTab(window,window->getId());
    tabWidget->setCurrentWidget(window);
}

void AffichageNote::afficheMedia(Media* media) {
    int j = tabWidget->count();
    for (int i = 0;i<tabWidget->count(); i++){
        if (tabWidget->tabText(i)==media->getId() || tabWidget->tabText(i)=="*"+media->getId()) {
            tabWidget->setCurrentIndex(i);
    return;
    }
}
    NoteEditeur* window=createEditeur(media);
    connect(window,&NoteEditeur::Editing,this,&AffichageNote::unsavedChanges);
    connect(window,&NoteEditeur::Editionfinished,this,&AffichageNote::savedChanges);
    tabWidget->addTab(window,window->getId());
    tabWidget->setCurrentWidget(window);

}

void AffichageNote::fermeNote(const QString &id){
    for (int i=0; i<tabWidget->count(); i++)
        if(tabWidget->tabText(i)==id || tabWidget->tabText(i)=="*"+id)
            fermeTab(i);
}

void AffichageNote::refreshNote(const QString &id) {
    for (int i =0; i<tabWidget->count(); i++) {
        if(tabWidget->tabText(i)==id||tabWidget->tabText(i)=="*"+id) {
            QWidget* edition = tabWidget->widget(i);
            tabWidget->removeTab(i);
            tabWidget->insertTab(i,edition,id);
            tabWidget->setCurrentIndex(i);
        }
    }
}

bool AffichageNote::ouverte(const QString &id) {
    for (int i=0; i<tabWidget->count(); i++)
        if(tabWidget->tabText(i)==id ||tabWidget->tabText(i)=="*"+id )
            return true;
   return false;
}

/*------------------------------------------------------Méthodes public slots-------------------------------------------------------*/

void AffichageNote::unsavedChanges(NoteEditeur *e) {
    tabWidget->setTabText(tabWidget->indexOf(e),"*"+e->getId());
}

void AffichageNote::savedChanges(NoteEditeur *e) {
    tabWidget->setTabText(tabWidget->indexOf(e),e->getId());
}
