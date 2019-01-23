/*************************************************************************
                           Tests  -  ensemble de tests +/- unitaires
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
//	Fournit un ensemble de fonctions destinées au débogage et aux jeux de tests
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void AfficheArgs ( char * args [], int nbr_args );
// Mode d'emploi :
//	Affiche les arguments fournis au main.
// Contrat :
//	Format des données fournies identique au main.

void LanceTest (unsigned short numTest);
// Mode d'emploi :
//	Lance le test indexé par numTest.
//	Si numTest n'est pas spécifié, exécute tous les tests.
// Contrat :
//	Aucun.

#endif // TESTS_H
