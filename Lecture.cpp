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
#include <cstddef>         // std::size_t
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
void LectureLogs ( const Historique* h, string fname, options.. )
// Algorithme :
//
{

  Parcours();
} //----- fin de Nom

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
      getline(monFlux, nvx.IP, " ");
      getline(monFlux, nvx.authenticatedUserName, " ");
      getline(monFlux, nvx.jour, " ");
      getline(monFlux, nvx.mois, " ");
      getline(monFlux, nvx.annee, " ");
      getline(monFlux, nvx.heure, " ");
      getline(monFlux, nvx.minute, " ");
      getline(monFlux, nvx.seconde, " ");
      getline(monFlux, nvx.fuseau, " ");
      getline(monFlux, nvx.type, " ");
      getline(monFlux, nvx.URL_cible, " ");
      getline(monFlux, nvx.protocole, " ");
      getline(monFlux, nvx.status, " ");
      getline(monFlux, nvx.data, " ");
      getline(monFlux, nvx.URL_source, " ");
      getline(monFlux, nvx.navigateur);

      //Nettoyage des parties intules récupérées

      if(valideOption(nvx)) historique->ajouterElement(URL_cible, URL_source);

    }

  }
  else
	{
	    cerr << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}

}

bool valideOption(struct Requete r, struct Restrictions re)
{
  if (r == null)
    {   return false;
    }

  bool e_valide = false;
  bool t_valide = false;
  // -e
  if(re.extensions)
  {
    string ext = getExtension(r.URL_cible);
    for(int i = 0; i < restrictedFormats.length(); i++)
    {
      ext.compare(restrictedFormats[i]) == 1 ? e_valide = true, break;
    }
  }

  // -t
  if(re.heure != -1)
  {
    r.heure.compare(re.heure) ? t_valide = true;
  }

  if(re.extensions && re.heure != -1)
    return e_valide && t_valide;
  else if(re.extensions)
    return e_valide;
  else if(re.heure != -1)
    return t_valide;
  else
    return true;
}

string getExtension( string s){
  size_t found = s.find_last_of(".");

  return s.substr(found+1);
}


//---------------------------------------------- Surcharge d operateurs --

//----------------------------------------- Constructeurs - Destructeur --
