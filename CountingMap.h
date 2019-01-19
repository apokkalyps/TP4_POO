/*************************************************************************
                           CountingMap  -  conteneur de requetes
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <CountingMap> (fichier CountingMap.h) ----------------
#if ! defined ( COUNTING_MAP_H )
#define COUNTING_MAP_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
template <typename Donnee>
struct Top10 
{
    vector <Donnee> donnees;
    vector <unsigned int> scores;
};


//------------------------------------------------------------------------
// Rôle de la classe <CountingMap>
//  Classe générique qui compte le nombre d'occurences d'un objet donné.
//  Ses paramètres de template sont :
//      - Donnee : le type de donnée qu'on devra compter
//      - HashF : une functor pour obtenir un size_t à partir d'un objet Donnee
//      - EqualF : une functor pour comparer deux objets Donnee
//------------------------------------------------------------------------

template <typename Donnee, class HashF, class EqualF>
class CountingMap
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    unsigned int Ajouter ( Donnee data );
    // Mode d'emploi :
    //  Ajoute la donnee fournie a la map et retourne le nombre d'occurences
    //  apres ajout.
    // Contrat :
    //  Aucun.

    void Exporter ( ostream & os = cout ) const;
    // Mode d'emploi :
    //  Exporte sous forme texte brut le contenu du CountingMap sur le flux os.
    //  L'opérateur << doit être surchargé pour le type de données.
    //  Bien sûr, on peut lui fournir l'objet cout (par défaut).
    // Contrat :
    //  Le flux est valide.

    Top10 <Donnee> GetTop10 () const;
    // Mode d'emploi :
    //  Renvoie une structure Top10 listant les dix (ou moins) éléments
    //  les plus décomptés.
    // Contrat :
    //  Aucun.


//------------------------------------------------- Surcharge d'opérateurs
    CountingMap & operator = ( const CountingMap & unCountingMap );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    explicit CountingMap ( const CountingMap & unCountingMap );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    explicit CountingMap ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~CountingMap ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
    typedef unordered_map <Donnee, unsigned int, HashF, EqualF > map_type;
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    map_type map;
};

//-------------------------------- Autres définitions dépendantes de <CountingMap>

template <typename Donnee, class HashF, class EqualF>
unsigned int CountingMap <Donnee, HashF, EqualF> :: Ajouter ( Donnee data )
{
    typename map_type::const_iterator iter = find (data); // Recherche de l'element.
    unsigned int quantite = 0; // Valeur associee a la data.

    if (iter != map.end())
    {
        quantite = *iter;
        erase (data);
    }

    insert (data, ++quantite);

    return quantite;
}

template <typename Donnee, class HashF, class EqualF>
void CountingMap <Donnee, HashF, EqualF> :: Exporter (ostream & os) const
{
    os << "CountingMap : " << map.size() << " éléments." << endl;
    typename map_type :: const_iterator debut (map.begin()), fin (map.end());

    while (debut != fin)
    {
        os << *debut << endl;
        ++debut;
    }
}

template <typename Donnee, class HashF, class EqualF>
Top10 <Donnee> CountingMap <Donnee, HashF, EqualF> :: GetTop10 () const
{}


#endif // COUNTING_MAP_H

