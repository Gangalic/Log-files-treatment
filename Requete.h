/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Requete> (fichier Requete.h) ----------------
#if ! defined ( Requete_H )
#define Requete_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Requete>
//
//
//------------------------------------------------------------------------

class Requete
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    string ObtenirURLdepart();
    
    string ObtenirURLarrivee();
    
    int ObtenirHeure();
    
    int ObtenirStatut();
    
    string ObtenirExtension();


//-------------------------------------------- Constructeurs - destructeur
    Requete ( const string line);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Requete ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Requete ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
void trouverURLarivee( string requette );

void trouverHeure( string temps );

void trouverURLdepart( string URL );

void trouverExtension( string requete );

//----------------------------------------------------- Attributs protégés
	string URLdepart;
	string URLarrivee;
	int heure;
	int statut;
	string extension;
};

//-------------------------------- Autres définitions dépendantes de <Requete>

#endif // Requete_H

