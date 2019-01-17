#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "main.h"
#include "Tests.h"

using namespace std;

Restrictions :: Restrictions (bool e, unsigned char h) : extensions (e), heure (h) {}

int main ( int argc, char *argv[])
{
#ifdef MAP
    cout << "Appel du main avec les parametres suivants : " << endl;
    AfficheArgs(argv, argc);
#endif // MAP

	// Definitions prealables
	Restrictions restr (false, -1);
	string source ( argv [argc--]);
	string graphviz;

	// Lecture des arguments
	for (int i=1; i<argc; i++)
	{
		if ( ! strcmp(argv [i], "-e"))
		{
			if (restr.extensions == true)
			{
				cerr << "Trop d'options : \"-e\" deja demande." << endl;
				exit (1);
			}

			restr.extensions = true;
		} else if ( ! strcmp( argv [i], "-g"))
		{
			if ( ! graphviz.empty () )
			{
				cerr << "Trop d'options : \"-g\" deja demande." << endl;
				exit (1);
			}

			graphviz = argv [i+1];
			++i;
		} else if ( ! strcmp( argv [i], "-t"))
		{
			if ( restr.heure != -1 )
			{
				cerr << "Trop d'options : \"-t\" deja demande." << endl;
				exit (1);
			}

			++i;
			unsigned int h = (unsigned int) stoi (argv[i]);
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

	// Verification des droits sur les fichiers.
	{
		ifstream ifs (source.c_str());
		if ( ! ifs )
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

	// Lecture du fichier d'entree

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
}

std::ostream & operator << (ostream & os, const Restrictions & res)
{
    os << boolalpha << "ext=" << res.extensions << ", heure=";
    //os << ((res.heure > 23) ? string("undefined") : to_string(res.heure)) << '.';
    return os;
}
