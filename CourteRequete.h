/*************************************************************************
                    CourteRequete  -  requête Web avec source et cible
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//-- Interface de la classe <CourteRequete> (fichier CourteRequete.h) ----
#if ! defined ( COURTEREQUETE_H )
#define COURTEREQUETE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <iostream>
using namespace std;
// #include "Lecture.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
//struct HashF_CourteRequete;
// Classe-fonction utilisée par CountingMap.

//------------------------------------------------------------------------
// Rôle de la classe <CourteRequete>
//  Version courte et exploitable d'une requête Web
//  telle que fournie par le système Apache.
//  Elle est prête à l'emploi avec les autres modules.
//------------------------------------------------------------------------

class CourteRequete
{
    friend struct HashF_CourteRequete;
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs
    CourteRequete & operator = ( const CourteRequete & cr );
    // Mode d'emploi :
    //  Recopie le contenu.
    // Contrat :
    //  Aucun.

    friend bool operator == (const CourteRequete& a, const CourteRequete& b);
    // Mode d'emploi :
    //  Compare deux la cible et la destination et renvoie true 
    //  ssi égalité pour les deux.
    // Contrat :
    //  Aucun.

    friend ostream & operator<< (ostream & os, const CourteRequete & cr);
    // Mode d'emploi :
    //  Ecrit le contenu de la CourteRequete dans le flux.
    // Contrat :
    //  Aucun.

    inline string GetSource () const 
    // Mode d'emploi :
    //  Renvoie la source par copie. Méthode inline car courte.
    // Contrat :
    //  Aucun.
    {
        return source;
    }

    inline string GetCible () const
    // Mode d'emploi :
    //  Renvoie la cible par copie. Méthode inline car courte.
    // Contrat ;
    //  Aucun.
    {
        return cible;
    }


//-------------------------------------------- Constructeurs - destructeur
    CourteRequete ( const CourteRequete & cr );
    // Mode d'emploi (constructeur de copie) :
    //  Recopie le contenu.
    // Contrat :
    //  Aucun.

    CourteRequete ( );
    // Mode d'emploi :
    //  Constructeur par défaut, CourteRequete avec rien dedans.
    // Contrat :
    //  Aucun.

    CourteRequete ( const string & URL_source, const string & URL_cible);
    // Mode d'emploi :
    //  Construit une CourteRequete avec une source et une cible.
    // Contrat :
    //  Aucun.
        
    virtual ~CourteRequete ( );
    // Mode d'emploi :
    //  Détruit la CourteRequête.
    // Contrat :
    //  Aucun.


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string source; // URL source.
    string cible; // URL cible.
};

//---------------------- Autres définitions dépendantes de <CourteRequete>

struct HashF_CourteRequete
// Classe-fonction utilisée par CountingMap.
{
    size_t operator () (const CourteRequete & cr) const;
};

#endif // CourteRequete_H

