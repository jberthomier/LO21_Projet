#include "affichagenote.h"

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


NoteEditeur* AffichageNote::createEditeur(Note* n) {
    QVector<NoteEditeur*>::iterator it;
    for (it = NoteEditeur::editeurs.begin(); it!=NoteEditeur::editeurs.end(); it++){
        if((*it)->getId()==n->getId()) {
            qDebug()<<"returned existing editor";
            return *it;
        }
    }
    qDebug()<<"Ajout editeur";
    NoteEditeur* edit=NULL;
    qDebug()<<"Entree18";
    QString type= n->getType();
    qDebug()<<type;
    if (type=="article") {
        qDebug()<<"Entree19";
        Article* a=dynamic_cast<Article*>(n);
        qDebug()<<"Entree20";
        edit = new ArticleEditeur(a);
        qDebug()<<"article";
    }
    /*if (type=="tache") {
        edit = new TacheEditeur(dynamic_cast<Tache*>(n));
        qDebug()<<"tache";
    }

    if (type=="media") {
        edit = new MediaEditeur(dynamic_cast<Media*>(n));
        qDebug()<<"media";
    }*/
    return edit;
}

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
    qDebug()<<"Entree7";
    int j = tabWidget->count();
    qDebug()<<j;
    for (int i = 0;i<tabWidget->count(); i++){
        qDebug()<<"Entree8";
        if (tabWidget->tabText(i)==article->getId() || tabWidget->tabText(i)=="*"+article->getId()) {
            qDebug()<<"Entree9";
            tabWidget->setCurrentIndex(i);
    qDebug()<<"Entree10";
    return;
    }
}
    qDebug()<<"Entree11";
    NoteEditeur* window=createEditeur(article);
    qDebug()<<"Entree12";
    connect(window,&NoteEditeur::Editing,this,&AffichageNote::unsavedChanges);
    qDebug()<<"Entree13";
    connect(window,&NoteEditeur::Editionfinished,this,&AffichageNote::savedChanges);
    qDebug()<<"Entree14";
    tabWidget->addTab(window,window->getId());
    qDebug()<<"Entree15";
    tabWidget->setCurrentWidget(window);
    qDebug()<<"Entree17";

}


void AffichageNote::fermeNote(const QString &id){
    for (int i=0; i<tabWidget->count(); i++)
        if(tabWidget->tabText(i)==id || tabWidget->tabText(i)=="*"+id)
            fermeTab(i);
}


void AffichageNote::fermeTab(int i) {
    tabWidget->setCurrentIndex(i);
    QWidget* old = tabWidget->widget(i);
    delete old;
}

bool AffichageNote::ouverte(const QString &id) {
    for (int i=0; i<tabWidget->count(); i++)
        if(tabWidget->tabText(i)==id ||tabWidget->tabText(i)=="*"+id )
            return true;
   return false;
}

void AffichageNote::refreshNote(const QString &id) {
    for (int i =0; i<tabWidget->count(); i++) {
        if(tabWidget->tabText(i)==id||tabWidget->tabText(i)=="*"+id) {
            QWidget* edition = tabWidget->widget(i);
            qDebug()<<"Note trouvee";
            tabWidget->removeTab(i);
            tabWidget->insertTab(i,edition,id);
            tabWidget->setCurrentIndex(i);
        }
    }
}

void AffichageNote::unsavedChanges(NoteEditeur *e) {
    tabWidget->setTabText(tabWidget->indexOf(e),"*"+e->getId());
}

void AffichageNote::savedChanges(NoteEditeur *e) {
    tabWidget->setTabText(tabWidget->indexOf(e),e->getId());
}
