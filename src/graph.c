#include "graph.h"

Hashmap wd_graph;

void setup_graph(void){
    wd_graph = hashmap_create(HASHMAP_LEN);
    hashmap_init(wd_graph, HASHMAP_LEN);
}

