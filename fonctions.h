#ifndef FONCTIONS
#define FONCTIONS

/** STRUCTURES **/

typedef struct Node Node;
struct Node 
{
	int outputsNumber; 
	int maxOutputs;	//default value of 25
	int* outputs;
};


/** PROTOTYPES **/
//functions
Node* init_nodes(Node* Nodes, int NumberNodes, char* fileName);
double** init_matrice(double** M, int NumberNodes, Node* Nodes);
double* init_vector(double* R, int NumberNodes);
int calculate_vector(double** M,double* R,int NumberNodes, double dampingFactor, float epsilon);


//utils
void print_outputs(Node* Nodes, int NumberNodes);
void print_matrice(double** M, int NumberNodes);
void print_Vector(double* R, int NumberOfLine);
double* calculate_matrix_vector(double** Matrix, double* Vector, int NumberNodes);
void addition_vector(double* Vector1, double* Vector2, int NumberNodes);
void calculate_vector_number(double* Vector, double Number, int NumberNodes);

//free
void free_nodes(Node* Nodes, int NumberNodes);
void free_matrix(double** M, int NumberNodes);

#endif