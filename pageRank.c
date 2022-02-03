/** Tests
 * email-Eu-core 1005 Nodes
 * test 4 nodes
 * test2 3 nodes
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fonctions.h"

int main(int argc, char const *argv[])
{
	//Check Variables
	if(argc < 5){
		printf("%s","You need to specify :\n1)Name of the data file (without .txt)\n2)Value of the damping factor\n3)Value of Epsilon\n4)Number of iterions for the algorithm\n");
		printf("%s\n","Example : ./executable test 0.85 0.0001 10" );
		return 0;
	}

	printf("%s\n","**** Lancement du programme PageRank ****" );

	char* fileName = (char*)argv[1];
	double dampingFactor = atof(argv[2]);
	float epsilon = atof(argv[3]);
	int nbIteration = atoi(argv[4]);

	printf("Damping Factor:%.2f, Epsilon:%.10f, Itérations:%d\n",dampingFactor,epsilon,nbIteration);

	printf("%s\n","Lecture des données et formatage");
	int* notUsedNode = NULL;
	notUsedNode = (int*) malloc(sizeof(int)* ADDITIONAL_NODE);
	int notUsedcount = 0;
	int NumberNodes = 0;

	notUsedcount = format_data_file(fileName,notUsedNode,&NumberNodes);
	printf("%s\n","Lecture des données et création du graphe");
	Node* Nodes = NULL;
	Nodes = init_nodes(Nodes,NumberNodes,fileName,notUsedNode,notUsedcount);

	// printf("%s\n","Création de la matrice M");
	// double** M = NULL;
	// M = init_matrice(M, NumberNodes, Nodes);

	printf("%s\n","Création de la matrice creuse");
	//sparseLink is a Tab with 3 variables
	int nbValue = NumberNodes;

	sparseLink* sparseM = (sparseLink*) malloc(sizeof(sparseLink)*nbValue);
	for (int i = 0; i < nbValue; ++i)
	{
		sparseM[i].value = 0;
		sparseM[i].line = -1;
		sparseM[i].column = -1;
	}

	sparseM = init_sparse_matrix(sparseM, &nbValue, NumberNodes, Nodes);

	printf("%s\n", "Création du vecteur de probabilité R");
	double* R = NULL;
	R = init_vector(R, NumberNodes);

	//print_Vector(R,NumberNodes);

	clock_t  begin;
	clock_t  end;
	double time_spent = 0;
	int i, finished;

	// printf("%s\n", "Calcul du vecteur de probabilité R via matrice M");

	// i = 0, finished=0;

	// begin = clock();

	// while( i< nbIteration && finished == 0){
	// 	finished = calculate_vector(M,R,NumberNodes,dampingFactor, epsilon);
	// 	i+=1;
	// }

	// end = clock();
	// time_spent = 0;
	// time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 	// printf( "matrix :Finished in %.10f sec\n", time_spent );

    printf("%s\n", "Calcul du vecteur de probabilité R via matrice creuse sparseM");

	i = 0, finished=0;

	begin = clock();

	while( i< nbIteration && finished == 0){
		finished = calculate_vector2(sparseM,R,nbValue,NumberNodes,dampingFactor, epsilon);
		i+=1;
	}

	end = clock();
	time_spent = 0;
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf( "sparseMatrix :Finished in %.10f sec\n", time_spent );

	printf("%s\n", "Sauvegarde des résultats dans le fichier de sortie");
	
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
		sprintf(temp,"%.10f",R[i]);
		fputs(temp,resultFile);
		fputs("\n",resultFile);

	}

	fclose(resultFile);

	//print_Vector(R,NumberNodes);

	printf("%s%s\n","Les résultats sont dans le fichier: ",resultsFileName );

	//free
	//nodes
	free_nodes(Nodes,NumberNodes);
	//M
	// free_matrix(M,NumberNodes);
	//R
	free(R);
	//notUsedNode
	free(notUsedNode);
	return 0;
}