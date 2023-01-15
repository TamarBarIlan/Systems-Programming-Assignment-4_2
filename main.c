#include <stdio.h>
#include "graph.h"

int main(){
    pnode temp= NULL;
    pnode *head= &temp;
    char method= ' ';
    while(scanf("%c", &method) != EOF){
        if(method == 'A'){
            build_graph(head);
        }
        else if(method == 'B'){
            insert_node(head);
        }
        else if(method == 'D')
        {
            delete_node(head);
        }
        else if(method == 'S'){
            int src= -1;
            int dest= -1;
            scanf("%d", &src);
            scanf("%d", &dest);
            int path= short_path(head, src, dest);
            printf("Dijsktra shortest path: %d \n", path);
        }
        else if(method == 'T'){
            TSP(head);
        }
    }
    delete_graph(head);
    return 0;
}