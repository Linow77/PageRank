#ifndef FONCTIONS
#define FONCTIONS

/** STRUCTURES **/

typedef struct Node Node;
struct Node 
{

	int value;
	int inputsNumber;
	int outputsNumber; //default value of 25
	int maxOutputs;
	int* outputs;

};


/** PROTOTYPES **/
Node* init_nodes(Node* Nodes, int NumberNodes, char* fileName);
float** init_matrice(float** M, int NumberNodes, Node* Nodes);
void print_outputs(Node* Nodes, int NumberNodes);
void print_matrice(float** M, int NumberNodes);


#endif