#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"

int main(int argc, char const *argv[])
{
	printf("%s\n","Lancement du programme PageRank" );
	int NumberNodes = 1005;
	int end = 5;
	printf("%s\n","Lecture des données et création du graphe");
	Node* Nodes = NULL;
	Nodes = init_nodes(Nodes,NumberNodes);

	printf("Number of outputs of node 4 : %d\n",Nodes[4].outputsNumber);

	printf("%s\n","Création de la matrice M");
	
	//int** M = init_matrice();


	//Free 
	return 0;
}