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

bool ValideOption(const RestrictionList * rlist, const Requete & r);
// Mode d'emploi :
//  Renvoie true si la requête fournie satisfait toutes les restrictions.
// Contrat :
//  Le pointeur de RestrictionList est bien défini.

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

namespace LectReq
// Encapsule les fonctions internes liées à la lecture d'un fichier
// pour en extraire les requêtes.
{
	namespace
	// Données et fonctions privées locales	
	{
		// ------------------------------------------------- Variables privées.
		const string localURL = "http://intranet-if.insa-lyon.fr";
		string source; // Fichier à écrire dedans de lequel pour.
		template <typename RequeteType, typename HashF>
		CountingMap <RequeteType, HashF> * requete; // Les requêtes
		const RestrictionList * restr; // Pointeur de liste de restrictions.

		// ------------------------------------------------- Fonctions privées.
		template <typename RequeteType, typename HashF>
		void parcours()
		// Mode d'emploi :
		//  Parcourt le fichier et remplit la CountingMap.
		// Contrat :
		//	Aucun.
		{
			ifstream monFlux(source.c_str());

			if (monFlux.good())
			{
				Requete nvx;
				while (LireRequete(monFlux, &nvx))
				{
					if (ValideOption(restr, nvx))
					{
						requete<RequeteType, HashF>->Ajouter (RequeteType(nvx));
					} 
				}
			}
			else
			{
				// Erreur 2
			}
		} //----- fin de parcours
	}

	// --------------------------------------------------- Fonctions publiques.

	template <typename RequeteType, typename HashF>
	void LectureLogs(
		CountingMap<RequeteType, HashF> * liste, 
		const string & laSource, 
		const RestrictionList & restrictions)
	// Mode d'emploi :
	//	Parcourt le fichier de Logs et enregistre tout dans la CountingMap.
	// Contrat :
	//	Le pointeur de CountingMap est valide.
	{
		requete<RequeteType, HashF> = liste;
		source = laSource;
		restr = & restrictions;
		parcours<RequeteType, HashF>();
	} //----- fin de LectureLogs
}


#endif // LECTURE_H
