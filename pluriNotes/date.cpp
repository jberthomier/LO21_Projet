#include "date.h"

using namespace TIME;

QTextStream& operator<<(QTextStream& f,const Date& x){ x.afficher(f); return f;}

Date::Date() { //date actuelle
    std::time_t result = std::time(nullptr); // nombre de secondes depuis le 01/01/1970
    struct std::tm dateActuelle;
    dateActuelle = *localtime(&result);
    setDate(dateActuelle.tm_yday, dateActuelle.tm_mon, dateActuelle.tm_year+1900);
}

void Date::setDate(unsigned short int j, unsigned short int m, unsigned int a){
    // initialisation de la date, renvoie vrai si la date est valide
    if (a<=3000) annee=a; else throw TimeException("erreur: annee invalide");
    if (m>=1&&m<=12) mois=m; else throw TimeException("erreur: mois invalide");
    switch(m){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: if (j>=1 && j<=31) jour=j; else throw TimeException("erreur: jour invalide"); break;
    case 4: case 6: case 9: case 11: if (j>=1 && j<=30) jour=j; else throw TimeException("erreur: jour invalide"); break;
    case 2: if (j>=1 && (j<=29 || (j==30 && a%4==0))) jour=j; else throw TimeException("erreur: jour invalide"); break;
    }
}

void Date::afficher(QTextStream& f) const{
    // affiche le date sous le format JJ/MM/AAAA
    f<<jour<<"/"<<mois<<"/"<<annee<<" "; //a completer pour avoir 03/05/1998 par exemple, complete avec des 0 si un seul chiffre pour le jour ou le mois
}

bool Date::operator==(const Date& d) const{
    if (annee<d.annee) return false;
    if (annee>d.annee) return false;
    if (mois<d.mois) return false;
    if (mois>d.mois) return false;
    if (jour<d.jour) return false;
    if (jour>d.jour) return false;
    return true;
}

bool Date::operator<(const Date& d) const{
    if (annee<d.annee) return true;
    if (annee>d.annee) return false;
    if (mois<d.mois) return true;
    if (mois>d.mois) return false;
    if (jour<d.jour) return true;
    if (jour>d.jour) return false;
    return false;
}

int Date::operator-(const Date& d) const{
    int n=(annee-d.annee)*365+(annee-d.annee)/4;
    n+=int((mois-d.mois)*30.5);
    n+=jour-d.jour;
    return n;
}

Date Date::demain() const{
    Date d=*this;
    d.jour+=1;
    switch(d.mois){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: if (d.jour==30) { d.jour=1; d.mois++; } break;
    case 4: case 6: case 9: case 11: if (d.jour==31) { d.jour=1; d.mois++; } break;
    case 2: if (d.jour==29 && d.annee%4>0) { d.jour=1; d.mois++; } if (d.jour==30) { d.jour=1; d.mois++; } break;
    }
    if (d.mois==13){ d.annee++; d.mois=1; }
    return d;
}

Date Date::operator+(unsigned int nb_jours) const{
    Date d=*this;
    while(nb_jours>0) { d=d.demain(); nb_jours--; }
    return d;
}

std::istream& operator>>(std::istream& flot, TIME::Date& date){
    unsigned int short j,m,a;
    bool ok=true;
    flot>>j;
    if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
    else ok=false;

    if (!flot) ok=false;

    if(flot.peek()=='/') {
        flot.ignore();
        flot>>m;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }
    if(flot.peek()=='/') {
        flot.ignore();
        flot>>a;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }

    if (ok) date=Date(j,m,a); else flot.clear(std::ios::failbit);
    return flot;
}
