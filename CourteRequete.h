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
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct HashF_CourteRequete
// Classe-fonction utilisée par CountingMap.
{
    size_t operator () (const CourteRequete & cr) const;
};

struct EqualF_CourteRequete
// Classe-fonction utilisée par CountingMap.
{
    bool operator () (const CourteRequete & a, const CourteRequete & b) const;
};

//------------------------------------------------------------------------
// Rôle de la classe <CourteRequete>
//  Version courte et exploitable d'une requête Web
//  telle que fournie par le système Apache.
//  Elle est prête à l'emploi avec les autres modules.
//------------------------------------------------------------------------

class CourteRequete
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs
    CourteRequete & operator = ( const CourteRequete & cr );
    // Mode d'emploi :
    //  Recopie le contenu.
    // Contrat :
    //  Aucun.

    bool operator == ( const CourteRequete & cr);
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


//-------------------------------------------- Constructeurs - destructeur
    CourteRequete ( const CourteRequete & cr );
    // Mode d'emploi (constructeur de copie) :
    //  Recopie le contenu.
    // Contrat :
    //  Aucun.

    CourteRequete ( const Requete & req );
    // Mode d'emploi :
    //  Recopie le contenu de la Requete par extraction des données pertinentes
    // Contrat :
    //  Aucun.

    CourteRequete ( );
    // Mode d'emploi :
    //  Constructeur par défaut, CourteRequete avec rien dedans.
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
    string destination; // URL cible.
};

//---------------------- Autres définitions dépendantes de <CourteRequete>

size_t HashF_CourteRequete::operator () (const CourteRequete & cr) const
// Algorithme : 
//  Algorithme djb2 issu du site http://www.cse.yorku.ca/~oz/hash.html.
//  Appliqué deux fois car deux strings.
{
    const char * str1 = cr.source.c_str();
    size_t hash1 = 5381;
    int c;

    while ((c = *str1++))
    {
        hash1 = ((hash1 << 5) + hash1) + c; /* hash1 * 33 + c */
    }

    const char * str2 = cr.cible.c_str();
    size_t hash2 = 5381;
    int c;

    while ((c = *str2++))
    {
        hash2 = ((hash2 << 5) + hash2) + c; /* hash2 * 33 + c */
    }
    return hash1+hash2;
}

bool EqualF_CourteRequete::operator () 
    (const CourteRequete & a, const CourteRequete & b) const
{
    return a == b;
}

#endif // CourteRequete_H

