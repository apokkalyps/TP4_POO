#include <iostream>
#include <string>

struct Restrictions
// extensions indique si l'option "-e" est demandee.
// heure indique l'heure demandee par l'utilisateur. 25 signifie pas d'heure demandee.
{
	bool extensions;
	char heure;
	Restriction (bool e, char h) : extension (e), heure (h) {}
};

int main ( int argc, char *argv[])
{
	// Definitions prealables
	Restrictions restr;
	restr.extensions = false;
	restr.heure = 25;
	string source ( argv [argc--]);
	
  // Lecture des arguments
	for (int i=1; i<argc; i++)
	{
		if (argv [i] == "-e")
		{
			restr.extensions = true;
		} else if (argv [i] == 
	}
  return 0;
}
