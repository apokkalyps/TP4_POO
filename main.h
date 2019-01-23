/*************************************************************************
                           Main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Main> (fichier Main.h) -------------------
#if ! defined ( MAIN_H )
#define MAIN_H

//------------------------------------------------------------------------
// Rôle du module <Main>
//	Module lancé au démarrage du programme.
//	Il prend en compte les arguments puis appelle tour à tour les autres
//	fonctionnalités.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>

//------------------------------------------------------------- Constantes

string source;
//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, char * argv [] );
// Mode d'emploi :
//	Fonction Main, porte d'entrée vers le programme depuis l'extérieur.
// 	Toutes les autres fonctionnalités sont encapsulées.
// Contrat :
//	Aucun !

#endif // MAIN_H

