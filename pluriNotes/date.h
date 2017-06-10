#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QTextStream>
#include <ctime>
#include <iostream>
#include <QDebug>


//QTextStream qDebug()()(stdout);
//QTextStream cin(stdin);

/*QTextStream& qDebug()
{
    static QTextStream ts( stdout );
    return ts;
}

QTextStream& cin
{
    static QTextStream ts( stdin );
    return ts;
}

*/
namespace TIME {

using namespace std;

class TimeException{
    public:
        //! Constructeur à partir d'une string
        TimeException(const QString& m):info(m){}
        const QString& GetInfo() const { return info; } //<! Retourne l'information stockée dans la classe
    private:
        QString info;
    };

class Date {
    public:
        //! Constructeur à partir d'un jour, mois, année
        /*! \param j jour avec 1<=j<=31
            \param m mois avec 1<=m<=12
            \param a année avec a>=0
            */
        Date();
        Date(unsigned int short j, unsigned int short m, unsigned int a):jour(1),mois(1),annee(0){ setDate(j,m,a); }
        // méthodes
        unsigned short int  getJour() const { return jour; } //<! Retourne le jour de la date
        unsigned short int  getMois() const { return mois; } //<! Retourne le mois de la date
        unsigned int getAnnee() const { return annee; } //<! Retourne l'année de la date
        void setDate(unsigned short int j, unsigned short int m, unsigned int a); //!< initialisation de la date
        QString afficher() const; //!< affiche le date sous le format JJ/MM/AAAA
        bool operator==(const Date& d) const; //<! d1==d2 retourne vrai si les deux dates sont égales
        bool operator<(const Date& d) const; //<! Compare deux dates dans le temps : d1<d2 retourne true si d1 est avant d2
        int operator-(const Date& d) const; //<! Retourne le nombre de jours séparant les deux dates
        Date demain() const; //<! Retourne la date du lendemain
        Date operator+(unsigned int nb) const; //<!Retourne la date de dans nb jours
    private:
        // attributs
        unsigned short int jour; // jour entre 1 et 31
        unsigned short int mois; // mois entre 1 et 12
        unsigned int annee;
    };

}

#endif // DATE_H
