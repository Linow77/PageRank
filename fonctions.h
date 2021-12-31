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
//functions
Node* init_nodes(Node* Nodes, int NumberNodes, char* fileName);
float** init_matrice(float** M, int NumberNodes, Node* Nodes);
float* init_vector(float* R, int NumberNodes);
float* calculate_vector(float** M,float* R,int NumberNodes, float dampingFactor);


//utils
void print_outputs(Node* Nodes, int NumberNodes);
void print_matrice(float** M, int NumberNodes);
void print_Vector(float* R, int NumberOfLine);
float* calculate_matrix_vector(float** Matrix, float* Vector, int NumberNodes);
float* addition_vector(float* Vector1, float* Vector2, int NumberNodes);
float* calculate_vector_number(float* Vector, float Number, int NumberNodes);

#endif