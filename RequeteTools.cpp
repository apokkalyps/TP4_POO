/*************************************************************************
                           RequeteTools  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <RequeteTools> (fichier RequeteTools.cpp) -----------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <string>
#include <locale>
#include <algorithm>
#include "RequeteTools.h"
#include "Main.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef forward_list<Restriction*>::const_iterator it;

//------------------------------------------------------ Fonctions privées

//---------------------------------------------------- Variables statiques


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

ostream & operator << (ostream & os, const Restriction & rs)
{
	return rs.Aff(os);
}

bool RestrictionList::TesterTout (const Requete & req) const
{
	if (taille==0) 
	{
		return true;
	}
	
	for (it debut (liste.cbegin()); debut!=liste.cend(); ++debut)
	{
		if ((**debut)(req) == false)
		{
			return false;
		}
	}
	return true;
} //----- fin de TesterTout

void RestrictionList::Ajouter (Restriction* restr)
{
	for (it debut (liste.cbegin()); debut!=liste.cend(); ++debut)
	{
		if (! ((*debut)->ClassToString().compare (restr->ClassToString())))
		{
			Erreur (OPTION, "Restriction en double.");
		}
	}
	liste.push_front(restr);
	++taille;
} //----- fin de Ajouter

ostream & operator << (ostream & os, const RestrictionList & rl)
{
	it debut (rl.liste.cbegin()), fin (rl.liste.cend());
	if (debut == fin)
	{
		return os << "Aucune restriction." << endl;
	}
	else
	{
		os << "Liste de restrictions :" << endl;
		for (; debut!=fin; ++debut)
		{
			os << " - " << **debut << endl;
		} 
		return os;
	}
} //----- fin de Operator<< pour RestrictionList

RestrictionList::~RestrictionList ()
{
	for (forward_list<Restriction*>::iterator 
		debut (liste.begin()); debut!=liste.end(); ++debut)
	{
		delete *debut;
	}
} //----- fin du destructeur de RestrictionList.

Restriction_Heure::Restriction_Heure (unsigned char h) :
	heure (h)
{
} //----- fin du constructeur de Restriction_Heure

bool Restriction_Heure::operator () (const Requete & req) const
{
	return req.heure.compare(to_string(heure)) == 0;
} //----- fin de Operator() pour Restriction_Heure

ostream & Restriction_Heure::Aff (ostream & os) const
{
	os << "{Restriction: heure dans [" << int(heure) << ", ";
	os << heure+1 << "[}";
	return os;
} //----- fin de Aff pour ostream et Restriction_Heure

string Restriction_Heure::ClassToString () const
{
	return "Restriction_Heure";
} //----- fin de ClassToString

Restriction_Extension::Restriction_Extension ()
{
} //----- fin du constructeur de Restriction_Extension

bool Restriction_Extension::operator () (const Requete & req) const
{
	locale loc; // Pour utiliser toupper
	//string extFichier (toupper(getExtension(req.URL_cible), loc));
	string extFichier (getExtension(req.URL_cible));
	transform (extFichier.begin(), extFichier.end(), extFichier.begin(), ::toupper);

	//to_upper(extFichier);
	for (unsigned int i=0; i<nbRF; ++i)
	{
		if (extFichier.compare(restrictedFormats[i]) == 0)
		{
			return false;
		}
	}
	return true;
} //----- fin de Operator() pour Restriction_Extension

ostream & Restriction_Extension::Aff (ostream & os) const
{
	os << "{Restriction: extension pas parmi : ";
	for (unsigned int i=0; i<nbRF-1; ++i)
	{
		os << restrictedFormats[i] << ", ";
	}
	os << restrictedFormats[nbRF-1] << '}';
	return os;
} //----- fin de Aff pour ostream et Restriction_Extension

string Restriction_Extension::getExtension (const string & nomFichier) const
{
  size_t found = nomFichier.find_last_of(".");
  return nomFichier.substr(found+1);
} //----- fin de getExtension

string Restriction_Extension::ClassToString () const
{
	return "Restriction_Extension";
} //----- fin de ClassToString
