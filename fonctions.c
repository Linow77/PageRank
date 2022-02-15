#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fonctions.h"

//Format the data file if needed
int format_data_file(char* fileName, int* notUsedNode, int* NumberNodes){

	//Get data from file and transfer them to Nodes
	FILE* file = NULL;
	char string[MAX_LENGTH] = "";
	char delimiter[] = " \t";
	char* part1 = "";
	char* part2 = "";
	int node1;
	int node2;
	int previousNode = -1;
	int nodeCount = 0;

	//adding .txt to fileName
	char data[strlen(fileName)+4];
	strcpy(data,fileName);
	strcat(data,".txt");

	//open file in reading mode
	file = fopen(data, "r");

	//check for any error while opening file
	if(!file){
		printf("%s\n","Impossible d'ouvrir le fichier" );
	}

	/** Check if somes Node are not used in order to get a clean Nodes Table**/
	int nbUsedNode = MIN_NUMBER_NODE;
	int lastnbUsedNode = nbUsedNode;
	int * usedNodes = (int*) malloc(sizeof(int)*nbUsedNode);
	//init usedNodes to all 
	for (int i = 0; i < nbUsedNode; ++i)
	{
		usedNodes[i]=0;
	}
	//get the first line of the file
	while (fgets(string,MAX_LENGTH,file) != NULL){
		//get the two nodes of the lines
		part1 = strtok(string,delimiter);
		part2 = strtok(NULL,delimiter);

		//convert string into int
		node1 = atoi(part1);
		node2 = atoi(part2);

		//Check if node1 or node2 is bigger than nbUsedNode
		if (node1 >= nbUsedNode || node2 >= nbUsedNode){
			//realloc tab
			lastnbUsedNode= nbUsedNode;
			if(node1>=node2){
				nbUsedNode = node1+1;
			}else {
				nbUsedNode = node2+1;
			}

			usedNodes = (int*) realloc(usedNodes,sizeof(int)*nbUsedNode);
			for (int i = lastnbUsedNode; i < nbUsedNode; ++i)
			{
				usedNodes[i] = 0;
			}
		}
		usedNodes[node1] = -1;
		usedNodes[node2] = -1;
	}

	//Keep the nodes that are not used
	int nbNotUsed = ADDITIONAL_NODE;
	int notUsedcount = 0;
	for (int i = 0; i < nbUsedNode; ++i)
	{
		if(usedNodes[i]==0){
			//check if notUsed tab is not full
			if(notUsedcount==nbNotUsed){
				//realloc
				nbNotUsed=+ADDITIONAL_NODE;
				notUsedNode = (int*) realloc(notUsedNode,sizeof(int)*nbNotUsed);
			}
			notUsedNode[notUsedcount] = i;
			notUsedcount++;
		}
	}

	*NumberNodes = nbUsedNode-notUsedcount;
	//realloc tab to the correct number
	usedNodes = (int*) realloc(usedNodes,sizeof(int)*(*NumberNodes));
	fclose(file);

	return notUsedcount;
}

