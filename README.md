# PageRank
## Execution de l'algorithme
Pour executer l'algorithme, utiliser la commande "make" pour créer l'executable.
Puis utiliser l'executable comme suit : ./executable data/nom_du_fichier_txt damping_factor epsilon itérations
En cas d'erreur, une aide vous est proposé et explique la bonne utilisation de l'executable.
**Si vous voulez utiliser les jeux de données de test, il faut redéfinir MIN_NUMBER_NODE=1 dans fonction.h**

## Fichiers du code
Vous avez la boucle main dans le fichier pageRank.c, les fonctions utilisées dans fonctions.c, et leurs références, ainsi que les structures utilisées dans fonctions.h

## Explication du code
Pour générer le graphe, j'ai créé une structure Node, qui stocke les liens sortants :
- outputs : tableau qui stocke les numéros des noeuds avec des liens sortants du noeud étudié.
- maxOutputs : Le tableau est initialisé avec une taille de 25, qui est agrandie si nécessaire.
- outputsNumber : Nombre de noeuds stockés actuellement

Dans le cas ou le jeu de données n'utilisent pas chaque numéro de noeuds, je formate les données pour que chaque noeuds correspondent à un site

Pour gérer la matrice creuse avec un tableau 1D, j'ai utilisé une structure permettant de spécifier les propriétés d'un lien:
- value : valeur dans la matrice creuse
- line : position dans la matrice creuse (ligne)
- column : position dans la matrice creuse (colonne)

Dans l'execution du programme, on récupère le nombre de noeuds, le damping factor, ainsi que le nombre d'itérations.
Voici les grandes étapes du programme :
1) Récupération des arguments
2) Lecture du fichier et formatage de celui ci si nécessaire
3) Lecture du fichier txt et création du graphe (tableau de Node)
4) Création de la matrice M et du vecteur propre R
5) Calcul du vecteur propre R selon le nombre d'itérations
6) Sauvegarde des résultats dans le fichier txt de sortie