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

    unsigned int CombienDe (Donnee data) const;
    // Mode d'emploi :
    //  Renvoie le nombre d'occurences associé à la Donnee data.
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
    // Type du conteneur des données de la CountingMap.
    
    template <typename Donnee_>
    struct Paire
    // Structure utilisée seulement dans la construction d'une struct Top10.
    {
        Donnee_ data;
        unsigned int score;
        Paire (Donnee_ d, unsigned int s) : data(d), score(s) {}
        bool operator < ( const Paire & p ) const
        {
            return score < p.score;
        }
    };
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    map_type map;
};

//-------------------------------- Autres définitions dépendantes de <CountingMap>

template <typename Donnee, class HashF, class EqualF>
unsigned int CountingMap <Donnee, HashF, EqualF> :: Ajouter ( Donnee data )
{
    unsigned int quantite = CombienDe (data); 

    if (data > 0)
    {
        erase (data);
    }

    insert (data, ++quantite);

    return quantite;
} //----- fin de Ajouter

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
} //----- fin de Exporter

template <typename Donnee, class HashF, class EqualF>
unsigned int CountingMap <Donnee, HashF, EqualF> :: CombienDe (Donnee data) const
{
    typename map_type::const_iterator iter = find (data); // Recherche de l'element.
    return (iter == map.end()) ? 0 : *iter;
}

template <typename Donnee, class HashF, class EqualF>
Top10 <Donnee> CountingMap <Donnee, HashF, EqualF> :: GetTop10 () const
// Algorithme :
//  On commence par créer un vector de paires {Donnee, uint}.
//  On remplit ce vector avec tous les éléments de la CountingMap.
//  On le trie dans l'ordre décroissant et on restreint sa taille.
//  Enfin on le renvoie.
{
    typename map_type::iterator debut (map.begin()), fin (map.end());
    vector <Paire <Donnee>> lesTuples;
    while (debut != fin)
    {
        lesTuples.push_back (Paire<Donnee>(debut->first, debut->second));
        debut++;
    }
    sort (lesTuples.begin(), lesTuples.end());
    reverse (lesTuples.begin(), lesTuples.end());

    if (lesTuples.size() > 10)
    {
        lesTuples.resize(10);
    }
    return lesTuples;
} //----- fin de GetTop10


#endif // COUNTING_MAP_H

