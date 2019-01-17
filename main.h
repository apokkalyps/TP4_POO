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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Restrictions
// Structure encapsulant (en public) les requêtes de l'utilisateurs
// en matière de restrictions dans la lecture du fichier.
// > extensions indique si l'option "-e" est demandee.
// > heure indique l'heure demandee par l'utilisateur. 
// 		-1 signifie pas d'heure demandee.
{
	bool extensions;
	unsigned char heure;
	Restrictions (bool e = false, unsigned char h = -1); // Constructeur
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, char *argv[]);
// Mode d'emploi :
//	Fonction Main, la seule appellable depuis l'extérieur.
// 	Toutes les autres fonctionnalités sont encapsulées.
// Contrat :
//	Aucun !

std::ostream & operator << (ostream & os, const Restrictions & res);
// Mode d'emploi :
//  Surcharge de l'opérateur d'injection dans un flux.
// Contrat :
//  Aucun !

#endif // MAIN_H

