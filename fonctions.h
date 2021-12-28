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
int calcul(int a, int b);
Node* init_nodes(Node* Nodes, int NumberNodes);

#endif