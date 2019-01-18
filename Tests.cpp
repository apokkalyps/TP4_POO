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

//------------------------------------------------------ Fonctions privées

//---------------------------------------------------- Variables statiques
void (*proceduresDeTests[]) () = 
// Tableau de pointeurs de fonctions facilitant l'accès aux procédures.
{
    nullptr // Inutile donc indispensable
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void AfficheArgs ( char * * args, int nbr_args )
{
    cout << "Affichage des " << nbr_args << "arguments : " << endl;
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

void LanceTest (unsigned short numTest = -1)
{
    if (numTest == -1)
    {
        int i = 0;
        while (proceduresDeTests[i] != nullptr)
        {
            proceduresDeTests[i]();
        }
    } else
    {
        proceduresDeTests[numTest]();
    }
}