/*************************************************************************
                           Paire  -  une donnée + un unsigned int
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Paire> (fichier Paire.h) ----------------
#if ! defined ( PAIRE_H )
#define PAIRE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
typedef unsigned int nbr_t; // Raccourci car beaucoup utilisé.

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Paire>
//  Version courte et exploitable d'une requête Web
//  telle que fournie par le système Apache.
//  Elle est prête à l'emploi avec les autres modules.
//------------------------------------------------------------------------

template <typename Donnee>
class Paire
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Paire & operator = ( const Paire & unPaire ) = default;
    // Mode d'emploi :
    //  Opérateur d'affectation par défaut (car pas d'allocation dynamique).
    // Contrat :
    //  Aucun.

    bool operator < ( const Paire <Donnee> & p ) const;
    // Mode d'emploi :
    //  Surcharge de l'opérateur de comparaison inférieur.
    // Contrat :
    //  Aucun.

    friend std::ostream & operator << ( std::ostream & os, const Paire<Donnee> p)
    // Mode d'emploi :
    //  Surchage de l'opérateur d'injection dans le flux de sortie.
    // Contrat :
    //  Aucun.
    {
        return ( os << '{' << p.data << ", " << p.score << '}' );
    }


//-------------------------------------------- Constructeurs - destructeur
    Paire ( const Paire & unePaire );
    // Mode d'emploi (constructeur de copie) :
    //  Constructeur par copie d'une paire.
    // Contrat :
    //  Aucun.

    Paire (Donnee d = Donnee (), nbr_t s = 0);
    // Mode d'emploi :
    //  Constructeur par défaut d'une paire.
    // Contrat :
    //  Aucun.

    virtual ~Paire ( );
    // Mode d'emploi :
    //  Destruction d'une paire.
    // Contrat :
    //  Aucun.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Donnee data; // Donnée stockée
    nbr_t score; // Nombre d'occurences
};

//-------------------------------- Autres définitions dépendantes de <Paire>

//------------------------------------------------- Surcharge d'opérateurs
template <typename Donnee>
bool Paire<Donnee> :: operator < ( const Paire <Donnee> & p ) const
{
    return score < p.score;
} //----- fin de operator < pour Paire.


//-------------------------------------------- Constructeurs - destructeur
template <typename Donnee>
Paire<Donnee>::Paire ( const Paire & unePaire ) :
    data (unePaire.data),
    score (unePaire.score)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Paire>" << endl;
#endif
} //----- Fin de Paire (constructeur de copie)


template <typename Donnee>
Paire<Donnee> :: Paire (Donnee d, nbr_t s) :
    data (d), score (s)
{
#ifdef MAP
    cout << "Appel au constructeur de <Paire>" << endl;
#endif
} //----- fin du constructeur de Paire.


template <typename Donnee>
Paire<Donnee>::~Paire ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Paire>" << endl;
#endif
} //----- Fin de ~Paire

#endif // PAIRE_H

