/*************************************************************************
                           Lecture  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Lecture> (fichier Lecture.h) -------------------
#if ! defined ( LECTURE_H )
#define LECTURE_H

//------------------------------------------------------------------------
// Rôle du module <Lecture>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "RequeteTools.h"
#include "CountingMap.h"

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
template <typename RequeteType, typename HashF>
void LectureLogs(
	CountingMap<RequeteType, HashF> * liste, 
	const string & source, 
	const RestrictionList & restrictions);
// Mode d'emploi :
//	Parcourt le fichier de Logs et enregistre tout dans la CountingMap.
// Contrat :
//	Le pointeur de CountingMap est valide.
//	Le fichier à écrire peut bien être écrit.

string GetExtension( const string & s);
// Mode d'emploi :
//  Renvoie l'extension du fichier dont le chemin est fourni.
//  Si pas d'extension renvoie l'argument entier.
// Contrat :
//  Aucun.

string CheckLocal(string s);
// Mode d'emploi :
//  Si le fichier décrit une URL locale, on tronque le début.
// Contrat :
//  Aucun.

#endif // LECTURE_H
