/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Requete> (fichier Requete.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <sstream>
#include <string>

//------------------------------------------------------ Include personnel
#include "Requete.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Requete::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

string Requete::ObtenirURLdepart()
// Algorithme :
{
	return URLdepart;
} //----- Fin de Méthode

string Requete::ObtenirURLarrivee()
// Algorithme :
{
	return URLarrivee;
} //----- Fin de Méthode

int Requete::ObtenirHeure()
// Algorithme :
{
	return heure;
} //----- Fin de Méthode

int Requete::ObtenirStatut()
// Algorithme :
{
	return statut;
} //----- Fin de Méthode

string Requete::ObtenirExtension()
// Algorithme :
{
	return extension;
} //----- Fin de Méthode


//-------------------------------------------- Constructeurs - destructeur
Requete::Requete ( const string line )
// Algorithme :
// lire tous la ligne et stoquer les infos
{
	string tmp;
	stringstream ss;
	ss.str(line);
	string IP;
	getline(ss, IP,' ');
	string nom;
	getline(ss, nom,' ');
	string surnom;
	getline(ss, surnom,' ');
	string temps;
	getline(ss, temps,']');
	temps+="]";
	getline(ss, tmp,'"');
	string requeteHTTP;
	getline(ss, requeteHTTP,'"');  //writes over (for last change to tmp and add to rHTTP)
	getline(ss, tmp,' ');
	string codeError;
	getline(ss, codeError,' ');
	string bytes;
	getline(ss, bytes,' ');
	getline(ss, tmp,'"');
	string URLDepartFull;
	getline(ss, URLDepartFull,'"');
	getline(ss, tmp,'"');
	string browser;
	getline(ss, browser,'"');
	
	//initialisation des attributs
	trouverURLdepart(URLDepartFull);
	trouverURLarivee(requeteHTTP);
	trouverHeure(temps);
	statut=atoi(codeError.c_str());
	trouverExtension(requeteHTTP);
#ifdef MAP
    cout << "Appel au constructeur de <Requete>" << endl;
#endif
} //----- Fin de Requete (constructeur de copie)

Requete::Requete ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Requete>" << endl;
#endif
} //----- Fin de Requete


Requete::~Requete ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Requete>" << endl;
#endif
} //----- Fin de ~Requete


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

    void Requete::trouverURLarivee( string requette )
    //Algorithme : extraire URL d'arrivee sans requete php
    {
    	stringstream ssR;
    	string temp;
    	ssR.str(requette);
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
