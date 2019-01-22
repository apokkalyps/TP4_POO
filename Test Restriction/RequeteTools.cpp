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
#include "RequeteTools.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef forward_list<Restriction*>::const_iterator it;

//------------------------------------------------------ Fonctions privées

//---------------------------------------------------- Variables statiques


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

bool RestrictionList::TesterTout (const Restriction & restr)
{
	for (it debut (liste.cbegin()); debut<liste.cend(); ++debut)
	{
		if (*debut(restr) == false)
		{
			return false;
		}
	}
	return true;
} //----- fin de TesterTout


bool Restriction_Heure::operator () (const Requete & req) const
{
	return req.heure.compare(heure) == 0;
} //----- fin de Operator() pour Restriction_Heure


ostream & operator << (ostream & os, const Restriction_Heure & restr)
{
	os << "{Restriction: heure dans [" << heure << ", ";
	os << heure+1 << "[}";
	return os;
} //----- fin de Operator<< pour ostream et Restriction_Heure

bool Restriction_Extension::operator () (const Requete & req) const
{
	string extFichier (getExtension(req.URL_cible));
	for (unsigned int i=0; i<nbRF; ++i)
	{
		if (extFichier.compare(restrictedFormats[i]) == 0)
		{
			return false;
		}
	}
	return true;
} //----- fin de Operator() pour Restriction_Extension

ostream & operator << (ostream & os, const Restriction_Extension & restr)
{
	os << "{Restriction: extension pas parmi : ";
	for (unsigned int i=0; i<nbRF-1; ++i)
	{
		os << restrictedFormats[i] << ", ";
	}
	os << restrictedFormats[nbRF-1];
	return os;
} //----- fin de Operator<< pour ostream et Restriction_Extension

string Restriction_Extension::getExtension (const string & nomFichier) const
{
  size_t found = nomFichier.find_last_of(".");
  return nomFichier.substr(found+1);
} //----- fin de getExtension