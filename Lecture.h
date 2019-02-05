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
#include <fstream>
#include "RequeteTools.h"
#include "CountingMap.h"
#include "Main.h"
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
bool LireRequete (ifstream & ifs, Requete * req);
// Mode d'emploi :
//	Lit une ligne sur le flux courant et écrit la requête lue
//	sur le pointeur fourni (doit être alloué et inscriptible).
//	Renvoie false si la lecture a échoué.
// Contrat :
//	Le pointeur est alloué.

bool ValideOption(const RestrictionList & rlist, const Requete & r);
// Mode d'emploi :
//  Renvoie true si la requête fournie satisfait toutes les restrictions.
// Contrat :
//  Aucun.

string GetExtension( const string & s);
// Mode d'emploi :
//  Renvoie l'extension du fichier dont le chemin est fourni.
//  Si pas d'extension renvoie l'argument entier.
// Contrat :
//  Aucun.

string CheckURL(string s);
// Mode d'emploi :
//  Si le fichier décrit une URL locale, on tronque le début.
// Contrat :
//  Aucun.

template <typename RequeteType, typename HashF>
void LectureLogs(
	CountingMap<RequeteType, HashF> * liste,
	const string & source,
	const RestrictionList & restr)
// Mode d'emploi :
//	Parcourt le fichier de Logs et enregistre tout dans la CountingMap.
// Contrat :
//	Le pointeur de CountingMap est valide.
{
	ifstream monFlux(source.c_str());

	if (monFlux.good())
	{
#ifdef MAP
		cout << "Flux ouvert. " << endl;
		unsigned int iLigne = 0;
#endif // MAP

		Requete nvx;
		while (LireRequete(monFlux, &nvx))
		{
#ifdef MAP
			cout << "Ligne " << iLigne++ << '.' << endl;
#endif // MAP
			if (ValideOption(restr, nvx))
			{
				liste->Ajouter (RequeteType(nvx));
			}
		}
#ifdef MAP
		cout << "Fin de la lecture, " << iLigne << " lignes lues." << endl;
#endif // MAP
	}
	else
	{
		Erreur(FICHIER, "Lecture du Logs.");
	}
} //----- fin de LectureLogs

#endif // LECTURE_H
