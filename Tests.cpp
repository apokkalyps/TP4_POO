/*************************************************************************
                           Tests  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Tests> (fichier Tests.cpp) -----------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Tests.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void AfficheArgs ( char * * args, int nbr_args )
{
    for (int i=0; i<nbr_args; ++i)
    {
        cout << i << " : " << args[i] << endl;
    }
} //----- fin de AfficheArgs.

std::ostream & operator << (ostream & os, const Restrictions & res)
{
    os << boolalpha << "[ext=" << res.extensions << ", heure=";
    os << ((res.heure > 23) ? string("?") : to_string(res.heure)) << ']';
    return os;
} //----- fin de Operator<< pour Restrictions.