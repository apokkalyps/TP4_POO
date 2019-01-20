/*************************************************************************
                           Lecture  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Lecture> (fichier Lecture.h) -------------------
#if ! defined ( LECTURE_H )
#define LECTURE_H

//------------------------------------------------------------------------
// Rôle du module <Lecture>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "RequeteTools.h"
#include "CountingMap.h"
#include "CourteRequete.h"
// #include "Main.h"

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
template <typename RequeteType, typename HashF>
void LectureLogs(string & fname, Restrictions & r,
  CountingMap<RequeteType, HashF> & liste);
// Mode d'emploi :
//
// Contrat :
//


bool valideOption ( Requete r );
// Mode d'emploi :
//
// Contrat :
//

void Parcours ( void );
// Mode d'emploi :
//
// Contrat :
//

string getExtension(string c);
// Mode d'emploi :
//
// Contrat :
//


#endif // LECTURE_H
