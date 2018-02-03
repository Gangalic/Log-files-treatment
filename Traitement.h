/*************************************************************************
                           Traitement  -  description
                             -------------------
    début                : 26/01/2018
    copyright            : (C) 2018 par B3332 (Duraffourg & Gangalic)
    e-mail               : b3332@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Traitement> (fichier Traitement.h) ----------------
#if ! defined ( Traitement_H )
#define Traitement_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <vector>

//------------------------------------------------------------------ Types
struct Option {
    bool typeOption [3] ={0,0,0};      //1ère case: -g, 2ème: -e, 3ème: -t
    int heure;
    string nomFichierDot;
};

//------------------------------------------------------------------------
// Rôle de la classe <Traitement>
// Utilisee pour effectuer la verification et traitement des valeurs et
// instructions inserees par l'utilisateur
// Interprete aussi les options et manipule les valeurs necessaires pour
// trouver le top des pages accedees et creation du fichier .dot (si indique)
//------------------------------------------------------------------------

class Traitement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    
    bool Traiter(int argc, char* argv[]);
    // Mode d'emploi :
    // argc et argv sont les valeurs parvenues de main

//-------------------------------------------- Constructeurs - destructeur

    Traitement ( );

    ~Traitement ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void TraitementGeneral(string f);
    // Mode d'emploi :
    // f est le nom de fichier outilise pour la lecture des donnees
    
    void CreerFichierDot();

//----------------------------------------------------- Attributs protégés
	map <pair<string,string>,int> trajets;
    map <string,int> hits;
    vector <pair<string, int>> top;
    Option option;
    bool erreur =false;
};
#endif // Traitement_H
