/** Tests
 * email-Eu-core 1005 Nodes
 * test 4 nodes
 * test2 3 nodes
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"

int main(int argc, char const *argv[])
{
	//Check Variables
	if(argc < 5){
		printf("%s","You need to specify :\n1)Name of the data file (without .txt)\n2)Number of nodes\n3)Value of the damping factor\n4)Number of iterions for the algorithm\n");
		printf("%s\n","Example : ./executable test 4 0.85 10" );
		return 0;

	}

	printf("%s\n","**** Lancement du programme PageRank ****" );

	int NumberNodes = atoi(argv[2]);
	char* fileName = (char*)argv[1];

	float dampingFactor = atof(argv[3]);
	int count = atoi(argv[4]);

	printf("node:%d, factor:%f, count:%d\n",NumberNodes,dampingFactor,count);

	printf("%s\n","Lecture des données et création du graphe");
	Node* Nodes = NULL;
	Nodes = init_nodes(Nodes,NumberNodes,fileName);

	printf("%s\n","Création de la matrice M");
	float** M = NULL;
	M = init_matrice(M, NumberNodes, Nodes);

	printf("%s\n", "Création du vecteur de probabilité R");
	float* R = NULL;
	R = init_vector(R, NumberNodes);

	//print_Vector(R,NumberNodes);

	printf("%s\n", "Calcul du vecteur de probabilité R");
	
	for (int i = 0; i < count; ++i)
	{
		R = calculate_vector(M,R,NumberNodes,dampingFactor);
	}
	
	//Save the results in file
	FILE* resultFile = NULL;

	//adding results.txt to fileName
	char resultsFileName[strlen(fileName)+11];
	strcpy(resultsFileName,fileName);
	strcat(resultsFileName,"results.txt");
	resultFile = fopen(resultsFileName,"w+");

	//check for any error while opening file
	if(!resultFile){
		printf("%s\n","Impossible d'ouvrir le fichier" );
		return 1;
	}

	char temp[50] = "";
	for (int i = 0; i < NumberNodes; i++)
	{
		sprintf(temp,"%f",R[i]);
		fputs(temp,resultFile);
		fputs("\n",resultFile);

	}

	fclose(resultFile);

	//print_Vector(R,NumberNodes);

	return 0;
}