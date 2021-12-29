#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"

int main(int argc, char const *argv[])
{
	printf("%s\n","**** Lancement du programme PageRank ****" );

	int NumberNodes = 1005;
	char* fileName = "email-Eu-core.txt";

	printf("%s\n","Lecture des données et création du graphe");
	Node* Nodes = NULL;
	Nodes = init_nodes(Nodes,NumberNodes,fileName);

	printf("%s\n","Création de la matrice M");
	float** M = NULL;
	M = init_matrice(M, NumberNodes, Nodes);

	//Free


	return 0;
}