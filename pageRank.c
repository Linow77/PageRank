#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"

int main(int argc, char const *argv[])
{
	printf("%s\n","**** Lancement du programme PageRank ****" );

	int NumberNodes = 1005;
	char* fileName = "email-Eu-core.txt";
	/*int NumberNodes = 4;
	char* fileName = "test.txt";*/

	float dampingFactor = 0.85;

	printf("%s\n","Lecture des données et création du graphe");
	Node* Nodes = NULL;
	Nodes = init_nodes(Nodes,NumberNodes,fileName);

	printf("%s\n","Création de la matrice M");
	float** M = NULL;
	M = init_matrice(M, NumberNodes, Nodes);

	printf("%s\n", "Création du vecteur de probabilité R");
	float* R = NULL;
	R = init_vector(R, NumberNodes);

	print_R(R,NumberNodes);

	printf("%s\n", "Calcul du vecteur de probabilité R");
	int count = 10;
	for (int i = 0; i < count; ++i)
	{
		R = calculate_vector(M,R,NumberNodes,dampingFactor);
	}
	

	printf("R=\n");
	print_R(R,NumberNodes);
	//Free


	return 0;
}