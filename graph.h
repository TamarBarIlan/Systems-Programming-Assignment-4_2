#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode dest_node;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int visit;
    int weight;
    int id_node;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph(pnode *head);
pnode find_prev_node(pnode *head, int id_to_find);
void insert_node(pnode *head);
void delete_node(pnode *head);
void delete_graph(pnode *head);
void free_node (pnode *curr);
int shortsPath(pnode *head, int src, int dest);
void delete_edge(pnode *curr, int id);
pnode find_node(pnode *head, int id);
pnode low_n(pnode *head);
void swap(int* a, int *b);
void permotion(pnode *head, int arr[], int size, int num_of_cities);
void TSP(pnode *head);


#endif