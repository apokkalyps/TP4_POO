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
extern void GenerateGraph (const vector<Paire<CourteRequete>> & 
	requetes, const string & nomFichier);



///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static string graphviz;
/*static*/ RestrictionList restr;
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
	// Lecture de la source
	source = args[--nbr_args];
	if (getExtension(source) != ".log")
	{
		source += ".log";
	}
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
			restr.Ajouter(new Restriction_Extension(re));
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
			restr.Ajouter(new Restriction_Heure (h));
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
#ifdef MAP
	else
	{
		cout << "Fichier source \"" << source << "\" OK." << endl;
	}
	ifs.close();
#endif // MAP

	if ( ! graphviz.empty () )
	{
		ofstream ofs (graphviz.c_str(), ios_base::app);
		if ( ! ofs )
		{
			cerr << "Echec d'ouverture du fichier " << graphviz << '.' << endl;
			exit (2);
		}
#ifdef MAP
		else
		{
			cout << "Fichier destination \"" << graphviz;
			cout << "\" OK." << endl;
		}
		ofs.close();
#endif // MAP
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
		debut (req.cbegin()), 
		fin (req.cend());
	while (debut != fin)
	{
		c_cibles.Ajouter (debut->GetData().GetCible(), debut->GetScore());
		++debut;
	}
	vector<Paire<string>> dest (c_cibles.GetTop (10));
	
	cout << "Liste des " << dest.size() << " cible(s) les plus visitées :" << endl;
	unsigned int compteur = 1;
	vector<Paire<string>> :: const_iterator
		debut2 (dest.cbegin()),
		fin2 (dest.cend());
	while (debut2 != fin2)
	{
		cout << compteur << ". \"" << debut2->GetData() << "\" avec ";
		cout << debut2->GetScore() << " visites." << endl;
		++compteur;
		++debut2;
	}
	cout << "Fini." << endl;
} //----- Fin de AfficheTop10.


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
	cout << "Source: " << source << ", export vers: ";
	cout << (graphviz.empty() ? "(null)" : graphviz) << endl;
#endif // MAP

	// Verification des droits sur les fichiers.
	VerificationDroits();
	requetes = new CountingMap <CourteRequete, HashF_CourteRequete>;

	// Lecture du fichier d'entree
	LectureLogs (/*source, restr, */requetes);

	// Production de la sortie
	if (graphviz.empty())
	{
		AfficheTop10();
	}
	else
	{
		GenerateGraph(requetes->GetAll(), graphviz);
	}
	delete requetes;
	return 0;
} //----- fin de Main.

