// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>

// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){

    graph_t* myGraph = (graph_t*)malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    if(myGraph == NULL){
        return NULL;
    }
    return myGraph;
}

//Function delcarations 
dll_t* getInNeighbors( graph_t * g, int value );
dll_t* getOutNeighbors( graph_t * g, int value );
int graph_remove_edge(graph_t * g, int source, int destination);

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
    //graph is null, return null
    if(g == NULL){
        return NULL;
    }
    //iterate through dll to find a node
    node_t* tempNode = g->nodes->head;
    while(tempNode != NULL){
        //if exists return pointer to node
        if(*(int*)tempNode->data == value){
            return tempNode->data;
        }
        //itr to next node
        tempNode = tempNode->next;
    }
    //if doesn't exist return null
    return NULL;
}

// Creates and returns a new graph node with the given value.
// Initializes the node's data, in-neighbors and out-neighbors to NULL.
// Returns NULL if there is an error allocating memory for the new node.
// Otherwise, returns a pointer to the newly created graph node.
graph_node_t * create_graph_node(int value){

    graph_node_t* graph_node = (graph_node_t*)malloc(sizeof(graph_node_t));
    
    if (graph_node == NULL){
        return NULL;
    } 
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if (g == NULL){
        return -1;
    } 
    
    if(find_node(g, value) != NULL){
        return -1;
    }
    
    graph_node_t * newNode = create_graph_node(value);
    if(newNode == NULL){
        return -1;
    }
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge(graph_t *g, int source, int destination) {
    if (g == NULL) {
        return -1;
    }
    graph_node_t* srcNode = find_node(g, source);
    if (srcNode == NULL) {
        return 0;
    }
    node_t* destNeighbors = srcNode->outNeighbors->head;
    while (destNeighbors != NULL) {
        if (*(int *)destNeighbors->data == destination) {
            return 1;
        }
        destNeighbors = destNeighbors->next;
    }
    return 0;
}

//This function removes the node from the graph along with any edges associated with it.
//That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value) {
    // If the graph is null, return -1
    if (g == NULL) {
        return -1;
    }

    // Find the node to remove
    graph_node_t* nodeToRemove = find_node(g, value);

    // Find the index of the node in the list of nodes
    node_t* itr = g->nodes->head;
    int nodeIndex = 0;
    while (*(int*)itr->data != value) {
        nodeIndex++;
        itr = itr->next;
    }

    // Remove any edges pointing to the node to remove
    dll_t* inNeighbors = getInNeighbors(g, value);
    node_t* inNeighborItr = inNeighbors->head;
    for (int i = 0; i < inNeighbors->count; i++) {
        int source = *(int*)inNeighborItr->data;
        graph_remove_edge(g, source, value);
        inNeighborItr = inNeighborItr->next;
    }
    free_dll(inNeighbors);

    // Remove any edges pointing from the node to remove
    dll_t* outNeighbors = getOutNeighbors(g, value);
    node_t* outNeighborItr = outNeighbors->head;
    for (int i = 0; i < outNeighbors->count; i++) {
        int dest = *(int*)outNeighborItr->data;
        graph_remove_edge(g, value, dest);
        outNeighborItr = outNeighborItr->next;
    }
    free_dll(outNeighbors);

    // Free memory used by the node to remove
    free(nodeToRemove);

    // Remove the node from the list of nodes
    dll_remove(g->nodes, nodeIndex);
    g->numNodes--;

    // Return 1 on success
    return 1;
}

// This function adds an edge from source to destination but not the other way.
// It will not add the same edge multiple times.
// In and out neighbors are modified appropriatelly.
// Destination will be an out neighbor of source.
// Source will be an in neighbor of destination.
// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // int resultSource = 0; // flag to indicate success/failure of adding edge to source node
    // int resultDest = 0; // flag to indicate success/failure of adding edge to destination node
  
    if(g == NULL){
        return -1; // if the graph is NULL, return -1
    }

    // find source and destination nodes
    graph_node_t* tempSourceNode =  find_node(g, source);
    graph_node_t* tempDestNode =  find_node(g, destination);

    // if either source or destination node is NULL, return 0
    if(tempSourceNode == NULL || tempDestNode == NULL){
        return 0;
    }

    // check if edge already exists, if so return 0
    if(contains_edge(g, source, destination) == 1){
        return 0;
    }
    else{
        // add destination to source's out neighbors and source to destination's in neighbors
       dll_push_back(tempSourceNode->outNeighbors, tempDestNode);
       dll_push_back(tempDestNode->inNeighbors, tempSourceNode); 
       g->numEdges++;
       return 1;
    }
    return 0;
}

