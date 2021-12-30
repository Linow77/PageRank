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
		Nodes[i].inputsNumber = 0;
		Nodes[i].outputsNumber = 0;
		Nodes[i].maxOutputs = 25;
		Nodes[i].outputs = (int*) malloc(sizeof(int)*Nodes[i].maxOutputs);	
	}


	//Get data from file and transfer them to Nodes
	FILE* file = NULL;
	char string[MAX_LENGTH] = "";
	char delimiter[] = " ";
	char* part1 = "";
	char* part2 = "";
	int node1;
	int node2;

	//open file in reading mode
	file = fopen(fileName, "r");

	//check for any error while opening file
	if(!file){
		printf("%s\n","Impossible d'ouvrir le fichier" );
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
		if(Nodes[node1].inputsNumber == Nodes[node1].maxOutputs ) {
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

float** init_matrice(float** M, int NumberNodes, Node* Nodes){

	//Allocation
	M = (float**) malloc(sizeof(float*)*NumberNodes);

	for (int i = 0; i < NumberNodes; i++)
	{
		M[i]= (float*) malloc(sizeof(float)*NumberNodes);
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
			M[Nodes[i].outputs[j]][i]=(float)1/(Nodes[i].outputsNumber);
		}
	}
	
	return M;
}

float* init_vector(float* R, int NumberNodes){
	R = (float*) malloc(sizeof(float)* NumberNodes);

	//At the beginning, each node has probability 1/N to be chosen
	for (int i = 0; i < NumberNodes; i++)
	{
		R[i] = (float)1/NumberNodes;
	}

	return R;

}

float* calculate_vector(float** M,float* R,int NumberNodes,float dampingFactor){

	

	/** Power method **/
	//R = P1 + P2
	//R = dMR + ((1-d)/N)V1 	where d is the damping factor

	//Calculate P1 = dMR
	float* P1 = NULL;
	P1 = (float*) malloc(sizeof(float)*NumberNodes);
	//P1=MR
	P1 = calculate_matrix_vector(M,R, NumberNodes);
	//P1=dMR
	P1 = calculate_vector_number(P1,dampingFactor,NumberNodes);


	//Calculate P2 = ((1-d)/N)V1 = p3V1
	//V1 is the vector with only ones so P2 is the vector with only p3

	float p3= (1-dampingFactor)/NumberNodes;

	float* P2 = NULL;
	P2 = (float*) malloc(sizeof(float)*NumberNodes);

	for (int i = 0; i < NumberNodes; i++)
	{
		P2[i] = p3;
	}
	
	/*
	printf("P1/\n");
	print_R(P1,NumberNodes);

	printf("P2/\n");
	print_R(P2,NumberNodes);
	*/

	//Calculate R

	R=addition_vector(P1,P2,NumberNodes);

	
	return R;

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

void print_matrice(float** M, int NumberNodes){
	for (int i = 0; i < NumberNodes; i++)
	{
		for (int j = 0; j < NumberNodes; j++)
		{
			printf("%.3f | ",M[i][j] );
		}
		printf("\n");
	}
}

void print_R(float* R, int NumberNodes){

	for (int i = 0; i < NumberNodes; i++)
	{
		printf("%.3f\n", R[i]);
	}
}

float* calculate_matrix_vector(float** Matrix, float* Vector, int NumberNodes){

	float* Result= NULL;
	Result = (float*) malloc(sizeof(float)*NumberNodes);

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

float* addition_vector(float* Vector1, float* Vector2, int NumberNodes){

	for (int i = 0; i < NumberNodes; i++)
	{
		Vector1[i] = Vector1[i] + Vector2[i];
	}

	return Vector1;
}

float* calculate_vector_number(float* Vector, float Number, int NumberNodes){
	
	for (int i = 0; i < NumberNodes; i++)
	{
		Vector[i] = Vector[i]*Number;
	}

	return Vector;
}