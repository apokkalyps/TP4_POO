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
extern RestrictionList restr;

using namespace std;
//------------------------------------------------------------- Constantes
//string * file_Name; // Nom du fichier de logs en lecture
/*extern RestrictionList restr;
static RestrictionList * regle; // Les restrictions appliquées aux requêtes choisies.
*/
static const int nbRF = 7; // Nombre de restrictedFormats
static const string localURL = "http://intranet-if.insa-lyon.fr"; //URL locale
static const string restrictedFormats[nbRF] =
  {"TIFF", "JPEG", "GIF", "PNG", "RAW", "CSS", "JS"}; // Formats interdits.

template <typename RequeteType, typename HashF>
CountingMap <RequeteType, HashF> * requete; // Les requêtes

//------------------------------------------------------------------ Types


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


bool valideOption ( const Requete & r );
// Mode d'emploi :
//
// Contrat :
//

bool Parcours ( void );
// Mode d'emploi :
//
// Contrat :
//

string getExtension(string c);
// Mode d'emploi :
//
// Contrat :
//

string checkLocal(string c);
// Mode d'emploi :
//
// Contrat :
//


template <typename RequeteType, typename HashF>
void LectureLogs(/*string & fname, RestrictionList & restr,*/
  CountingMap<RequeteType, HashF> * liste)
// Mode d'emploi :
//
// Contrat :
//
{
  /*extern RestrictionList restr;
  regle = &restr;*/
  requete<RequeteType, HashF> = liste;
  if ( ! Parcours() )
  {
  	extern string source;
	cerr << "ERREUR: Impossible d'ouvrir le fichier \"" << source;
	cerr << "\"." << endl;
  	delete requete<RequeteType, HashF>;
  	exit(2);
  }
} //----- fin de LectureLogs

#endif // LECTURE_H
