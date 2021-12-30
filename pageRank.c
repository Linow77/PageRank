/** Tests
 * email-Eu-core 1005 Nodes
 * test 4 nodes
 * test2 3 nodes
 **/

#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"

int main(int argc, char const *argv[])
{
	/*printf("%d\n",argc );

	for (int i = 0; i < argc; ++i)
	{
		printf("%s\n",argv[i] );
	}*/

	if(argc < 5){
		printf("%s","You need to specify :\n1)Data file name\n2)Number of nodes\n3)Value of the damping factor\n4)Number of iterions for the algorithm\n");
		printf("%s\n","Example : ./executable test.txt 4 0.85 10" );
		return 0;

	}

	printf("%s\n","**** Lancement du programme PageRank ****" );
	/*int NumberNodes = 1005;
	char* fileName = "email-Eu-core.txt";
	*/
	int NumberNodes = atoi(argv[2]);
	char* fileName = (char*)argv[1];

	float dampingFactor = atof(argv[3]);
	int count = atoi(argv[4]);

	printf("node:%d, factor:%f, count:%d",NumberNodes,dampingFactor,count);

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
	
	for (int i = 0; i < count; ++i)
	{
		R = calculate_vector(M,R,NumberNodes,dampingFactor);
	}
	

	printf("R=\n");
	print_R(R,NumberNodes);
	//Free


	return 0;
}