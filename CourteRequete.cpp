/*************************************************************************
                    CourteRequete  -  requête Web avec source et cible
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//- Réalisation de la classe <CourteRequete> (fichier CourteRequete.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "CourteRequete.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------------------Classes-fonctions
size_t HashF_CourteRequete::operator () (const CourteRequete & cr) const
// Algorithme : 
//  Algorithme djb2 issu du site http://www.cse.yorku.ca/~oz/hash.html.
//  Appliqué deux fois car deux strings.
{
    const char * str1 = cr.source.c_str();
    size_t hash1 = 5381;
    int c;

    while ((c = *str1++))
    {
        hash1 = ((hash1 << 5) + hash1) + c; /* hash1 * 33 + c */
    }

    const char * str2 = cr.cible.c_str();
    size_t hash2 = 5381;
    int c;

    while ((c = *str2++))
    {
        hash2 = ((hash2 << 5) + hash2) + c; /* hash2 * 33 + c */
    }
    return hash1+hash2;
}

bool EqualF_CourteRequete::operator () 
    (const CourteRequete & a, const CourteRequete & b) const
{
    return a == b;
}

//----------------------------------------------------- Méthodes publiques
// type CourteRequete::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
CourteRequete & CourteRequete::operator = ( const CourteRequete & cr )
{
	source = cr.source;
	cible = cr.cible;
} //----- Fin de operator =

ostream & operator << (ostream & os, const CourteRequete & cr)
{
	return (os << "Requete { " << cr.source << " -> " << cr.cible << " }");
} //----- Fin de operator<< 

bool CourteRequete::operator == ( const CourteRequete & cr)
{
	return ( ! cible.compare(cr.cible)) && ( ! source.compare(cr.source));
} //------ Fin de operator==


//-------------------------------------------- Constructeurs - destructeur
CourteRequete::CourteRequete ( const CourteRequete & cr ) :
	source (cr.source),
	cible (cr.cible)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <CourteRequete>" << endl;
#endif
} //----- Fin de CourteRequete (constructeur de copie)

 CourteRequete::CourteRequete ( const Requete & req ) :
 	source (req.URL_source),
 	cible (req.URL_cible)
 {
 #ifdef MAP
    cout << "Appel au constructeur de <CourteRequete> par copie ";
    cout << "d'une Requete entiere." << endl;
#endif
 } //----- Fin de CourteRequete (constructeur par copie de Requete)


CourteRequete::CourteRequete ( ) :
	source(),
	cible()
{
#ifdef MAP
    cout << "Appel au constructeur de <CourteRequete>" << endl;
#endif
} //----- Fin de CourteRequete


CourteRequete::~CourteRequete ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <CourteRequete>" << endl;
#endif
} //----- Fin de ~CourteRequete


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

