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
#include <sstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Main.h"
#include "Tests.h"
#include "CountingMap.h"
#include "RequeteTools.h"
#include "Lecture.h"
#include "CourteRequete.h"
extern void GenerateGraph (const vector<Paire<CourteRequete>> & 
	requetes, const string & nomFichier);


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static string graphviz;
static RestrictionList restr;
static CountingMap <CourteRequete, HashF_CourteRequete> * requetes;
static string source;

//------------------------------------------------------ Fonctions privées
static void LectureArguments ( char ** args, int nbr_args)
// Mode d'emploi :
//	Traite les options saisies par l'utilisateur lors de l'appel du programme.
//	args : liste des paramètres tels que fournis lors de l'appel du main.
// 	nbr_args : nombre de paramètres tel que fourni lors de l'appel du main.
// Contrat : 
//	nbr_args est compatible avec args.
{
	// Jeux de tests ?
	// Si oui, on doit aussi spécifier en option l'indice du test.
	if ( ! strcmp (args[1], "--tests"))
	{
		if (nbr_args == 2 && StringIsNumeric (args[2]))
		{
			LanceTest (args[2]);
		}
		else
		{
			LanceTest();
		}
	}

	// Lecture de la source
	source = args[--nbr_args];
	if (GetExtension(source) != "log")
	{
		source += ".log";
	}
	if ( nbr_args < 1 || nbr_args > 6 || source[0] == '-')
	{
		Erreur (OPTION, "Syntaxe d'appel incorrecte.");
	}



	// Sinon analyse des options
	for (int i=1; i<nbr_args; i++)
	{
		// Cas : restriction sur les extensions
		if ( ! strcmp(args [i], "-e"))
		{
			restr.Ajouter(new Restriction_Extension);
		}

		// Cas : demande d'export en GraphViz
		else if ( ! strcmp( args [i], "-g"))
		{
			if ( ! graphviz.empty () )
			{
				Erreur (OPTION, "\"-g\" deja demande.");
			}
			else
			{
				if (i+1>=nbr_args)
				{
					Erreur (OPTION, "Syntaxe d'appel incorrecte.");
				}
				else
				{
					graphviz = args[i+1];
					if (GetExtension(graphviz) != "dot")
					{
						graphviz += ".dot";
						++i;
					}
				}

			}
		} 

		// Cas : restriction sur le temps
		else if ( ! strcmp( args [i], "-t"))
		{
			if (StringIsNumeric(args[i+1]))
			{
				++i;
				unsigned int h = (unsigned int) stoi (args[i]);
				if (h > 23)
				{
					Erreur (OPTION, "Heure demandee invalide.");
				}
				restr.Ajouter(new Restriction_Heure (h));
			} else 
			{
				Erreur (OPTION, "Heure demandee invalide.");
			}


		} else
		{
			ostringstream oss;
			oss << "Option invalide : " << "\"" << args[i] << "\".";
			Erreur (OPTION, oss.str());
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
		Erreur (FICHIER, "Lecture du fichier Log.");
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
			Erreur (FICHIER, "Ecriture impossible du GraphViz.");
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
	if (req.size() < 1)
	{
		cout << "Aucune requête à afficher." << endl;
		return;
	}


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
	LectureLogs <CourteRequete, HashF_CourteRequete>(requetes, source, restr);

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

bool StringIsNumeric (const string & s)
// Algorithme : 
// https://stackoverflow.com/questions/4654636/
{
	return (!s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end());
} //----- fin de StringIsNumeric

void Erreur (Erreur_e err, const string & message)
{
	int exit_code;
	switch (err)
	{
		case OPTION:
		{
			cerr << "Problème d'option : ";
			exit_code = 1;
			break;
		}
		case FICHIER:
		{
			cerr << "Problème de fichier : ";
			exit_code = 2;
			break;

		}
		default:
		// Ce cas n'est pas sensé se produire.
		{
			cerr << "Problème inconnu : ";
			exit_code = -1;
			break;
		}
	}
	cerr << "\033[31;1m" << message << "\033[0m" << " Arrêt." << endl;
	exit (exit_code);

} //----- fin de Erreur
