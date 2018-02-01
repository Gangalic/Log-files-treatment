/*************************************************************************
                           Traitement  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Traitement> (fichier Traitement.h) ----------------
#if ! defined ( Traitement_H )
#define Traitement_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <vector>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Option {
    bool typeOption [3] ={0,0,0};      //1ère case: -g, 2ème: -e, 3ème: -t
    int heure;
    string nomFichierDot;
};

//------------------------------------------------------------------------
// Rôle de la classe <Traitement>
//
//
//------------------------------------------------------------------------

class Traitement
{
//----------------------------------------------------------------- PUBLIC

public:

//-------------------------------------------- Constructeurs - destructeur

    Traitement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    ~Traitement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void Traiter(int argc, char* argv[]);

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	
    void TraitementGeneral(string f);
    
    void CreerFichierDot();

//----------------------------------------------------- Attributs protégés
    map <pair<string,string>,int> trajets;
    map <string,int> hits;
    vector <pair<string, int>> top;
    Option option;
    bool erreur =false;
};

//-------------------------------- Autres définitions dépendantes de <Traitement>

#endif // Traitement_H

