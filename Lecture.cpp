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
void Lecture ( const Historique* h, string fname, options.. )
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

      struct Requete new;

      getline(monFlux, new.IP, " ");
      getline(monFlux, new.authenticatedUserName, " ");
      getline(monFlux, new.jour, " ");
      getline(monFlux, new.mois, " ");
      getline(monFlux, new.annee, " ");
      getline(monFlux, new.heure, " ");
      getline(monFlux, new.minute, " ");
      getline(monFlux, new.seconde, " ");
      getline(monFlux, new.fuseau, " ");
      getline(monFlux, new.type, " ");
      getline(monFlux, new.URL_R, " ");
      getline(monFlux, new.protocole, " ");
      getline(monFlux, new.status, " ");
      getline(monFlux, new.data, " ");
      getline(monFlux, new.URL_r, " ");
      getline(monFlux, new.navigateur);

      if(valideOption(new)) historique->ajouterElement(URL_r, URL_r);

    }

  }
  else
	{
	    cerr << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}

}

bool valideOption(struct Requete elmt)
{
  .
}


//---------------------------------------------- Surcharge d operateurs --

//----------------------------------------- Constructeurs - Destructeur --
