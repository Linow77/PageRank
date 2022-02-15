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

typedef struct sparseLink sparseLink;
struct sparseLink 
{
	double value; 
	int line;	
	int column;
};

//VARIABLES 
#define MAX_LENGTH 100
#define ADDITIONAL_NODE 100
#define MIN_NUMBER_NODE 1000

/** PROTOTYPES **/
//functions
int format_data_file(char* fileName,int* notUsedNode, int* NumberNodes);
Node* init_nodes(Node* Nodes, int NumberNodes, char* fileName, int* notUsedNode, int nbNotUsed);
sparseLink* init_sparse_matrix(sparseLink* sparseM, int* nbValue, int NumberNodes, Node* Nodes);
double* init_vector(double* R, int NumberNodes);
int calculate_vector(sparseLink* sparseM, double* R, int nbValue, int NumberNodes,double dampingFactor, float epsilon);
double* calculate_matrix_vector(sparseLink* sparseM, double* Vector, int nbValue, int NumberNodes);
void addition_vector(double* Vector1, double* Vector2, int NumberNodes);
void calculate_vector_number(double* Vector, double Number, int NumberNodes);
double addition_result(double* Vector, int NumberNodes);

//utils
void print_outputs(Node* Nodes, int NumberNodes);
void print_Vector(double* R, int NumberOfLine);


//free
void free_nodes(Node* Nodes, int NumberNodes);

// void calculate_matrix_number(sparseLink* sparseM, int nbValue, double dampingFactor);
#endif