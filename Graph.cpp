/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Graph> (fichier Graph.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include <algorithm>

#include "Graph.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef vector<Paire<CourteRequete>> liste;

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
/
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void GenerateGraph (const liste & req, const string & nomFichier)
{
  //Déclaration d'un flux permettant d'écrire dans un fichier.
  ofstream monFlux(nomFichier.c_str());

  if(monFlux)
  {
    set <string, greater <string> > nodes;
    //Recuperation des nodes uniques
    liste::const_iterator
    d (req.begin()),
    f (req.end());
  	while (d != f)
  	{
      nodes.insert(debut->GetData().GetSource());
      nodes.insert(debut->GetData().GetCible());
  	}

    //ecriture des nodes
    set <string, greater <string> > :: iterator itr;
    for (itr = nodes.begin(); (itr != nodes.end()) && monFlux.good(); ++itr)
    {
        monFlux << *itr << ";" << endl;
    }

    //ecriture des relations entre nodes et de leur cardinalité
    d=req.begin());
    f=req.end());
  	while ((d != f) && monFlux.good())
  	{
  		monFlux << debut->GetData().GetSource() << " -> " ;
      monFlux << debut->GetData().GetCible()  << " [label=\"" ;
      monFlux << debut->GetScore()  << "\"];" << endl;
  	}
  }
  else
  {
    cerr << "Echec d'ouverture du fichier " << nomFichier << '.' << endl;
    exit (2);
  }

} //----- fin de GenerateGraph
