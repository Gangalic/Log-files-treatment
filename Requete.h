/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : 26/01/2018
    copyright            : (C) 2018 par B3332 (Duraffourg & Gangalic)
    e-mail               : b3332@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Requete> (fichier Requete.h) ----------------
#if ! defined ( Requete_H )
#define Requete_H

//------------------------------------------------------------------------
// Rôle de la classe <Requete>
// Utilisee pour traiter la ligne de chaque requete et retrouver le parametres
// necessaires pour le traitement d'apres
// Peut etre extensible en ajoutant des autres attributs pour des autres
// traitements plus specifiques
//------------------------------------------------------------------------

class Requete
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    
    string ObtenirURLdepart();
    // Mode d'emploi :
    // Donne l'URL de depart en extern
    
    string ObtenirURLarrivee();
    // Mode d'emploi :
    // Donne l'URL d'arrivee en extern
    
    int ObtenirHeure();
    // Mode d'emploi :
    // Donne l'heure en extern
    
    int ObtenirStatut();
    // Mode d'emploi :
    // Donne le statut de la requete en extern
    
    string ObtenirExtension();
    // Mode d'emploi :
    // Donne l'extension du fichier d'arrivee en extern

//-------------------------------------------- Constructeurs - destructeur
    Requete ( const string line );
    // Mode d'emploi:
    // Copie une ligne pour le traiter dedans

    Requete ( );

    ~Requete ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void trouverURLarrivee( string requete );
    // Mode d'emploi :
    // Retrouve l'URL d'arrivee depuis la line envoyee du constructeur 
    
    void trouverHeure( string temps );
    // Mode d'emploi :
    // Retrouve l'heure de requete depuis la line du constructeur 
    
    void trouverURLdepart( string URL );
    // Mode d'emploi :
    // Retrouve l'URL de depart depuis la line du constructeur 
    
    void trouverExtension( string requete );
    // Mode d'emploi :
    // Retrouve l'extension du fichier d'arrivee depuis la line du constructeur 

//----------------------------------------------------- Attributs protégés
	string URLdepart;
	string URLarrivee;
	int heure;
	int statut;
	string extension;
};

#endif // Requete_H

