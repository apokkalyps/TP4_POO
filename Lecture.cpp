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
#include "RequeteTools.h"
#include <string>
using namespace std;
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static const string localURL = "http://intranet-if.insa-lyon.fr";

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
bool ValideOption(const RestrictionList * rlist, const Requete & r)
{
	return rlist->TesterTout(r);
} //----- fin de valideOption

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

