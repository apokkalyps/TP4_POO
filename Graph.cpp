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
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "CountingMap.h"
#include "CourteRequete.h"


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
void GenerateGraph ( const CountingMap<RequeteType, HashF> & liste )
// Algorithme :
//
{
  //Déclaration d'un flux permettant d'écrire dans un fichier.
  ofstream monFlux(nomFichier.c_str());

  if(monFlux)
  {
    vector<Paire<CourteRequete>> req = liste->GetAll();
    set <string, greater <string> > nodes;

    //Recuperation des nodes uniques
    vector<Paire<CourteRequete>>::const_iterator
    d (req.begin()),
    f (req.end());
  	while (d != f)
  	{
      nodes.insert(debut->GetData().GetSource());
      nodes.insert(debut->GetData().GetCible());
  	}
    set <string, greater <string> > :: iterator itr;
    for (itr = nodes.begin(); itr != nodes.end(); ++itr)
    {
        monFlux << *itr << ";" << endl;
    }

    //Affichage des relations et de leru label
    vector<Paire<CourteRequete>>::const_iterator
    debut (req.begin()),
    fin (req.end());
  	while (debut != fin)
  	{
  		monFlux << debut->GetData().GetSource() << " -> " ;
      monFlux << debut->GetData().GetCible()  << " [label=\"" ;
      monFlux << debut->GetData().GetScore()  << "\"];" << endl;
  	}

  }
  else
  {
     cerr << "ERREUR: Impossible d'ouvrir le fichier." << endl;
  }

} //----- fin de GenerateGraph
