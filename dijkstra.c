#include "dijkstra.h"

void dijkstraCommercial(adj_array_node *array, int src, int d_nhops[], int d_route[]){
    int parent[SIZE]={0};
    d_nhops[src]=0;
    d_route[src]=1;

    deque_node *queue_clients=NULL;
    deque_node *queue_peers=NULL;
    deque_node *queue_providers=NULL;

    parent[src]=src;
    queue_providers=append(queue_providers,src);
    bool flag_abort=false;

    while(queue_clients!=NULL || queue_peers!=NULL|| queue_providers!=NULL){
        
    }
    
}