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
#include "Historique.h"
#include <string>

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
  string URL_R                 ;
  string protocole             ;
  string status                ;
  string data                  ;
  string URL_r                 ;
  string navigateur            ;
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Lecture(const Historique* h, string fname, options..);

bool valideOption ( struct Requete );
// Mode d'emploi :
//
// Contrat :
//

void Parcours ( void ) const;
// Mode d'emploi :
//
// Contrat :
//

//------------------------------------------------------------------ PROTEGE
//------------------------------------------------------- Methodes protegees --
//----------------------------------------------------- Attributs protégés
  Historique* historique;
  string file_Name;

#endif // LECTURE_H
