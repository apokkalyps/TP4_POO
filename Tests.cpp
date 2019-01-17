#include "Tests.h"

#include <iostream>
using namespace std;

void AfficheArgs ( char * * args, int nombre )
{
    for (int i=0; i<nombre; ++i)
    {
        cout << i << " : " << args[i] << endl;
    }
}
