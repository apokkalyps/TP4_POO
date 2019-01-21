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
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <fstream>
#include <cstring>
#include "CountingMap.h"
#include "CourteRequete.h"
#include <string>
#include <algorithm>
#include <set>
#include <iterator>
#include <vector>
#include <unordered_map>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void GenerateGraph ( const CountingMap<RequeteType, HashF> & liste );
// Mode d'emploi :
//
// Contrat :
//

#endif // GRAPH_H
