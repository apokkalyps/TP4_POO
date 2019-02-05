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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum Erreur_e
{
	OPTION,
	FICHIER
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, char * argv [] );
// Mode d'emploi :
//	Fonction Main, porte d'entrée vers le programme depuis l'extérieur.
// 	Toutes les autres fonctionnalités sont encapsulées.
// Contrat :
//	Aucun !

bool StringIsNumeric (const string & s);
// Mode d'emploi :
//	Indique si une chaine de caractères contient des caractères autres que 
//	'-' et '0-9'.
// Mode d'emploi :
//	Aucun.

void Erreur (Erreur_e err, const string & message);
// Mode d'emploi :
//	Affiche un message d'erreur et arrête l'exécution avec 
//	un code de retour non nul.
// Contrat :
//	Aucun.

#endif // MAIN_H

