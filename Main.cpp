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
template <typename RequeteType, typename HashF>
extern void LectureLogs(string fname, struct Restrictions & r,
  CountingMap<RequeteType, HashF> & requetes);


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static string graphviz;
static string source;
static Restrictions restr;
static CountingMap <CourteRequete, HashF_CourteRequete> requetes;

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
	if ( nbr_args < 2 || nbr_args > 7 || source[0] == '-')
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
			if (restr.extensions == true)
			{
				cerr << "Trop d'options : \"-e\" deja demande." << endl;
				exit (1);
			}

			restr.extensions = true;
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
			if ( restr.heure != -1 )
			{
				cerr << "Trop d'options : \"-t\" deja demande." << endl;
				exit (1);
			}

			++i;
			unsigned int h = (unsigned int) stoi (args[i]);
			if (h > 23)
			{
				cerr << "Heure demandee invalide." << endl;
				exit (1);
			}

			restr.heure = h;
		} else
		{
			cerr << "Erreur, option invalide." << endl;
		}
	}
}

static void VerificationDroits (ifstream * ifs, ofstream * ofs)
// Mode d'emploi :
//	Vérifie les droits d'accès aux fichiers.
//	Crée aussi les flux si besoin.
// Contrat :
//	Aucun !
{
	ifs = new ifstream(source.c_str());
	if ( ! *ifs)
	{
		cerr << "Echec de lecture du fichier log !" << endl;
		delete ifs;
		exit (2);
	}

	if ( ! graphviz.empty () )
	{
		ofs = new ofstream (graphviz.c_str(), ios_base::app);
		if ( ! *ofs )
		{
			cerr << "Echec d'ouverture du fichier " << graphviz << '.' << endl;
			delete ofs;
			exit (2);
		}
	}
}

static void AfficheTop10 ()
{
} //----- Fin de AfficheTop10.

static void GenererGraphe ()
{
} //----- Fin de GenererGraphe.


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc, char *argv[])
{
	
#ifdef MAP
    cout << "Appel du main avec les parametres suivants : " << endl;
    AfficheArgs(argv, argc);
#endif // MAP

   // Definitions prealables
	restr = Restrictions (false, -1);

	// Lecture des arguments
	LectureArguments (argv, argc);
#ifdef MAP
	cout << "Restrictions: " << restr << endl;
	cout << "Source: " << source << ", export vers: " << graphviz << endl;
#endif

	// Verification des droits sur les fichiers.
	ifstream * ifs_p = nullptr;
	ofstream * ofs_p = nullptr;
	VerificationDroits(ifs_p, ofs_p);
	

	// Lecture du fichier d'entree
	LectureLogs (source, restr, requetes);

	// Production de la sortie
	if (graphviz.empty())
	{
		AfficheTop10();
	}
	else
	{
		GenererGraphe();
	}
	return 0;
} //----- fin de Main.

Restrictions :: Restrictions (bool e, unsigned char h) : 
	extensions (e), heure (h) 
{
} // ----- fin du constructeur de Restrictions.

