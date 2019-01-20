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
static string file_Name; // Nom du fichier de logs en lecture
static Restrictions regle; // Les restrictions appliquées aux requêtes choisies.
static const int nbRF = 7; // Nombre de restrictedFormats
static const string restrictedFormats[nbRF] = 
  {"TIFF", "JPEG", "GIF", "PNG", "RAW", "CSS", "JS"}; // Formats interdits.

template <typename RequeteType, typename HashF>
static CountingMap <RequeteType, HashF> * requete; // Les requêtes

//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


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

template <typename RequeteType, typename HashF>
void LectureLogs(string & fname, Restrictions & r,
  CountingMap<RequeteType, HashF> * liste)
// Mode d'emploi :
//
// Contrat :
//
{
  regle = r;
  file_Name = fname;
  requete<RequeteType, HashF> = liste;
  Parcours();
} //----- fin de LectureLogs

#endif // LECTURE_H
