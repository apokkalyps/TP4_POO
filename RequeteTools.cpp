/*************************************************************************
                           RequeteTools  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <RequeteTools> (fichier RequeteTools.cpp) -----------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <string>
#include "RequeteTools.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Fonctions privées

//---------------------------------------------------- Variables statiques


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
Restrictions :: Restrictions (bool e, unsigned char h) : 
	extensions (e), heure (h) 
{
} // ----- fin du constructeur de Restrictions.

std::ostream & operator << (ostream & os, const Restrictions & res)
{
    os << boolalpha << "[ext=" << res.extensions << ", heure=";
    os << ((res.heure > 23) ? string("?") : to_string(res.heure)) << ']';
    return os;
} //----- fin de Operator<< pour Restrictions.