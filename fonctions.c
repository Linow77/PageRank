#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"

#define MAX_LENGTH 100

Node* init_nodes(Node* Nodes, int NumberNodes, char* fileName){
	int i;

	//Allocation of Nodes
	Nodes = (Node*) malloc(sizeof(Node)*NumberNodes);
	
	for(i=0;i<NumberNodes;i++){
		Nodes[i].outputsNumber = 0;
		Nodes[i].maxOutputs = 25;
		Nodes[i].outputs = (int*) malloc(sizeof(int)*Nodes[i].maxOutputs);	
	}


	//Get data from file and transfer them to Nodes
	FILE* file = NULL;
	char string[MAX_LENGTH] = "";
	char delimiter[] = " \t";
	char* part1 = "";
	char* part2 = "";
	int node1;
	int node2;

	//adding .txt to fileName
	char data[strlen(fileName)+4];
	strcpy(data,fileName);
	strcat(data,".txt");

	//open file in reading mode
	file = fopen(data, "r");

	//check for any error while opening file
	if(!file){
		printf("%s\n","Impossible d'ouvrir le fichier" );
		return Nodes;
	}

	//get the first line of the file
	while (fgets(string,MAX_LENGTH,file) != NULL){
		//get the two nodes of the lines
		part1 = strtok(string,delimiter);
		part2 = strtok(NULL,delimiter);

		//convert string into int
		node1 = atoi(part1);
		node2 = atoi(part2);

		//add outputs in node1
		//check if outputs is full
		if(Nodes[node1].outputsNumber == Nodes[node1].maxOutputs ) {
			//realloc outputs
			Nodes[node1].maxOutputs += 25;
			Nodes[node1].outputs = (int*) realloc(Nodes[node1].outputs, sizeof(int)*Nodes[node1].maxOutputs);
		}

		Nodes[node1].outputs[Nodes[node1].outputsNumber] = node2;
		//increment number of output from node1
		Nodes[node1].outputsNumber = Nodes[node1].outputsNumber + 1;
	}

	fclose(file);

	return Nodes;
}

double** init_matrice(double** M, int NumberNodes, Node* Nodes){

	//Allocation
	M = (double**) malloc(sizeof(double*)*NumberNodes);

	for (int i = 0; i < NumberNodes; i++)
	{
		M[i]= (double*) malloc(sizeof(double)*NumberNodes);
	}

	//Init M at 0
	for (int i = 0; i < NumberNodes; i++)
	{
		for (int j = 0; j < NumberNodes; j++)
		{
			M[i][j]=0;
		}
	}

	//For each Nodes
	for (int i = 0; i < NumberNodes; i++)
	{
		//Examine each outputs
		for (int j = 0; j < Nodes[i].outputsNumber; j++)
		{
			M[Nodes[i].outputs[j]][i]=1.0/(Nodes[i].outputsNumber);
		}
	}
	
	return M;
}

double* init_vector(double* R, int NumberNodes){
	R = (double*) malloc(sizeof(double)* NumberNodes);

	//At the beginning, each node has probability 1/N to be chosen
	for (int i = 0; i < NumberNodes; i++)
	{
		R[i] = 1.0/NumberNodes;
	}

	return R;
}

void calculate_vector(double** M,double* R,int NumberNodes,double dampingFactor){

	/** Power method **/
	//R = P1 + P2
	//R = dMR + ((1-d)/N)V1 	where d is the damping factor

	//Calculate P1 = dMR
	double* P1 = NULL;
	//P1=MR
	P1 = calculate_matrix_vector(M,R, NumberNodes);
	//P1=dMR
	calculate_vector_number(P1,dampingFactor,NumberNodes);

	//Calculate P2 = ((1-d)/N)V1 = p3V1
	//V1 is the vector with only ones so P2 is the vector with only p3

	double p3= (double)(1.0-dampingFactor)/(double)NumberNodes;

	double* P2 = NULL;
	P2 = (double*) malloc(sizeof(double)*NumberNodes);

	for (int i = 0; i < NumberNodes; i++)
	{
		P2[i] = p3;
	}	

	//Calculate Result
	addition_vector(P1,P2,NumberNodes);

	//Store result in R
	for (int i = 0; i < NumberNodes; i++)
	{
		R[i]= P1[i];
	}

	//free temp
	free(P1);
	free(P2);
}


//Utils
void print_outputs(Node* Nodes, int NumberNodes){

	for (int i = 0; i < NumberNodes; i++)
	{
		printf("Node %d: ",i);
		//Examine each outputs
		for (int j = 0; j < Nodes[i].outputsNumber; j++)
		{
			printf("%d | ",Nodes[i].outputs[j] );
		}
		printf("\n");
	}
}

void print_matrice(double** M, int NumberNodes){
	for (int i = 0; i < NumberNodes; i++)
	{
		for (int j = 0; j < NumberNodes; j++)
		{
			printf("%.3f | ",M[i][j] );
		}
		printf("\n");
	}
}

void print_Vector(double* R, int NumberOfLine){

	for (int i = 0; i < NumberOfLine; i++)
	{
		printf("%.3f\n", R[i]);
	}
}

double* calculate_matrix_vector(double** Matrix, double* Vector, int NumberNodes){

	double* Result= NULL;
	Result = (double*) malloc(sizeof(double)*NumberNodes);

	for (int i = 0; i < NumberNodes; i++)
	{
		Result[i]=0;

		for (int j = 0; j < NumberNodes; j++)
		{
			Result[i]+= Matrix[i][j]*Vector[j];			
		}
	}

	return Result;
}

void addition_vector(double* Vector1, double* Vector2, int NumberNodes){

	for (int i = 0; i < NumberNodes; i++)
	{
		Vector1[i] = Vector1[i] + Vector2[i];
	}
}

void calculate_vector_number(double* Vector, double Number, int NumberNodes){
	
	for (int i = 0; i < NumberNodes; i++)
	{
		Vector[i] = Vector[i]*Number;
	}

}

//free functions
void free_nodes(Node* Nodes, int NumberNodes){
	for (int i = 0; i < NumberNodes; i++)
	{
		//free int tab
		free(Nodes[i].outputs);
	}
	free(Nodes);

}

void free_matrix(double** M, int NumberNodes){

	for (int i = 0; i < NumberNodes; i++)
	{
		free(M[i]);
	}
	free(M);
}