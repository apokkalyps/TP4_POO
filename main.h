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
#include <iostream>
#include <string>
#include "CountingMap.h"
#include "CourteRequete.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Restrictions
// Structure encapsulant (en public) les requêtes de l'utilisateur
// en matière de restrictions dans la lecture du fichier source.
// > extensions indique si l'option "-e" est demandee.
// > heure indique l'heure demandee par l'utilisateur. 
// 		-1 signifie pas d'heure demandee.
{
	bool extensions;
	unsigned char heure;
	explicit Restrictions (bool e = false, unsigned char h = -1); // Constr
};

CountingMap <CourteRequete, HashF_CourteRequete> requetes;
// Variable globale des courtes requêtes extraites.

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, char * argv [] );
// Mode d'emploi :
//	Fonction Main, porte d'entrée vers le programme depuis l'extérieur.
// 	Toutes les autres fonctionnalités sont encapsulées.
// Contrat :
//	Aucun !

#endif // MAIN_H

