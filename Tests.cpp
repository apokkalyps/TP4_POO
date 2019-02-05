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
#include <vector>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Tests.h"
#include "CountingMap.h"
#include "Paire.h"
#include "CourteRequete.h"
#include "RequeteTools.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------ Fonctions privées

static void Test_Paire ()
// Mode d'emploi :
//  Effectue des tests pour vérifier le bon fonctionnement de la struct Paire.
// Contrat :
//  Aucun.
{
    cout << " >> TEST CHOISI : CLASSE GENERIQUE PAIRE <<" << endl << endl;
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
    
    cout << "Paire par copie : ";
    Paire<string> paire5 (paire1);
    cout << paire5 << endl;
    cout << "Paire par affectation : ";
    paire5 = paire3;
    cout << paire5 << endl;

    cout << noboolalpha;
} //----- fin de Test_Paire


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

static void Test_CountingMap_String ()
{
    cout << " >> TEST CHOISI : CLASSE GENERIQUE COUNTINGMAP AVEC DES STRING <<";
    cout << endl << endl;

    CountingMap <string, HashF_String> toto;
    // On déclare une CountingMap de string avec nos hash et égal.
    cout << "Taille : " << toto.GetTaille() << endl;
    toto.Exporter (); // cout par défaut
    toto.Ajouter (string("Deux"));
    toto.Ajouter (string("Quatre"));
    toto.Ajouter (string("Trois"));
    toto.Ajouter (string("Trois"));
    toto.Ajouter (string("Deux"));
    toto.Ajouter (string("Quatre"));
    toto.Ajouter (string("Quatre"));
    toto.Ajouter (string("Trois"));
    toto.Ajouter (string("Un"));
    toto.Ajouter (string("Quatre"));

    toto.Exporter (cout);
    cout << "Combien de \"Deux\" ? " << toto.CombienDe("Deux") << endl;
    cout << "Combien de \"aaa\" ? " << toto.CombienDe("aaa") << endl;
    cout << "Combien de \"\" ? " << toto.CombienDe("") << endl;

    cout << "Vecteur de tous les éléments : " << endl;
    vector <Paire <string> > lesTop = toto.GetAll();
    vector<Paire<string>>::const_iterator 
        debut (lesTop.cbegin()), 
        fin (lesTop.cend()); 
    while (debut != fin)
    {
        cout << *debut << '.' << endl;
        ++debut;
    }

    cout << "Vecteur trié des 2 meilleurs éléments : " << endl;
    lesTop = toto.GetTop(2);
    debut = lesTop.cbegin();
    fin  = lesTop.cend(); 
    while (debut != fin)
    {
        cout << *debut << '.' << endl;
        ++debut;
    }
}

static void Test_CourteRequete ()
{
	typedef CourteRequete C;
	C a ;
	cout << "CourteRequete vide : " << a << endl;
	C b (string("Source_1"), string("Cible_1"));
	cout << "CourteRequete : " << b << endl;
	cout << "Egalite des deux ? " << boolalpha;
	cout << (a == b) << endl;
	C c ("Source_1", "Cible_1");
	cout << "Egalite ? " << (a == c) << endl;
	cout << "Construction par copie : ";
	C d (c);
	cout << ", egalite ? " << (c==d) << endl;
	cout << "Creation par affectation : " << endl;
	C e = C();
}

static void Test_Restriction ()
{
	RestrictionList l;
	cout << "Liste de restrictions vide: " << endl;
	cout << l << endl;
	
	cout << "Ajout d'une restr ext: " << endl;
	l.Ajouter (new Restriction_Extension);
	cout << l << endl;
	cout << "Ajout d'une restr heure: " << endl;
	l.Ajouter (new Restriction_Heure(2));
	cout << l << endl;
	cout << "Ajout d'une restr ext: " << endl;
	l.Ajouter (new Restriction_Extension);
	cout << l << endl;
	cout << "Ajout d'une restr heure (Attention ça va planter) : " << endl;
	l.Ajouter (new Restriction_Heure(5));
	cout << l << endl;
}

//---------------------------------------------------- Variables statiques
static void (*proceduresDeTests[]) () = 
// Tableau de pointeurs de fonctions facilitant l'accès aux procédures.
{
    Test_Paire,
    Test_CountingMap_String,
    Test_CourteRequete,
    Test_Restriction,
    nullptr // Inutile donc indispensable
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void AfficheArgs ( char * args [], const int nbr_args )
{
    cout << "Affichage des " << nbr_args << " arguments : " << endl;
    for (int i=0; i<nbr_args; ++i)
    {
        cout << i << " : " << args[i] << endl;
    }
} //----- fin de AfficheArgs.

void LanceTest (const char * numTestArray)
{


    // Recherche du max des procédures de test :
    size_t nbr_procedures=0;
    while (proceduresDeTests[nbr_procedures] != nullptr)
    {
        nbr_procedures++;
    }

    // On verifie si numTestArray est un nombre ou pas.
    // Algorithme : 
    // https://stackoverflow.com/questions/4654636/
    string numTestString (numTestArray);
    unsigned int numTest;
    
    if (!numTestString.empty() && std::find_if(numTestString.begin(), 
        numTestString.end(), [](char c) { return !std::isdigit(c); }) == numTestString.end())
    {
        numTest = stoi (numTestString);
    }
    else
        numTest = -1;

    if (numTest == (unsigned int)-1)
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
