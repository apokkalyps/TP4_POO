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

struct Restrictions
// Structure encapsulant (en public) les requêtes de l'utilisateur
// en matière de restrictions dans la lecture du fichier source.
// > extensions indique si l'option "-e" est demandee.
// > heure indique l'heure demandee par l'utilisateur.
// 		-1 signifie pas d'heure demandee.
{
	bool extensions;
	unsigned char heure;
	explicit Restrictions (bool e = false, unsigned char h = -1); // Constr
};



//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void LectureLogs(const Historique* h, string fname, options..);
// Mode d'emploi :
//
// Contrat :
//


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

string getExtension(string c);
// Mode d'emploi :
//
// Contrat :
//


//------------------------------------------------------------------ PROTEGE
//------------------------------------------------------- Methodes protegees --
//----------------------------------------------------- Attributs protégés
  Historique* historique;
  string file_Name;

  string restrictedFormats[7] = {TIFF, JPEG, GIF, PNG, RAW, CSS, JS};

#endif // LECTURE_H
