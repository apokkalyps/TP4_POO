/*************************************************************************
                           Lecture  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Lecture> (fichier Lecture.cpp) ---------------

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


//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


void Parcours()
{
  ifstream monFlux(file_Name.c_str());

  if(monFlux)
  {
    while(monFlux.good())
    {
      #ifdef MAP
      	  	cout << "Lecture d'une ligne " << endl;
      #endif

      struct Requete nvx;

      //Remmplissage de la ligne pour une requete donnée
      getline(monFlux, nvx.IP, ' ');
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
      nvx.userName = nvx.userName.substr(1);

      nvx.annee = nvx.annee.substr(0,nvx.annee.length()-1);
      nvx.fuseau = nvx.fuseau.substr(0,nvx.fuseau.length()-1);

      nvx.type = nvx.type.substr(1);

      nvx.protocole = nvx.protocole.substr(0,nvx.protocole.length()-1);

      nvx.URL_source = checkLocal(nvx.URL_source.substr(1,nvx.URL_source.length()-1));

      nvx.navigateur = nvx.navigateur.substr(1,nvx.navigateur.length()-1);

      //Validation et ajout

      // On créer une requete courte avec uniquement les elements voulus
      CourteRequete nvlle(nvx.URL_source, nvx.URL_cible);

      if(valideOption(nvx))
      {
        requete<CourteRequete, HashF_CourteRequete>->Ajouter (nvlle);
      }
    }
  }
  else
	{
	    cerr << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}

}

bool valideOption(const Requete & r)
{
  return regle->TesterTout(r);
}
  /*
  if (r == null)
    {   return false;
    }
*/
/*
  bool e_valide = false;
  bool t_valide = false;

  // Restriction sur l'extension : -e
  if(regle.extensions)
  {
    string ext = getExtension(r.URL_cible);
    for(int i = 0; i < nbRF; i++)
    {
      if (ext.compare(restrictedFormats[i]) == 1)
      {
        e_valide = true;
      }
      else
      {
        break;
      }
    }
  }

  // Restriction sur l'heure : -t heure
  if (regle.heure != 1 && r.heure.compare (to_string (regle.heure)))
  {
    t_valide = true;
  }

  if(regle.extensions && regle.heure != -1)
    return e_valide && t_valide;
  else if(regle.extensions)
    return e_valide;
  else if(regle.heure != -1)
    return t_valide;
  else
    return true;
}*/

string getExtension( string s)
{
  size_t found = s.find_last_of(".");

  return s.substr(found+1);
}

string checkLocal(string s)
{
  // Algorithme de 
  // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s12.html
  std::string::size_type i = s.find(localURL);
	if (i != std::string::npos)
		s.erase(i, localURL.length());

  return s;


}


//---------------------------------------------- Surcharge d operateurs --

//----------------------------------------- Constructeurs - Destructeur --
