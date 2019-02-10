/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Graph> (fichier Graph.h) -------------------
#if ! defined ( GRAPH_H )
#define GRAPH_H

//------------------------------------------------------------------------
// Rôle du module <Graph>
// Création d'un graphViz à partir d'un vecteur de paires de courtes requetes
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>

#include "CourteRequete.h"
#include "Paire.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef vector<Paire<CourteRequete>> liste;

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void GenerateGraph (const liste & requetes, const string & nomFichier);
// Mode d'emploi :
//   Ecriture dans le fichier nomFichier.dot du graph des requetes de liste
// Contrat :
//    aucun

#endif // GRAPH_H
