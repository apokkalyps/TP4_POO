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
		//	Le fichier a le droit d'être écrit.
		{
			ifstream monFlux(source.c_str());

			if(monFlux)
				{
				while( monFlux.good())
				{
					#ifdef MAP
					cout << "Lecture d'une ligne " << endl;
					#endif

					struct Requete nvx;

					//Remmplissage de la ligne pour une requete donnée
					getline(monFlux, nvx.IP, ' ');
					if (monFlux.eof())
					{
						return;
					}
					getline(monFlux, nvx.userName, ' ');
					getline(monFlux, nvx.authenticatedUserName, ' ');
					getline(monFlux, nvx.jour, '/');
					getline(monFlux, nvx.mois, '/');
					getline(monFlux, nvx.annee, ':');
					getline(monFlux, nvx.heure, ':');
					getline(monFlux, nvx.minute, ':');
					getline(monFlux, nvx.seconde, ' ');
					getline(monFlux, nvx.fuseau, ' ');
					getline(monFlux, nvx.type, ' ');
					getline(monFlux, nvx.URL_cible, ' ');
					getline(monFlux, nvx.protocole, ' ');
					getline(monFlux, nvx.status, ' ');
					getline(monFlux, nvx.data, ' ');
					getline(monFlux, nvx.URL_source, ' ');
					getline(monFlux, nvx.navigateur);

					//Nettoyage des parties inutiles récupérées (char en trop)
					nvx.fuseau = nvx.fuseau.substr(0,nvx.fuseau.length()-1);
					nvx.type = nvx.type.substr(1, nvx.type.length()-1);
					nvx.protocole = nvx.protocole.substr(0,nvx.protocole.length()-1);
					nvx.URL_source = 
						CheckLocal(nvx.URL_source.substr(1,nvx.URL_source.length()-2));
					nvx.navigateur = 
						nvx.navigateur.substr(1,nvx.navigateur.length()-2);

					// On créer une requete courte avec uniquement les elements voulus
					RequeteType nvlle(nvx);

					if(ValideOption(restr, nvx))
					{
						requete<RequeteType, HashF>->Ajouter (nvlle);
					} 
				}
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
	//	Le fichier à écrire peut bien être écrit.
	{
		requete<RequeteType, HashF> = liste;
		source = laSource;
		restr = & restrictions;
		parcours<RequeteType, HashF>();
	} //----- fin de LectureLogs
}


#endif // LECTURE_H
