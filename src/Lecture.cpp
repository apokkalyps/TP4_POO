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
#include <string>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Lecture.h"
#include "RequeteTools.h"
using namespace std;

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static const string localURL = "http://intranet-if.insa-lyon.fr";
static int comp = 0;

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
		CheckURL(req->URL_source.substr(1,req->URL_source.length()-2));
	req->URL_cible = CheckURL(req->URL_cible);
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

string CheckURL(string s)
// Algorithme :
//	https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s12.html
{
	string localURL2 = "http://servif-web.insa-lyon.fr:90";
	string localURL3 = "http://intranet-if:90";
	string localURL4 = "http://intranet-if.insa-lyon.fr:90";
	//cout << "- avant : " << s << endl;
	std::string::size_type local1 = s.find("http://intranet-if.insa-lyon.fr");
	std::string::size_type local2 = s.find("http://servif-web.insa-lyon.fr:90");
	std::string::size_type local3 = s.find("http://intranet-if:90");
	std::string::size_type local4 = s.find("http://intranet-if.insa-lyon.fr:90");

	std::string::size_type i = s.find("jsessionid");
	std::string::size_type j = s.find("google");
	std::string::size_type k = s.find("php?");

// Filtrage des URL locales
	if (local1 != std::string::npos)
	{
		if (local4 != std::string::npos)
		{
			s.erase(local4, localURL4.length());
		}
		else
		{
			s.erase(local1, localURL.length());
		}
	}
	else if (local2 != std::string::npos)
	{
		s.erase(local2, localURL2.length());
	}
	else if (local3 != std::string::npos)
	{
		s.erase(local3, localURL3.length());
	}


	if(j != std::string::npos)
	{
		s = "www.google.com";
	}


	if(k != std::string::npos)
	{
		//cout << comp <<" - avant : " << s << endl;
		s = s.substr(0, k+3);
		//cout << "- apres : " << s << endl;
	}
	if(i != std::string::npos)
	{
		s = s.substr(0, i);
	}

	comp++;

	//cout << "- apres : " << s << endl;
	return s;
} //----- fin de CheckURL
