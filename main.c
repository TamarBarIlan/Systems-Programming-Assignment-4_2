#include <stdio.h>
#include "graph.h"

int main(){
    char ch= 'x';
    pnode temp= NULL;
    pnode *head= &temp;
    while(scanf("%c", &ch) != EOF){
        if(ch == 'A'){
            build_graph(head);
        }
        else if(ch == 'B'){
            insert_node(head);
        }
        else if(ch == 'D')
        {
            delete_node(head);
        }
        else if(ch == 'S'){
            int src= -1;
            int dest= -1;
            scanf("%d", &src);
            scanf("%d", &dest);
            int path= shortsPath(head, src, dest);
            printf("Dijsktra shortest path: %d \n", path);
        }
        else if(ch == 'T'){
            TSP_cmd(head);
        }
    }
    deleteGraph(head);
    return 0;
}