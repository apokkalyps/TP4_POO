/*************************************************************************
                           Tests  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Tests> (fichier Tests.h) ---------------
#ifndef TESTS_H
#define TESTS_H

//------------------------------------------------------------------------
// Rôle du module <Tests>
//	Fournit un ensemble de fonctions destinées au débogage et aux jeux de tests.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Main.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void AfficheArgs ( char * args [], int nbr_args );
// Mode d'emploi :
//	Affiche les arguments fournis au main.
// Contrat :
//	Format des données fournies identique au main.

std::ostream & operator << (ostream & os, const Restrictions & res);
// Mode d'emploi :
//  Surcharge de l'opérateur d'injection dans un flux.
// Contrat :
//  Aucun !

#endif // TESTS_H
