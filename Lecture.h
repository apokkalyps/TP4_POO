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
#include "CountingMap.h"
#include "CourteRequete.h"
#include "Main.h"
#include <string>

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Requete{
  string IP                    ;
  string userName              ;
  string authenticatedUserName ;
  string jour                  ;
  string mois                  ;
  string annee                 ;
  string heure                 ;
  string minute                ;
  string seconde               ;
  string fuseau                ;
  string type                  ;
  string URL_cible                 ;
  string protocole             ;
  string status                ;
  string data                  ;
  string URL_source                 ;
  string navigateur            ;
};


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
template <typename RequeteType, typename HashF>
void LectureLogs(string fname, struct Restrictions & r, 
  CountingMap<RequeteType, HashF> & requetes);
// Mode d'emploi :
//
// Contrat :
//


bool valideOption ( struct Requete );
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


//------------------------------------------------------------------ PROTEGE
//------------------------------------------------------- Methodes protegees --
//----------------------------------------------------- Attributs protégés
  //Historique* historique;
  string file_Name;
  struct Restrictions regle;
  string restrictedFormats[7] = {TIFF, JPEG, GIF, PNG, RAW, CSS, JS};

#endif // LECTURE_H
