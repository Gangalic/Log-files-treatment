/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : 26/01/2018
    copyright            : (C) 2018 par B3332 (Duraffourg & Gangalic)
    e-mail               : b3332@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Requete> (fichier Requete.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <sstream>
#include <string>

//------------------------------------------------------ Include personnel
#include "Requete.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string Requete::ObtenirURLdepart()
{
	return URLdepart;
} //----- Fin de Méthode ObtenirURLdepart

string Requete::ObtenirURLarrivee()
{
	return URLarrivee;
} //----- Fin de Méthode ObtenirURLarrivee

int Requete::ObtenirHeure()
{
	return heure;
} //----- Fin de Méthode ObtenirHeure

int Requete::ObtenirStatut()
{
	return statut;
} //----- Fin de Méthode ObtenirHeure

string Requete::ObtenirExtension()
{
	return extension;
} //----- Fin de Méthode ObtenirExtension


//-------------------------------------------- Constructeurs - destructeur
Requete::Requete ( const string line )
// Algorithme :
// Lit tous la ligne et stocker les informations utiles
// Simple pour modifications, car on doit seulement ajouter des parametres
{
	string tmp;
	stringstream ss;
	ss.str(line);
	// trouve IP
	string IP;
	getline(ss, IP,' ');
	// trouve nom utilisateur
	string nom;
	getline(ss, nom,' ');
	// trouve surnom utilisateur
	string surnom;
	getline(ss, surnom,' ');
	// trouve le temps de requete
	string temps;
	getline(ss, temps,']');
	temps+="]";
	getline(ss, tmp,'"');
	// trouve la requete HTTP
	string requeteHTTP;
	getline(ss, requeteHTTP,'"');
	getline(ss, tmp,' ');
	// trouve le code envoye apres l'execution de requete
	string codeError;
	getline(ss, codeError,' ');
	// trouve le numero de bytes utilises par l'operation
	string bytes;
	getline(ss, bytes,' ');
	getline(ss, tmp,'"');
	// trouve l'URL de depart complet
	string URLDepartFull;
	getline(ss, URLDepartFull,'"');
	getline(ss, tmp,'"');
	// trouve le navigateur utilise
	string browser;
	getline(ss, browser,'"');
	
	//initialisation des attributs
	trouverURLdepart(URLDepartFull);
	trouverURLarrivee(requeteHTTP);
	trouverHeure(temps);
	statut=atoi(codeError.c_str());
	trouverExtension(requeteHTTP);
#ifdef MAP
    cout << "Appel au constructeur de <Requete>" << endl;
#endif
} //----- Fin de Requete (constructeur)

Requete::Requete ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <Requete>" << endl;
#endif
} //----- Fin de Requete


Requete::~Requete ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Requete>" << endl;
#endif
} //----- Fin de ~Requete


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Requete::trouverURLarrivee( string requete )
//Algorithme : extraire URL d'arrivee sans requete php
{
	stringstream ssR;
	string temp;
	ssR.str(requete);
	getline(ssR,temp,' ');
	getline(ssR,URLarrivee,' ');
	ssR.str(URLarrivee);
	getline(ssR,URLarrivee,'?');
	URLarrivee="http://intranet-if.insa-lyon.fr"+URLarrivee;
} //----- Fin de Méthode

void Requete::trouverHeure( string temps )
//Algorithme : extraire heure de log
{
	stringstream ssT;
	string temp;
	ssT.str(temps);
	getline(ssT,temp,':');
	getline(ssT,temp,':');
	heure=atoi(temp.c_str());
} //----- Fin de Méthode

void Requete::trouverURLdepart( string URL )
//Algorithme : extraire URL de depart sans requete php
{
	stringstream ssU;
	ssU.str(URL);
	getline(ssU,URLdepart,'?');
} //----- Fin de Méthode

void Requete::trouverExtension( string requete )
//Algorithme : extraire extension
{
	stringstream ssR;
	string temp;
	ssR.str(requete);
	getline(ssR,temp,'.');
	getline(ssR,extension,' ');
	ssR.str(extension);
	getline(ssR,extension,'?');
} //----- Fin de Méthode
