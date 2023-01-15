#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <math.h>

#define INFINI 1000000
static int min = INFINI;

void delete_edge(pnode *node, int id)
{
    pnode temp = *node;
    pedge edge_temp = temp->edges;
    if (edge_temp == NULL)
    {
        return;
    }
    if (edge_temp->dest_node->id_node == id)
    {
        pedge edge_trash = edge_temp;
        (*node)->edges = edge_temp->next;
        free(edge_trash);
        return;
    }
    while (edge_temp->next != NULL)
    {
        if (edge_temp->next->dest_node->id_node == id)
        {
            pedge trash_edge = edge_temp->next;
            edge_temp->next = edge_temp->next->next;
            free(trash_edge);
            return;
        }
        edge_temp = edge_temp->next;
    }
    *node = temp;
}

void delete_node(pnode *head)
{
    int id;
    pnode prev = NULL;
    pnode temp = *head;
    pnode *this_head = NULL;

    scanf("%d", &id);

    if (temp->id_node == id)
    {
        this_head = head;
    }

    while (temp != NULL)
    {
        if (temp->next != NULL && temp->next->id_node == id)
        {
            prev = temp;
        }
        if (temp->next != NULL && temp->edges != NULL && temp->edges->dest_node->id_node == id)
        {
            pedge t_e = temp->edges;
            temp->edges = temp->edges->next;
            free(t_e);
            temp = temp->next;
            continue;
        }
        pedge t_e = temp->edges;
        if (t_e != NULL)
        {
            while (t_e->next != NULL)
            {
                if (t_e->next->dest_node->id_node == id)
                {
                    pedge curr_e = t_e->next;
                    t_e->next = curr_e->next;
                    free(curr_e);
                }
                else
                {
                    t_e = t_e->next;
                }
            }
        }
        temp = temp->next;
    }

    if (this_head != NULL)
    {
        pedge curr_e = (*this_head)->edges;
        while (curr_e != NULL)
        {
            pedge f_edge = curr_e;
            curr_e = curr_e->next;
            free(f_edge);
        }
        pnode t_n = *this_head;
        *this_head = t_n->next;
        free(t_n);
    }
    else if (prev != NULL)
    {
        pnode f_node = prev->next;
        pedge t_e = f_node->edges;
        while (t_e != NULL)
        {
            pedge curr_e = t_e;
            t_e = t_e->next;
            free(curr_e);
        }
        prev->next = f_node->next;
        free(f_node);
    }
}

void delete_graph(pnode *head)
{
    pnode temp_node = *head;
    while (temp_node != NULL)
    {
        pnode next_temp = temp_node->next;
        free_node(&temp_node);
        free(temp_node);
        temp_node = next_temp;
    }
    *head = NULL;
}

void free_node(pnode *curr)
{
    pedge temp_edge = (*curr)->edges;
    while (temp_edge != NULL)
    {
        pedge next_edge = temp_edge->next;
        free(temp_edge);
        temp_edge = next_edge;
    }
}

pnode find_node(pnode *head, int id)
{
    pnode n = *head;
    pnode temp = n;
    while (temp != NULL)
    {
        if (temp->id_node == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void insert_node(pnode *head)
{
    int id = -1;
    scanf("%d", &id);
    pnode new_node = find_node(head, id);
    if(new_node != NULL){
        free_node(&new_node);
        new_node->edges = NULL;
    }
    else
    {
        new_node = (pnode)malloc(sizeof(node));
        new_node->id_node = id;
        new_node->edges = NULL;
        new_node->next = NULL;
        pnode temp = *head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    int w = -1;
    int id_dest = -1;
    pnode node_dest;
     while (scanf("%d", &id_dest) && id_dest != EOF)
     {
        node_dest = find_node(head, id_dest);
        scanf("%d", &w);
        pedge new_edge = (pedge)malloc(sizeof(edge));
        new_edge->dest_node = node_dest;
        new_edge->weight = w;
        new_edge->next = new_node->edges;
        new_node->edges = new_edge;
     }
}

void build_graph(pnode *head)
{
    if (*head != NULL)
    {
        delete_graph(head);
    }
    pnode start = *head;
    int num_ver = -1;
    scanf("%d", &num_ver);
    start = (pnode)malloc(sizeof(node));
    start->id_node = 0;
    start->edges = NULL;
    start->next = NULL;
    pnode temp = start;
    for(int i = 1; i < num_ver; i++){
        pnode new_node = (pnode)malloc(sizeof(node));
        new_node->id_node = i;
        new_node->edges = NULL;
        new_node->next = NULL;
        temp->next = new_node;
        temp = temp->next;
    }
    int counter = num_ver;
    int id_dest = -1, w = -1, id_curr_node = -1;
    pnode curr_node, dest_node;
    char ch = ' ';
    *head = start;
    while(scanf("%c", &ch) && ch != EOF){
        if(ch == 'n'){
            scanf("%d", &id_curr_node);
            curr_node = find_node(head, id_curr_node);
            while(scanf("%d", &id_dest) != 0 && id_dest != EOF ){
                scanf("%d", &w);
                dest_node = find_node(head, id_dest);
                pedge new_edge = (pedge)malloc(sizeof(edge));
                new_edge->dest_node = dest_node;
                new_edge->weight = w;
                new_edge->next = curr_node->edges;
                curr_node->edges = new_edge;
            }
            counter--;
        }
        if(counter == 0){
            break;
        }
    }
    *head = start;
}



pnode low_n(pnode *head)
{
    pnode temp = *head;
    pnode min = temp;
    int maxi = INFINI;
    while (temp != NULL)
    {
        if (temp->weight < maxi)
        {
            if (temp->visit == 0)
            {
                maxi = temp->weight;
                min = temp;
            }
        }
        temp = temp->next;
    }
    return min;
}

int shortsPath(pnode *head, int src, int dest)
{
    pnode temp = *head;
    int counter = 0;
    while (temp != NULL)
    {
        temp->weight = INFINI - 10;
        temp->visit = 0;
        counter++;
        temp = temp->next;
        
    }
    pnode node_src = find_node(head, src);
    node_src->weight = 0;
    while (counter > 0)
    {
        node_src = low_n(head);
        if (node_src->id_node == dest)
        {
            return node_src->weight;
        }
        pedge s_edge = node_src->edges;
        node_src->visit = 1;
        while (s_edge != NULL)
        {
            if (node_src->weight + s_edge->weight < s_edge->dest_node->weight)
            {
                s_edge->dest_node->weight = node_src->weight + s_edge->weight;
            }
            s_edge = s_edge->next;
        }
        counter--;
    }
    return 0;
}

void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}


void permotion(pnode *head, int arr[], int size, int num_of_cities)
{
    if (size == 1)
    {
        int path = 0;
        for (int j = 0; j < num_of_cities - 1; j++)
        {
            path += shortsPath(head, arr[j], arr[j + 1]);
        }
        if (path < min)
        {
            min = path;
        }
        return;
    }
    for (int j = 0; j < size; j++)
    {
        permotion(head, arr, size - 1, num_of_cities);
        if (size % 2 == 1)
        {
            swap(&arr[0], &arr[size - 1]);
        }
        else
        {
            swap(&arr[j], &arr[size - 1]);
        }
    }
}

void TSP(pnode *head)
{
    min = INFINI;
    int num = -1;
    int size = -1;
    scanf("%d", &size);
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &num);
        arr[i] = num;
    }
    permotion(head, arr, size, size);
    int eps = 3;
    if (INFINI - min <= eps)
    {
        min = -1;
    }
    printf("TSP shortest path: %d \n", min);
}