/*************************************************************************
                           Lecture  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Lecture> (fichier Lecture.cpp) -------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Lecture.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "CountingMap.h"
#include "CourteRequete.h"
using namespace std;
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static const string localURL = "http://intranet-if.insa-lyon.fr";
static const string source; // Fichier à écrire dedans de lequel pour.
template <typename RequeteType, typename HashF>
static CountingMap <RequeteType, HashF> * requete; // Les requêtes
static const RestrictionList * restr; // Pointeur de liste de restrictions.

//------------------------------------------------------ Fonctions privées
static bool valideOption(const Requete & r)
// Mode d'emploi :
//  Renvoie true si la requête fournie satisfait toutes les restrictions.
// Contrat :
//  Le pointeur de RestrictionList est bien défini.
{
	return restr->TesterTout(r);
} //----- fin de valideOption

template <typename RequeteType, typename HashF>
static void setValues 
	(CountingMap<RequeteType, HashF> * liste, 
	const string & fichierSource, 
	const RestrictionList & restrictions)
// Mode d'emploi :
//  Met les bonnes valeurs dans les variables privées du modules.
// Contrat :
//  Les variables sont bien formées, le pointeur bien alloué.
{
	requete<RequeteType, HashF> = liste;
	source = fichierSource;
	restr = & restrictions;
} //----- fin de setValues

template <typename RequeteType, typename HashF>
static void parcours()
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

			if(valideOption(nvx))
			{
				requete<RequeteType, HashF>->Ajouter (nvlle);
			} 
		}
	}
} //----- fin de parcours

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
template <typename RequeteType, typename HashF>
void LectureLogs(CountingMap<RequeteType, HashF> * liste, 
	const string & source, 
	const RestrictionList & restrictions)
{
	setValues <RequeteType, HashF> (liste, source, restrictions);
	parcours<RequeteType, HashF>();
} //----- fin de LectureLogs


string GetExtension( const string & s)
{
  size_t found = s.find_last_of(".");
  return s.substr(found+1);
} //------ fin de GetExtension

string CheckLocal(string s)
// Algorithme :
//	https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s12.html
{
	std::string::size_type i = s.find(localURL);
	if (i != std::string::npos)
	{
		s.erase(i, localURL.length());
	}
	return s;
} //----- fin de CheckLocal
