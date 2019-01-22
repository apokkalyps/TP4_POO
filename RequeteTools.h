/*************************************************************************
                   RequeteTools  -  outils pour manipuler des requetes
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <RequeteTools> (fichier RequeteTools.h) ---------------
#ifndef REQUETE_TOOLS_H
#define REQUETE_TOOLS_H

//------------------------------------------------------------------------
// Rôle du module <RequeteTools>
//	Contient les structures et outils éventuels pour manipuler des requêtes.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <iostream>
#include <forward_list>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Requete
// Structure contenant toutes les informations sur une requête.
{
	string IP                    ;
	string userName              ;
	string authenticatedUserName ;
	string jour                  ;
	string mois                  ;
	string annee                 ;
	string heure                 ;
	string minute                ;
	string seconde               ;
	string fuseau                ;
	string type                  ;
	string URL_cible             ;
	string protocole             ;
	string status                ;
	string data                  ;
	string URL_source            ;
	string navigateur            ;
};

struct Restriction
// Structure contenant une simple fonction booléenne qui teste une Requete.
{
	virtual bool operator () (const Requete & req) const = 0;
	// Mode d'emploi :
	//	Teste si la requête satisfait la restriction saisie.
	// Contrat :
	//	Aucun.
	virtual void Afficher (ostream & os) const = 0;
	// Mode d'emploi :
	//	Affiche sur le flux fourni la restriction courante.
	// Contrat :
	//	Aucun.
	virtual ~Restriction() = default;
	// Détruit l'objet courant.
};

struct RestrictionList
// Structure contenant une liste des restrictions de lecture.
// Contrat d'utilisation : pas de copie.
{
	forward_list<Restriction*> liste; 
	// Liste simplement chaînée de restrictions en accès libre.
	bool TesterTout (const Requete & req);
	// Mode d'emploi :
	//	Teste toutes les restrictions sur la requête fournie et renvoie 
	//	true si et seulement si toutes les restrictions sont validées.
	// Contrat :
	//	Aucun.
	friend ostream & operator << (ostream & os, 
		const RestrictionList & rl);
	// Mode d'emploi :
	//	Affiche toutes les restrictions, une par ligne + un entête.
	// Contrat :
	//	Aucun.
	~RestrictionList ();
	// Mode d'emploi :
	//	Destructeur car allocation dynamique.
	// Contrat :
	//	Aucun.
};

struct Restriction_Heure : public Restriction
// Restriction sur l'heure.
{
public:
	Restriction_Heure (unsigned char h);
	bool operator () (const Requete & req) const;
	virtual void Afficher (ostream & os) const;
private:
	unsigned char heure = 0;
};

struct Restriction_Extension : public Restriction
// Restriction sur l'extension du fichier de l'URL cible.
{
public:

	bool operator () (const Requete & req) const;
	virtual void Afficher (ostream & os) const;
private:
	string getExtension (const string & nomFichier) const;
	// Renvoie l'extension du fichier.
	// Contrat : le fichier a bien une extension.
	const static unsigned int nbRF = 7; // Nombre de restrictedFormats
	const string restrictedFormats[nbRF] =
  {"TIFF", "JPEG", "GIF", "PNG", "RAW", "CSS", "JS"}; // Formats interdits.
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


#endif // REQUETE_TOOLS_H
