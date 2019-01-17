#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>

void AfficheTop10() {}
void GenererGraphe() {}

struct Restrictions
// extensions indique si l'option "-e" est demandee.
// heure indique l'heure demandee par l'utilisateur. -1 signifie pas d'heure demandee.
{
	bool extensions;
	unsigned char heure;
	Restrictions (bool e, unsigned char h);
};

std::ostream & operator << (std::ostream & os, const Restrictions & res);

int main ( int argc, char *argv[]);



#endif // MAIN_H_INCLUDED
