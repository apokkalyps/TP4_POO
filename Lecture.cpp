/*************************************************************************
                           Lecture  -  lecture d'un fichier de Logs Apache
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Lecture> (fichier Lecture.cpp) -------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <string>
#include <fstream>
#include "Lecture.h"
#include "RequeteTools.h"
using namespace std;
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static const string localURL = "http://intranet-if.insa-lyon.fr";

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
bool LireRequete (ifstream & ifs, Requete * req)
{
	// On vérifie si le flux va bien et si on a atteint la fin.
	if (ifs.good())
	{
		getline (ifs, req->userName, ' ');
		if (ifs.eof())
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	// On parcourt la ligne en récupérant tout.
	getline(ifs, req->userName, ' ');
	getline(ifs, req->authenticatedUserName, ' ');
	getline(ifs, req->jour, '/');
	getline(ifs, req->mois, '/');
	getline(ifs, req->annee, ':');
	getline(ifs, req->heure, ':');
	getline(ifs, req->minute, ':');
	getline(ifs, req->seconde, ' ');
	getline(ifs, req->fuseau, ' ');
	getline(ifs, req->type, ' ');
	getline(ifs, req->URL_cible, ' ');
	getline(ifs, req->protocole, ' ');
	getline(ifs, req->status, ' ');
	getline(ifs, req->data, ' ');
	getline(ifs, req->URL_source, ' ');
	getline(ifs, req->navigateur);

	//Nettoyage des parties inutiles récupérées (char en trop)
	req->fuseau = req->fuseau.substr(0,req->fuseau.length()-1);
	req->type = req->type.substr(1, req->type.length()-1);
	req->protocole = req->protocole.substr(0,req->protocole.length()-1);
	req->URL_source = 
		CheckLocal(req->URL_source.substr(1,req->URL_source.length()-2));
	req->navigateur = 
		req->navigateur.substr(1,req->navigateur.length()-2);

	return true;
} //----- fin de LireRequete

bool ValideOption(const RestrictionList & rlist, const Requete & r)
{
	return rlist.TesterTout(r);
} //----- fin de ValideOption

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

