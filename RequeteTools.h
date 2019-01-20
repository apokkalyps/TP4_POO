/*************************************************************************
                   RequeteTools  -  outils pour manipuler des requetes
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <RequeteTools> (fichier RequeteTools.h) ---------------
#ifndef REQUETE_TOOLS_H
#define REQUETE_TOOLS_H

//------------------------------------------------------------------------
// Rôle du module <RequeteTools>
//	Contient les structures et outils éventuels pour manipuler des requêtes.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Requete
// Structure contenant toutes les informations sur une requête.
{
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
  string URL_cible             ;
  string protocole             ;
  string status                ;
  string data                  ;
  string URL_source            ;
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


#endif // REQUETE_TOOLS_H
