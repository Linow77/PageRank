# PageRank
## Execution de l'algorithme
Pour executer l'algorithme, utiliser la commande "make" pour créer l'executable.
Puis utiliser l'executable comme suit : ./executable nom_du_fichier_txt nombre_de_noeuds damping_factor itérations
En cas d'erreur, une aide vous est proposé et explique la bonne utilisation de l'executable.

## Fichiers du code
Vous avez la boucle main dans le fichier pageRank.c, les fonctions utilisées dans fonctions.c, et leurs références, ainsi que la structure utilisée dans fonctions.h

## Explication du code
Pour générer le graphe, j'ai créé une structure Node, qui stocke les liens sortants :
- outputs : tableau qui stocke les numéros des noeuds avec des liens sortants du noeud étudié.
- maxOutputs : Le tableau est initialisé avec une taille de 25, qui est agrandie si nécessaire.
- outputsNumber : Nombre de noeuds stockés actuellement

Dans l'execution du programme, on récupère le nombre de noeuds, le damping factor, ainsi que le nombre d'itérations.
Voici les grandes étapes du programme :
1) Récupération des arguments
2) Lecture du fichier txt et création du graphe (tableau de Node)
3) Création de la matrice M et du vecteur propre R
4) Calcul du vecteur propre R selon le nombre d'itérations
5) Sauvegarde du résultats dans le fichier txt de sortie