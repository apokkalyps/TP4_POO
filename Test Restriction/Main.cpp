/*************************************************************************
                           Main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Main> (fichier Main.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Main.h"
#include "Tests.h"
#include "CountingMap.h"
#include "RequeteTools.h"
#include "Lecture.h"



///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static string graphviz;
static string source;
static RestrictionList restr;
static CountingMap <CourteRequete, HashF_CourteRequete> * requetes;

//------------------------------------------------------ Fonctions privées
static void LectureArguments ( char ** args, int nbr_args)
// Mode d'emploi :
//	Traite les options saisies par l'utilisateur lors de l'appel du programme.
//	args : liste des paramètres tels que fournis lors de l'appel du main.
// 	nbr_args : nombre de paramètres tel que fourni lors de l'appel du main.
// Contrat : 
//	restr a été construit par défaut, nbr_args est compatible avec args.
{
	source = args[--nbr_args];
	if ( nbr_args < 1 || nbr_args > 6 || source[0] == '-')
	{
		cerr << "Syntaxe d'appel incorrecte. Verifiez votre syntaxe avec";
		cerr << " le manuel." << endl;
		exit (1);
	}

	// Jeux de tests ?
	// Si oui, on doit aussi spécifier en option l'indice du test.
	if ( ! strcmp (args[1], "--tests"))
	{
		LanceTest(stoi(string(args[2])));
	}

	// Sinon analyse des options
	for (int i=1; i<nbr_args; i++)
	{
		if ( ! strcmp(args [i], "-e"))
		{
			Restriction_Extension re;
			restr.liste.push_front(new Restriction_Extension(re));
		} else if ( ! strcmp( args [i], "-g"))
		{
			if ( ! graphviz.empty () )
			{
				cerr << "Trop d'options : \"-g\" deja demande." << endl;
				exit (1);
			}

			graphviz = args [i+1];
			++i;
		} else if ( ! strcmp( args [i], "-t"))
		{
			++i;
			unsigned int h = (unsigned int) stoi (args[i]);
			if (h > 23)
			{
				cerr << "Heure demandee invalide." << endl;
				exit (1);
			}
			restr.liste.push_front(new Restriction_Heure (h));
		} else
		{
			cerr << "Erreur, option invalide : \"" << args[i] << "\"." << endl;
			exit(1);
		}
	}
}

static void VerificationDroits ()
// Mode d'emploi :
//	Vérifie les droits d'accès aux fichiers.
//	Crée aussi les flux si besoin.
// Contrat :
//	Aucun !
{
	ifstream ifs (source.c_str());
	if ( ! ifs)
	{
		cerr << "Echec de lecture du fichier log !" << endl;
		exit (2);
	}

	if ( ! graphviz.empty () )
	{
		ofstream ofs (graphviz.c_str(), ios_base::app);
		if ( ! ofs )
		{
			cerr << "Echec d'ouverture du fichier " << graphviz << '.' << endl;
			exit (2);
		}
	}
}

static void AfficheTop10 ()
// Mode d'emploi :
//	Affiche les dix URL cibles les plus visitées.
// Contrat :
//	Le pointeur 'requetes' existe.
// Algorithme :
//	On compte d'abord le nombre de cibles avec le nombre de fois qu'elles
//	ont été atteintes, au travers d'une nouvelle CountingMap.
//	Ensuite, on affiche les dix meilleures.
{
	CountingMap <string> c_cibles; // Compteur des "hit" par cible
	
	vector<Paire<CourteRequete>> req = requetes->GetAll();
	vector<Paire<CourteRequete>>::const_iterator 
		debut (req.begin()), 
		fin (req.end());
	while (debut != fin)
	{
		c_cibles.Ajouter (debut->GetData().GetCible(), debut->GetScore());
		++debut;
	}
	vector<Paire<string>> dest (c_cibles.GetTop (10));
	
	cout << "Liste des " << dest.size() << " cibles les plus visitées :";
	unsigned int compteur = 1;
	vector<Paire<string>> :: const_iterator
		debut2 (dest.begin()),
		fin2 (dest.end());
	while (debut != fin)
	{
		cout << compteur << ". \"" << debut2->GetData() << " avec ";
		cout << debut2->GetScore() << " visites." << endl;
		++compteur;
		++debut2;
	}
	cout << "Fini." << endl;
} //----- Fin de AfficheTop10.

static void GenererGraphe (...)
{
} //----- Fin de GenererGraphe.


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, char *argv[])
{
	
#ifdef MAP
    AfficheArgs(argv, argc);
#endif // MAP

   // Lecture des arguments
	LectureArguments (argv, argc);
#ifdef MAP
	cout << restr;
	cout << (graphviz.empty() ? "(null)" : graphviz) << endl;
#endif

	// Verification des droits sur les fichiers.
	VerificationDroits();
	requetes = new CountingMap <CourteRequete, HashF_CourteRequete>;

	// Lecture du fichier d'entree
	LectureLogs (source, restr, requetes);

	// Production de la sortie
	if (graphviz.empty())
	{
		AfficheTop10();
	}
	else
	{
		GenererGraphe(graphviz, requetes->GetAll());
	}
	delete requetes;
	return 0;
} //----- fin de Main.

