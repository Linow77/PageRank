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

/** PROTOTYPES **/
//functions
int format_data_file(char* fileName,int* notUsedNode, int* NumberNodes);
Node* init_nodes(Node* Nodes, int NumberNodes, char* fileName, int* notUsedNode, int nbNotUsed);
double** init_matrice(double** M, int NumberNodes, Node* Nodes);
sparseLink* init_sparse_matrix(sparseLink* sparseM, int* nbValue, int NumberNodes, Node* Nodes);
double* init_vector(double* R, int NumberNodes);
int calculate_vector(double** M,double* R,int NumberNodes, double dampingFactor, float epsilon);
int calculate_vector2(sparseLink* sparseM, double* R, int nbValue, int NumberNodes,double dampingFactor, float epsilon);


//utils
void print_outputs(Node* Nodes, int NumberNodes);
void print_matrice(double** M, int NumberNodes);
void print_Vector(double* R, int NumberOfLine);
double* calculate_matrix_vector(double** Matrix, double* Vector, int NumberNodes);
double* calculate_matrix_vector2(sparseLink* sparseM, double* Vector, int nbValue, int NumberNodes);
void addition_vector(double* Vector1, double* Vector2, int NumberNodes);
void calculate_vector_number(double* Vector, double Number, int NumberNodes);

//free
void free_nodes(Node* Nodes, int NumberNodes);
void free_matrix(double** M, int NumberNodes);

#endif