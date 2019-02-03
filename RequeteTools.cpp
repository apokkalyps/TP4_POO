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
#include "RequeteTools.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef forward_list<Restriction*>::const_iterator it;

//------------------------------------------------------ Fonctions privées

//---------------------------------------------------- Variables statiques


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

Restriction::Restriction (bool uniq) :
	unique (uniq)
{
} //----- fin du constructeur de Restriction

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
		if ((*debut)->unique && restr->unique)
		{
			cerr << "Erreur : restriction déjà présente : ";
			(*debut)->Afficher(cerr);
			cerr << endl;
			exit(1);
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
			os << " - ";
			(*debut)->Afficher(os);
			os << (((*debut)->unique) ? " [u]" : "");
			os << endl;
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
	Restriction(true),
	heure (h)
{
} //----- fin du constructeur de Restriction_Heure

bool Restriction_Heure::operator () (const Requete & req) const
{
	return req.heure.compare(to_string(heure)) == 0;
} //----- fin de Operator() pour Restriction_Heure

void Restriction_Heure::Afficher (ostream & os) const
{
	os << "{Restriction: heure dans [" << int(heure) << ", ";
	os << heure+1 << "[}";
} //----- fin de Operator<< pour ostream et Restriction_Heure

Restriction_Extension::Restriction_Extension () :
	Restriction (false)
{
} //----- fin du constructeur de Restriction_Extension

bool Restriction_Extension::operator () (const Requete & req) const
{
	locale loc; // Pour utiliser toupper
	string extFichier (toupper(getExtension(req.URL_cible), loc));
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

void Restriction_Extension::Afficher (ostream & os) const
{
	os << "{Restriction: extension pas parmi : ";
	for (unsigned int i=0; i<nbRF-1; ++i)
	{
		os << restrictedFormats[i] << ", ";
	}
	os << restrictedFormats[nbRF-1] << '}';
} //----- fin de Operator<< pour ostream et Restriction_Extension

string Restriction_Extension::getExtension (const string & nomFichier) const
{
  size_t found = nomFichier.find_last_of(".");
  return nomFichier.substr(found+1);
} //----- fin de getExtension

istream & operator >> (istream & ifs, Requete & req)
{
	return ifs;
} //----- fin de Operator >> pour Requete.
