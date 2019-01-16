#include <iostream>
#include <string>

struct Restrictions
// extensions indique si l'option "-e" est demandee.
// heure indique l'heure demandee par l'utilisateur. -1 signifie pas d'heure demandee.
{
	bool extensions;
	unsigned char heure;
	Restriction (bool e, unsigned char h) : extension (e), heure (h) {}
};

int main ( int argc, char *argv[])
{
	// Definitions prealables
	Restrictions restr (false, -1);
	string source ( argv [argc--]);
	string graphviz;
	
  // Lecture des arguments
	for (int i=1; i<argc; i++)
	{
		if (argv [i] == "-e")
		{
			if (restr.extensions == true)
			{
				cerr << "Trop d'options : \"-e\" deja demande." << endl;
				exit (1);
			}
			
			restr.extensions = true;
		} else if (argv [i] == ("-g")
		{
			if ( ! graphviz.empty () )
			{
				cerr << "Trop d'options : \"-g\" deja demande." << endl;
				exit (1);
			}
			
			graphviz = argv [i+1];
			++i;
		} else if (argv [i] == "-t")
		{
			if ( restr.heure != -1 )
			{
				cerr << "Trop d'options : \"-t\" deja demande." << endl;
				exit (1);
			}
			
			++i;
			unsigned int h = stoi (argv[i]);
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
	return 0;
}