//Create the Graph with Node struct
Node* init_nodes(Node* Nodes, int NumberNodes, char* fileName, int* notUsedNode, int notUsedcount){
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
	int previousNode = -1;
	int nodeCount = 0;

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

	/** Fill Nodes Table with clean informations **/


	while (fgets(string,MAX_LENGTH,file) != NULL){
		//get the two nodes of the lines
		part1 = strtok(string,delimiter);
		part2 = strtok(NULL,delimiter);

		//convert string into int
		node1 = atoi(part1);
		node2 = atoi(part2);

		//Check if node1 or node2 is after not used nodes
		int node1Decrement = 0;
		int node2Decrement = 0;
		for (int i = 0; i < notUsedcount; ++i)
		{
			if(node1 > notUsedNode[i]){
				node1Decrement++;
			}
			if(node2 > notUsedNode[i]){
				node2Decrement++;
			}
		}	


		//adjust node1 and node2
		node1 = node1 - node1Decrement;
		node2 = node2 - node2Decrement;

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

//Use Sparse Matrix properties to store Matrix in 1D with sparseLink struct
sparseLink* init_sparse_matrix(sparseLink* sparseM, int* nbValue, int NumberNodes,Node* Nodes){

	//sparseM size is equal to the number of value in the matrix which are not equal to 0
	int actualValue = 0;
	int lastValue = 0;


	//For each Nodes
	for (int i = 0; i < NumberNodes; i++)
	{

		//Examine each outputs
		for (int j = 0; j < Nodes[i].outputsNumber; j++)
		{
			//Check if matrix is full
			if(actualValue == *nbValue){
				//realloc
				lastValue = *nbValue;
				*nbValue = *nbValue + NumberNodes;
				sparseM = (sparseLink*) realloc(sparseM,sizeof(sparseLink)*(*nbValue));

				for (int i = lastValue; i < *nbValue; ++i)
				{
					sparseM[i].value = 0;
					sparseM[i].line = -1;
					sparseM[i].column = -1;
				}

			}

			sparseM[actualValue].value = 1.0/Nodes[i].outputsNumber;
			sparseM[actualValue].line = Nodes[i].outputs[j];
			sparseM[actualValue].column = i;

			actualValue++;
		}
	}

	return sparseM;
}

//Init Vector R with 1/NumberNodes for each parameters
double* init_vector(double* R, int NumberNodes){
	R = (double*) malloc(sizeof(double)* NumberNodes);

	//At the beginning, each node has probability 1/N to be chosen
	for (int i = 0; i < NumberNodes; i++)
	{
		R[i] = 1.0/NumberNodes;
	}

	return R;
}

//Calculate R with M matrix 1D
int calculate_vector(sparseLink* sparseM, double* R, int nbValue,int NumberNodes,double dampingFactor, float epsilon){

	/** Power method **/
	//R = P1 + P2
	//R = dMR + ((1-d)/N)V1 	where d is the damping factor

	//Calculate P1 = dMR
	double* P1 = NULL;
	//P1=MR
	P1 = calculate_matrix_vector(sparseM,R, nbValue,NumberNodes);

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

	//Check if precision epsilon is good
	int finished = 1;
	for (int i = 0; i < NumberNodes; i++)
	{
		//If one component of the vector is not precised enough, continue to iterate
		if(fabs(P1[i]-R[i]) > (double)epsilon){
			finished = 0;
		}
	}

	//Store result in R
	for (int i = 0; i < NumberNodes; i++)
	{
		R[i]= P1[i];
	}

	//free temp
	free(P1);
	free(P2);

	return finished;
}

//Calculate dM with M matric 1D
void calculate_matrix_number(sparseLink* sparseM, int nbValue, double dampingFactor){

	for (int i = 0; i < nbValue; ++i)
	{
		sparseM[i].value = dampingFactor * sparseM[i].value;
	}

}

//Calculate MR with M matrix 1D
double* calculate_matrix_vector(sparseLink* sparseM, double* Vector, int nbValue, int NumberNodes){

	double* Result= NULL;
	Result = (double*) malloc(sizeof(double)*NumberNodes);

	for (int i = 0; i < NumberNodes; ++i)
	{
		Result[i] = 0;
	}

	for (int i = 0; i < nbValue; ++i)
	{
		Result[sparseM[i].line] +=  sparseM[i].value*Vector[sparseM[i].column];
	}

	return Result;
}

//Addition vector1 and Vector2
void addition_vector(double* Vector1, double* Vector2, int NumberNodes){

	for (int i = 0; i < NumberNodes; i++)
	{
		Vector1[i] = Vector1[i] + Vector2[i];
	}
}

//Calculate Vector* Number
void calculate_vector_number(double* Vector, double Number, int NumberNodes){
	
	for (int i = 0; i < NumberNodes; i++)
	{
		Vector[i] = Vector[i]*Number;
	}
}

double addition_result(double* Vector, int NumberNodes){

	double result = 0.0;

	for (int i = 0; i < NumberNodes; ++i)
	{
		result += Vector[i];
	}

	return result;
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

void print_Vector(double* R, int NumberOfLine){

	for (int i = 0; i < NumberOfLine; i++)
	{
		printf("%.3f\n", R[i]);
	}
}

//Free functions
void free_nodes(Node* Nodes, int NumberNodes){
	for (int i = 0; i < NumberNodes; i++)
	{
		//free int tab
		free(Nodes[i].outputs);
	}
	free(Nodes);

}