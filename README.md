## Manuel d utilisation

### Name
./analog nomFichier.log - affiche dans la console les 10 documents les plus consultes, a partir du fichier donne en parametres.

### Synopsis
 ./analog [-egt] nomfichier.log

### Description
Affiche les 10 documents les plus consultes par ordre decroissant de popularite. Le nom du fichier .log specifie est le nom du log apache qui sera utilise pour determiner les 10 documents. Il est admis que ce fichier .log est bien ecrit. 

De plus, ./analog a la possibilite de creer un fichier GraphViz interpretable par la commande dot. Voir -g dans les options pour plus d informations.

### Options
- -e,  permet d exclure les documents qui ont une extension de type image, css ou javascript.
- -g nomFichierGraph.dot, permet de produire un fichier au format GraphViz ou chaque document est un noeud et chaque arc un parcours.
- -t heure, permet de ne prendre en compte que les hits dans le creneau horaire [heure, heure+1[. Heure doit etre un nombre compris entre 0 et 23 compris.

### Environnement
En cas d appel de la commande avec l option -g fichier.dot, le fichier sera cree s il n existe pas deja, et ecrase s il existe deja.

### Auteur
Cette page a ete ecrite par Duraffourg Maud et Gangalic Catalin.

### Voir aussi
[dot][1].

[1]: http://www.linuxcertif.com/man/1/dot/
