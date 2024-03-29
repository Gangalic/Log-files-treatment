/*************************************************************************
                           Traitement  -  description
                             -------------------
    début                : 26/01/2018
    copyright            : (C) 2018 par B3332 (Duraffourg & Gangalic)
    e-mail               : b3332@insa-lyon.fr
*************************************************************************/

//------ Réalisation de la classe <Traitement> (fichier Traitement.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

//------------------------------------------------------ Include personnel
#include "Requete.h"
#include "Traitement.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// Algorithme :
// Traite tous les exceptions d'insertion
bool Traitement::Traiter (int argc, char* argv[]){
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
        //avec options
        for(int i=1; i<argc-1;i++)
        {

            string temp = string(argv[i]);
            if(temp=="-g")
            {
                if ((option.typeOption[0]==0) && ((i+1)<argc) ){
                // gere le cas ou on trouve 2 fois -g et le cas
                // ou il n'y a pas de nom de fichier donne
					temp = argv[i+1];

					if ( (temp.length()>4) &&
						(temp.substr(temp.length()-4,temp.length())==".dot") ){
						// gere le cas ou le fichier n est pas .dot

						string charac = "ABCDEFGHIJKLMNOPQRSTUVWXYZ-";
						charac+="abcdefghijklmnopqrstuvwxyz_0123456789";
						temp = temp.substr(0,temp.length()-4);

						if(temp.find_first_not_of(charac)==string::npos)
						// gere le cas ou le nom du fichier est mal specifie
						{
							option.typeOption[0]=1;
							option.nomFichierDot=string(argv[i+1]);
							i=i+1;
						}
						else
						{
							cout<<"Erreur : le nom du fichier .dot est mal"
							    <<" spécifié"<<endl;
							erreur = true;
							break;
						}
					}else
					{
						cout<<"Erreur : le fichier donnée pour l'option -g "
							<<"n'est pas un .dot"<<endl;
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
                if (option.typeOption[1]==0) {
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
                if ((option.typeOption[2]==0) && ((i+1)<argc) ){
                // gere le cas ou on trouve 2 fois -t et le cas
                // ou il n'y a pas de nom de fichier donne
                    option.typeOption[2]=1;
                    temp = string(argv[i+1]);

                    if ( (temp.find_first_not_of("0123456789")==string::npos) &&
                        ( (atoi(temp.c_str())>=0)&&(atoi(temp.c_str())<24) ) ){
                    //check si l arg donne est bien un entier entre 0 et 23
                        option.heure=atoi(temp.c_str());
                        i=i+1;
                    }else
                    {
                        cout<<"Erreur: l'heure doit être un entier entre 0 et 23"
                            <<endl;
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
    
    // verification de bon ecriture du fichier .log
    if ((temp.length()>4) &&
        (temp.substr(temp.length()-4,temp.length())==".log"))
    {
        string charac = "ABCDEFGHIJKLMNOPQRSTUVWXYZ-abcdefghijklmnopqrstuvwxyz";
        charac+="_0123456789";
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
            cout<<"Erreur : le nom du fichier specifie n'est pas valide. "
                <<"Veuillez n'entrez que des nombres, des lettres ou des tirets"
                <<endl;

			erreur = true;
        }
    }
    else
    {
        cout<<"Erreur : le fichier specifie n'est pas un log"<<endl;
        erreur = true;
    }



    if(erreur)
    {
        cout<<"Aucun traitement n'a ete effectue."<<endl;
        return false;
    }else
    {
        cout<<"Traitement en cours"<<endl;
        // traitement des fichiers
        string file=string(argv[argc-1]);
        TraitementGeneral(file);
        if (option.typeOption[0]){
            CreerFichierDot();
        }
        return true;
    }


}



//-------------------------------------------- Constructeurs - destructeur
Traitement::Traitement( ) : top(10)
// Algorithme :
// initilisation des attributs
{
#ifdef MAP
    cout << "Appel au constructeur de <Traitement>" << endl;
#endif
} //----- Fin de Traitement (constructeur de copie)

Traitement::~Traitement()
{
#ifdef MAP
    cout << "Appel au destructeur de <Traitement>" << endl;
#endif
} //----- Fin de ~Traitement

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
// Algorithme :
// Traitement generale en utilisant les options choisis par l'utilisateur
void Traitement::TraitementGeneral(string f){
	string line;
	ifstream fi;
	fi.open(f);
	bool selection;
	while (fi.good()){
		getline(fi, line);
		selection=true;
		Requete lineR = Requete(line);
        
        // verifier si la page a ete bien accedee
		if (lineR.ObtenirStatut()==200){
			// seulement pour les documents
			if (option.typeOption[1]){
				if (lineR.ObtenirExtension()!="html"){
				    selection=false;
				}
			}
			// pour un certain temps
			if (option.typeOption[2] && selection){
				if (lineR.ObtenirHeure()!=option.heure){
				    selection=false;
				}
			}
		}else{
		    selection=false;
		}

		if (selection){
		    string URLd=lineR.ObtenirURLdepart();
		    string URLa=lineR.ObtenirURLarrivee();
		    // ajouter les elements dans map "hits"
		    auto posH = hits.find(URLa);
		    if (posH==hits.end()){
		        hits.insert(make_pair(URLa,1));
		    }else{
		        posH->second++;
		    }
		    // ajouter les elements dans map "trajets" si on a l'option -g
		    if (option.typeOption[0]){
    		    auto posT = trajets.find(make_pair(URLd,URLa));
    		    if (posT==trajets.end()){
    		        trajets.insert(make_pair(make_pair(URLd,URLa),1));
    		    }else{
    		        posT->second++;
    		    }
		    }
		}
	}
	// trier et trouver le top 10 pages visitees
	partial_sort_copy(hits.begin(),hits.end(),top.begin(),top.end(),
	                [](const pair<string, int> &a, const pair<string,int> &b){
	                    return a.second>b.second;
	                });
    
    // afficher le top 10
    if((top.front()).first=="")
    {
        cout<<"Aucun résultat n'a été trouvé"<<endl;
    }
	for (pair<string,int> t : top){
	    if (t.first!=""){
	        cout<<t.first<<" ("<<t.second<<" hit";
	        if (t.second>1){
	            cout<<"s";
	        }
	        cout<<")"<<endl;
	    }
	}

	fi.close();
}

// creation fichier .dot
void Traitement::CreerFichierDot(){
    map <string, string> dictTrajets;
    long i=0;
    string nodes;
    ofstream f(option.nomFichierDot);
    f<<"digraph {\n";

    for (auto elem : trajets){
        nodes="node"+to_string(i);
        dictTrajets.insert(make_pair(elem.first.first,nodes));
        i++;
        nodes="node"+to_string(i);
        dictTrajets.insert(make_pair(elem.first.second,nodes));
        i++;
    }

    for (auto elem : dictTrajets){
        f<<elem.second<<" [label=\""<<elem.first<<"\"];\n";
    }

    for (auto elem : trajets){
        f<<dictTrajets[elem.first.first]<<" -> "<<dictTrajets[elem.first.second]
        <<" [label=\""<<elem.second<<"\"];\n";
    }
    f<<"}";
}