//The function removes an edge from source to destination but not the other way.
//Make sure you remove destination from the out neighbors of source.
//Make sure you remove source from the in neighbors of destination.
// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){

    int posOfNode; //represents the position of a node in a dll

    if(g == NULL){
        return -1; // if the graph is NULL, return -1
    }

    // find the source and destination nodes in the graph
    graph_node_t* tempSourceNode =  find_node(g, source);
    graph_node_t* tempDestNode =  find_node(g, destination);

    // check if either the source or destination node is NULL
    if(tempSourceNode == NULL || tempDestNode == NULL){
        return 0;
    }

    // check if the edge exists, if so return 0
    if(contains_edge(g, source, destination) == 0){
        return 0;
    }
    else{
        //get position of source in inNeighboors of dest
        posOfNode = dll_get_pos(tempDestNode->inNeighbors, source);
        //remove source from the in neighbors of destination.
        if(posOfNode != -1){
            dll_remove(tempDestNode->inNeighbors, posOfNode);
        }

        //get position of destination in outNeighboors of source
        posOfNode = dll_get_pos(tempSourceNode->outNeighbors, destination);
        //remove destination from the out neighbors of source. 
        if(posOfNode != -1){
            dll_remove(tempSourceNode->outNeighbors, posOfNode);
        }
        g->numEdges--;
        return 1;
    }
    return 0;
   
}
// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if the node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    if(g == NULL){
        return NULL; // if the graph is NULL, return -1
    }
    graph_node_t* tempNode = find_node(g, value);

    if(tempNode == NULL){
        return NULL;
    }
    return tempNode->inNeighbors;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    if(g == NULL){
        return -1;
    }
    graph_node_t* tempNode = find_node(g, value);

    if(tempNode == NULL){
        return -1;
    }

    return tempNode->inNeighbors->count;
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if the node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    if(g == NULL){
        return NULL; // if the graph is NULL, return -1
    }
    graph_node_t* tempNode = find_node(g, value);

    if(tempNode == NULL){
        return NULL;
    }
    return tempNode->outNeighbors;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    if(g == NULL){
        return -1;
    }
    graph_node_t* tempNode = find_node(g, value);

    if(tempNode == NULL){
        return -1;
    }
    return tempNode->outNeighbors->count;
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if(g == NULL){
        return -1; // if the graph is NULL, return -1
    }
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if(g == NULL){
        return -1; // if the graph is NULL, return -1
    }
    return g-> numEdges;
}

// returns 1 if we can reach the destination from source
// returns 0 if it is not reachable
// returns -1 if the graph is NULL 
// use BFS
int graph_is_reachable(graph_t * g, int source, int dest) {
    if(g == NULL){
        return -1; //return -1 if graph is NULL
    }

    // find the source node from the graph
    graph_node_t* srcNode = find_node(g, source);

    if(srcNode == NULL){
        return 0; //check the source node exists, if not return 0
    }

    //initialize a new doubly linked list to store visited nodes
    dll_t* visited = create_dll();
    //initialize a new doubly linked list to store nodes in the queue
    dll_t* queue = create_dll();

    dll_push_back(queue, srcNode); // add the source node to the queue
    dll_push_back(visited, srcNode); // mark the source node as visited

    // loop until the queue is empty
    while (dll_empty(queue) != 1) { 

        graph_node_t* currNode = dll_pop_front(queue);  // remove the front node from the queue

        // if the current node data is equal to destination value, return 1
        if (currNode->data == dest) {
            free_dll(queue); // free the queue memory
            free_dll(visited); // free the visited memory
            return 1;
        }

        // get the current node's out neighbors
        dll_t* currOutNeighbors = currNode->outNeighbors;
        // initialize a pointer to the current node's first out neighbor
        node_t* currNeighborNode = currOutNeighbors->head;

        while (currNeighborNode != NULL) { // iterate through each of the current node's out neighbors
            // get the current neighbor node
            graph_node_t* currNeighbor = currNeighborNode->data; /*(graph_node_t*)*///if doesn't work try casting

            if (dll_contains(visited, currNeighbor->data) != 1) { // if the neighbor has not been visited yet
                dll_push_back(queue, currNeighbor); // add the neighbor to the queue
                dll_push_back(visited, currNeighbor); // mark the neighbor as visited
            }
            currNeighborNode = currNeighborNode->next; // move to the next neighbor
        }
    }

    // free the queue memory
    free_dll(queue); 
    // free the visited memory
    free_dll(visited);
    // if the destination was not found, return 0
    return 0;
}

// returns 1 if there is a cycle in the graph
// returns 0 if no cycles exist in the graph
// returns -1 if the graph is NULL 
// use BFS
int graph_has_cycle(graph_t * g) {

    if (g == NULL) {
        return -1; //return -1 if graph is NULL
    }

    node_t* itr = g->nodes->head;

    // loop through each node in the graph
    while(itr != NULL){

        // find the current node from the graph
        graph_node_t* currNode = itr->data;

        node_t* currNeighborItr = currNode->outNeighbors->head;

        while (currNeighborItr != NULL) { // iterate through each of the current node's out neighbors
            // get the current neighbor graphnode
            graph_node_t* currNeighbor = currNeighborItr->data;

            if(graph_is_reachable(g, currNeighbor->data, currNode->data) == 1){ //graph has cycle, return 1
                return 1;
            }
            currNeighborItr = currNeighborItr->next; // move to the next neighbor
        }
        itr = itr->next;
    }
    // if no cycles were found, return 0
    return 0;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    if(g == NULL){
        exit(1); // if the graph is NULL, exit
    }
    //for each g->nodes, call free dll on the inNeighbors and outNeighbors
	node_t* tempItr = g->nodes->head;
    node_t* tempItrPrev;
    while(tempItr != NULL){
        graph_node_t* tempNode = tempItr->data;

        if(tempNode != NULL){
            free_dll(tempNode->inNeighbors);
            free_dll(tempNode->outNeighbors);
            free(tempNode);
        }
        tempItrPrev = tempItr;
        tempItr = tempItr->next;
        free(tempItrPrev);
    }
    free_dll(g->nodes);
    free(g);
}

#endif
