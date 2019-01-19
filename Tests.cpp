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
#include "CountingMap.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Fonctions privées

static void Test_PaireCountingMap ()
// Mode d'emploi :
//  Effectue des tests pour vérifier le bon fonctionnement de la struct Paire.
// Contrat :
//  Aucun.
{
    Paire <string> paire1 ("paire 1", 1);
    Paire <float> paire2 (3.1415, 2);
    Paire <string> paire3 ("paire 3", 3);
    Paire <string> paire4 ("a_paire 4", 4);
    cout << "Paire 1 : " << paire1 << endl;
    cout << "Paire 2 : " << paire2 << endl;
    cout << "Paire 3 : " << paire3 << endl;
    cout << "Paire 4 : " << paire4 << endl;

    cout << boolalpha;
    cout << "Paire3 < Paire1 ? " << (paire3 < paire1) << endl;
    cout << "Paire1 < Paire3 ? " << (paire1 < paire3) << endl;
    cout << "Paire4 < Paire1 ? " << (paire4 < paire1) << endl;
    cout << "Paire2 < Paire2 ? " << (paire2 < paire2) << endl;

    cout << noboolalpha;
} //----- fin de Test_PaireCountingMap


// Test de CountingMap avec des String
struct HashF_String 
// Structure contenant juste une fonction de hashage.
// Source : algorithme djb2 du site http://www.cse.yorku.ca/~oz/hash.html.
{
    size_t operator () (const string & s) const
    {
        const char * str = s.c_str();
        size_t hash = 5381;
        int c;

        while ((c = *str++))
        {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }

        return hash; 
    }
};
struct EqualF_String
// Structure contenant juste une fonction d'égalité.
{
    bool operator () (const string & a, const string & b) const
    {
        return !a.compare(b);
    }
};
void Test_CountingMap_String ()
{
    CountingMap <string, HashF_String, EqualF_String> toto;
    // On déclare une CountingMap de string avec nos hash et égal.
    toto.Ajouter (string("Bonjour"));
    toto.Ajouter (string("Bonjour"));
    toto.Ajouter (string("Au revoir."));
    toto.Exporter (cout);
}

//---------------------------------------------------- Variables statiques
static void (*proceduresDeTests[]) () = 
// Tableau de pointeurs de fonctions facilitant l'accès aux procédures.
{
    Test_PaireCountingMap,
    Test_CountingMap_String,
    nullptr // Inutile donc indispensable
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void AfficheArgs ( char * * args, int nbr_args )
{
    cout << "Affichage des " << nbr_args << " arguments : " << endl;
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
    // Recherche du max des procédures de test :
    size_t nbr_procedures=0;
    while (proceduresDeTests[nbr_procedures] != nullptr)
    {
        nbr_procedures++;
    }

    if (numTest == -1)
    {
        for (unsigned int i=0; i<nbr_procedures; i++)
        {
            proceduresDeTests[i]();
        }
    } else
    {
        if (numTest >= nbr_procedures)
        {
            cerr << "Indice de procédure invalide." << endl;
        }
        else
        {
            proceduresDeTests[numTest]();
        }
    }

    cout << "Fin des jeux de tests." << endl;
    exit (0);
}