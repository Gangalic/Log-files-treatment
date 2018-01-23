/*************************************************************************
                           main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <main> (fichier main.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

//------------------------------------------------------ Include personnel
#include "Requete.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Option {
    bool typeOption [3] ={0,0,0};      //1ère case : -g, 2ème case : -e, 3ème case : -t
    int heure;
    string nomFichierDot;
};

//---------------------------------------------------- Variables statiques
map <pair<string,string>,int> trajets;
map <string,int> hits;
bool erreur =false;

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom


//class declaration
void Read (int argc, char* argv[]);

void traitementGeneral(string f, Option option);

//main
int main(int argc, char* argv[])
{
    Read(argc, argv);
	//for testing
	for (auto elem : trajets){
	    cout<<elem.first.first<<" "<<elem.first.second<<" "<<elem.second<<endl;
	}
	cout<<endl;
	for (auto elem : hits){
	    cout<<elem.first<<" "<<elem.second<<endl;
	}

}

//class definition
void Read (int argc, char* argv[]){
    Option option;
    string nomFichierLog;

    if(argc == 1)
    {
      //erreur
        cout<<"Erreur : veuillez entrer un nom de fichier."<<endl;
        erreur=true;
    }else if (argc == 2)
    {
        //sans option
    }else
    {
        //avec option
        for(int i=1; i<argc-1;i++)
        {
    
            string temp = string(argv[i]);
            if(temp=="-g")
            {
                if ((option.typeOption[0]==0) && ((i+1)<argc) ){
                //gere le cas ou on trouve 2 fois -g et le cas òu il n'y a pas de nom de fichier donne
                   option.typeOption[0]=1;
                    temp = string(argv[i+1]);
                    if (temp.substr(temp.length()-4,temp.length())==".dot"){
                    //gere le cas ou le fichier n est pas .dot
                        option.nomFichierDot=string(argv[i+1]);
                        i=i+1;
                    }else
                    {
                        cout<< "Erreur : le fichier donnée pour l'option -g n'est pas un .dot"<<endl;
                        erreur = true;
                        break;
                    }
                }else
                {
                    cout << "Erreur : -g n'a pas été correctement entrée"<<endl;
                    erreur = true;
                    break;
                }
            }
            else if(temp=="-e")
            {
                if (option.typeOption[0]==0) {
                    option.typeOption[1]=1;
                }else
                {
                    cout << "Erreur : -e est present deux fois"<<endl;
                    erreur = true;
                    break;
                }
            }
            else if(temp=="-t")
            {
                if ((option.typeOption[0]==0) && ((i+1)<argc) ){
                //gere le cas ou on trouve 2 fois -t et le cas òu il n'y a pas de nom de fichier donne
                    option.typeOption[2]=1;
                    temp = string(argv[i+1]);
    
                    if ( (temp.find_first_not_of("0123456789")==string::npos)&&( (atoi(temp.c_str())>=0)&&(atoi(temp.c_str())<24) ) ){
                    //check si l arg donne est bien un entier entre 0 et 23
                        option.heure=atoi(temp.c_str());
                        i=i+1;
                    }else
                    {
                        cout<< "Erreur : l'heure doit être un entier entre 0 et 23"<<endl;
                        erreur = true;
                        break;
                    }
                }else
                {
                    cout << "Erreur : -t n'a pas été correctement entrée"<<endl;
                    erreur = true;
                    break;
                }
    
            }
    
        }

    }

    string temp = string(argv[argc-1]);

    if (temp.substr(temp.length()-4,temp.length())==".log")
    {
        string charac = "ABCDEFGHIJKLMNOPQRSTUVWXYZ-abcdefghijklmnopqrstuvwxyz_0123456789";
        temp=temp.substr(0,temp.length()-5);
        if(temp.find_first_not_of(charac)==string::npos)
        {
            nomFichierLog = string(argv[argc-1]);
            ifstream entreeFic;
            entreeFic.open(nomFichierLog);
            if(!entreeFic)
            {
                cout<<"Erreur : le fichier specifie n'existe pas"<<endl;
                erreur = true;
            }
            entreeFic.close();
        }
        else
        {
            cout<<"Erreur : le nom du fichier specifie n'est pas valide. Veuillez n'entrez que des nombres, des lettres ou des tirets."<<endl;
        }
    }
    else
    {
        cout<<"Erreur : le fichier specifie n'est pas un log"<<endl;
        erreur = true;
    }



    if(erreur)
    {
        cout<<"Aucun traitement n'a pas ete effectue."<<endl;
    }else
    {
        //traitement des fichiers
        string file=string(argv[argc-1]);
        traitementGeneral(file,option);
    }
}

//traitement
void traitementGeneral(string f, Option option){
	string line;
	ifstream fi;
	fi.open(f);
	while (fi.good()){
		getline(fi, line);
		Requete lineR = Requete(line);
		if (lineR.ObtenirStatut()==200){
			if (option.typeOption[1]){
				//only text pages
				if (lineR.ObtenirExtension()=="html"){
				    string URLd=lineR.ObtenirURLdepart();
				    string URLa=lineR.ObtenirURLarrivee();
				    /*cout<<"URL depart: "<<URLd<<endl;
				    cout<<"URL arrivee: "<<URLa<<endl;
				    cout<<endl;*/
				    //adding to 2 keys matrix
				    auto posT = trajets.find(make_pair(URLd,URLa));
				    if (posT==trajets.end()){
				        trajets.insert(make_pair(make_pair(URLd,URLa),1));
				    }else{
				        posT->second++;
				    }
				    auto posH = hits.find(URLa);
				    if (posH==hits.end()){
				        hits.insert(make_pair(URLa,1));
				    }else{
				        posH->second++;
				    }
				}
			}
			if (option.typeOption[2]){
				// for certain time
			}
			if (option.typeOption[0]){
				// decide where to put the 2 keys matrix such that it takes less of memory
			}
		}
	}
	fi.close();
}




//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

