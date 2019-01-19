/*************************************************************************
                           CountingMap  -  conteneur de requetes
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//-- Interface de la classe <CountingMap> (fichier CountingMap.h) --------
#if ! defined ( COUNTING_MAP_H )
#define COUNTING_MAP_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef unsigned int nbr_t; // Raccourci car beaucoup utilisé.

template <typename Donnee_>
struct Paire
// Structure stockant un "tuple" de la CountingMap.
// Elle est utilisée pour extraire plusieurs trucs à la fois de la CM.
{
    Donnee_ data; // Donnée stockée
    nbr_t score; // Nombre d'occurences
    Paire (Donnee_ d = Donnee_ (), nbr_t s = 0); 
    // Unique constructeur possible + par défaut.
    bool operator < ( const Paire <Donnee_> & p ) const;
    // Surcharge de l'opérateur de comparaison inférieur.
    friend ostream & operator << ( ostream & os, const Paire<Donnee_> p)
    // Surchage de l'opérateur d'injection dans le flux de sortie.
    {
        return ( os << '{' << p.data << ", " << p.score << '}' );
    }
    Paire <Donnee_> & operator= (const Paire<Donnee_> & src) = default;
};

//------------------------------------------------------------------------
// Rôle de la classe <CountingMap>
//  Classe générique qui compte le nombre d'occurences d'un objet donné.
//  Ses paramètres de template sont :
//      - Donnee : le type de donnée qu'on devra compter
//          Opérateurs à surcharger : == (égalité), << (ostream).
//      - HashF : une functor pour obtenir un size_t à partir d'un objet Donnee
//------------------------------------------------------------------------

template <typename Donnee, class HashF = hash<Donnee>>
class CountingMap
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    nbr_t Ajouter ( Donnee data );
    // Mode d'emploi :
    //  Ajoute la donnee fournie a la CountingMap.
    //  Retourne le nombre d'occurences apres ajout.
    // Contrat :
    //  Aucun.

    nbr_t CombienDe (Donnee data) const;
    // Mode d'emploi :
    //  Renvoie le nombre d'occurences associé à data.
    // Contrat :
    //  Aucun.

    void Exporter ( ostream & os = cout ) const;
    // Mode d'emploi :
    //  Exporte sous forme texte brut le contenu du CountingMap sur le flux os.
    //  L'opérateur << doit être surchargé pour le type de données.
    //  Bien sûr, on peut lui fournir l'objet cout (par défaut).
    // Contrat :
    //  Le flux est valide.

    size_t GetTaille () const;
    // Mode d'emploi :
    //  Renvoie la taille du CountingMap en nombre d'éléments connus.
    // Contrat :
    //  Aucun.

    vector<Paire<Donnee>> GetTop (unsigned int nombre) const;
    // Mode d'emploi :
    //  Renvoie un vecteur des nombre éléments les plus décomptés.
    // Contrat :
    //  Aucun.


//------------------------------------------------- Surcharge d'opérateurs
    CountingMap & operator = ( const CountingMap & unCountingMap ) = delete;
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    explicit CountingMap ( const CountingMap & unCountingMap ) = delete;
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
    typedef unordered_map <Donnee, nbr_t, HashF> map_type;
    // Type du conteneur des données de la CountingMap.
    

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    map_type map;
};

//------------------------------ Autres définitions dépendantes de <CountingMap>

// --- Pour la structure Paire
template <typename Donnee_>
Paire<Donnee_> :: Paire (Donnee_ d, nbr_t s) :
    data (d), score (s)
{
} //----- fin du constructeur de Paire.

template <typename Donnee_>
bool Paire<Donnee_> :: operator < ( const Paire <Donnee_> & p ) const
{
    return score < p.score;
} //----- fin de operator < pour Paire.



// --- Pour la classe CountingMap
template <typename Donnee, class HashF>
CountingMap <Donnee, HashF> :: CountingMap ()
{
    #ifdef MAP
    cout << "Création d'une instance de CountingMap." << endl;
    #endif
} //----- fin du constructeur par défaut

template <typename Donnee, class HashF>
CountingMap <Donnee, HashF> :: ~CountingMap ()
{
    #ifdef MAP
    cout << "Destruction d'une instance de CountingMap." << endl;
    #endif
} //----- fin du destructeur


template <typename Donnee, class HashF>
nbr_t CountingMap <Donnee, HashF> :: Ajouter ( Donnee data )
{
    nbr_t quantite = CombienDe (data); 

    if (quantite > 0)
    {
        map.erase (data);
    }

    //map.insert (data, ++quantite);
    map.insert (pair<Donnee, nbr_t> (data, ++quantite));

    return quantite;
} //----- fin de Ajouter

template <typename Donnee, class HashF>
void CountingMap <Donnee, HashF> :: Exporter (ostream & os) const
{
    size_t taille = GetTaille();
    if (taille == 0)
    {
        os << "CountingMap vide." << endl;
    }
    else
    {
        os << "CountingMap : " << GetTaille() << " éléments." << endl;
        typename map_type::const_iterator debut(map.cbegin()), fin(map.cend());

        while (debut != fin)
        {
            os << "-> " << debut->first << " | " << debut->second << endl;
            ++debut;
        }
    }
} //----- fin de Exporter

template <typename Donnee, class HashF>
nbr_t CountingMap <Donnee, HashF> :: CombienDe (Donnee data) const
{
    typename map_type::const_iterator iter = map.find (data);
    return (iter == map.end()) ? 0 : iter->second;
} //----- fin de CombienDe.

template <typename Donnee, class HashF>
size_t CountingMap <Donnee, HashF> :: GetTaille () const
{
    return map.size();
} //----- fin de GetTaille.

template <typename Donnee, class HashF>
vector<Paire<Donnee>> CountingMap <Donnee, HashF> :: GetTop 
    (unsigned int nombre) const
// Algorithme :
//  On commence par créer un vector de paires {Donnee, nbr_t}.
//  On remplit ce vector avec tous les éléments de la CountingMap.
//  On le trie dans l'ordre décroissant et on restreint sa taille.
//  Enfin on le renvoie.
{
    typename map_type::const_iterator debut (map.cbegin()), fin (map.cend());
    vector <Paire <Donnee>> lesTuples;
    while (debut != fin)
    {
        lesTuples.push_back (Paire<Donnee>(debut->first, debut->second));
        debut++;
    }
    sort (lesTuples.begin(), lesTuples.end());
    reverse (lesTuples.begin(), lesTuples.end());

    if (lesTuples.size() > nombre)
    {
        lesTuples.resize(nombre);
    }
    return lesTuples;
} //----- fin de GetTop


#endif // COUNTING_MAP_H

