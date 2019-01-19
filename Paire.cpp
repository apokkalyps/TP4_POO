/*************************************************************************
                           Paire  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Paire> (fichier Paire.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Paire.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Paire::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
template <typename Donnee>
bool Paire<Donnee> :: operator < ( const Paire <Donnee> & p ) const
{
    return score < p.score;
} //----- fin de operator < pour Paire.


//-------------------------------------------- Constructeurs - destructeur
Paire::Paire ( const Paire & unePaire ) :
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


Paire::~Paire ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Paire>" << endl;
#endif
} //----- Fin de ~Paire


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

