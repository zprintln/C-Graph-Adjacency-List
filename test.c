#include <stdio.h>
#include <stdlib.h>
#include "my_graph.h"
#include "my_dll.h"
//Test create graph function
void test_create_graph(){
    // Test create_graph() function
    graph_t* g = create_graph();
    if (g == NULL) {
        printf("Error: Could not create graph.\n");
    }else{
        printf("Success: Graph created.\n");
    }
    free_graph(g);
    return;
}
// Test graph_add_node() function
void test_add_node(){
    graph_t* g = create_graph();
    int ret = graph_add_node(g, 1);
    if (ret != 1) {
        printf("Error: Could not add node.\n");
    }else{
        printf("Success: Node added.\n");
    }
    free_graph(g);
    return;
}
// Test find_node() function
void test_find_node(){
    graph_t* g = create_graph();
    graph_add_node(g, 1);
    graph_node_t* n = find_node(g, 1);
    if (n == NULL) {
        printf("Error: Could not find node.\n");
    }else{
        printf("Success: Node found.\n");
    }
    free_graph(g);
    return;
}

//Test graph_add_edge() function
void test_graph_add_edge(){
    graph_t *g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 3);
    int ret = graph_add_edge(g, 3, 1);
    if(ret != 1){
        printf("Error: Edge could not be added. \n");
    }else{
        printf("Success: Edge added.\n");
    }
    free_graph(g);
    return;
}

// Test contains_edge() function
void test_contains_edge(){
    graph_t *g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_edge(g, 1, 2);
    int ans = contains_edge(g, 1, 2);
    if (ans != 1) {
        printf("Error: Edge not found.\n");
    }else{
        printf("Success: Node contains edge.\n");
    }
    free_graph(g);
    return;
}
// Test graph_remove_edge() function
void test_graph_remove_edge(){
    graph_t* g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_edge(g, 1, 2);
    int ret = graph_remove_edge(g, 1, 2);
    if (ret != 1) {
        printf("Error: Could not remove edge.\n");
    }else{
        printf("Success: Edge removed.\n");
    }
    free_graph(g);
    return;
}
 // Test graph_remove_node() function
void test_graph_remove_node(){
    graph_t* g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    int ret = graph_remove_node(g, 1);
    if (ret != 1) {
        printf("Error: Could not remove node.\n");
    }else{
        printf("Success: Node removed.\n");
    }
    free_graph(g);
    return;
}
// Test getInNeighbors() function
void test_getInNeighbors(){
    graph_t* g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_edge(g, 1, 2);
    dll_t* inNeighbors = getInNeighbors(g, 2);
    if (inNeighbors == NULL) {
        printf("Error: Could not get in neighbors.\n");
    }else{
        printf("Success: in-neighbors retrieved.\n");
    }
    free_graph(g);
    return;
}
 // Test getOutNeighbors() function
void test_getOutNeighbors(){
    graph_t* g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_edge(g, 2, 1);
    dll_t* outNeighbors = getOutNeighbors(g, 2);
    if (outNeighbors == NULL) {
        printf("Error: Could not get out neighbors.\n");
    }else{
        printf("Success: out-neighbors retrieved.\n");
    }
    free_graph(g);
    return;
}
   
void test_graph_is_reachable() {

    graph_t* g = create_graph();

    graph_add_node(g, 0);
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_node(g, 3);

    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 2);
    graph_add_edge(g, 0, 3);
    graph_add_edge(g, 1, 3);
    graph_add_edge(g, 2, 3);

    
    int source = 0;
    int dest = 3;
    int result = graph_is_reachable(g, source, dest);

    if (result == -1) {
        printf("test_graph_is_reachable: FAIL (graph is NULL)\n");
    }else if (result == 1) {
        printf("test_graph_is_reachable: PASS\n");
    }else{
        printf("test_graph_is_reachable: FAIL (expected 1 but got %d)\n", result);
    }
    free_graph(g);
    return;
}

void test_graph_has_cycle(){

    graph_t* g = create_graph();

    graph_add_node(g, 1);
    graph_add_node(g, 3);
    graph_add_node(g, 2);
    graph_add_node(g, 4);
    graph_add_node(g, 5);

    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 3);
    graph_add_edge(g, 3, 4);
    graph_add_edge(g, 4, 5);
    graph_add_edge(g, 5, 1);

    graph_add_edge(g, 2, 5);
    graph_add_edge(g, 5, 2);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 4);
    graph_add_edge(g, 4, 5);

    //check if edges exist between all nodes 
    printf("Path from %d to %d, expected %d = %d \n",2, 5, 1, graph_is_reachable(g, 2, 5));
    printf("Path from %d to %d, expected %d = %d \n",5, 2, 1, graph_is_reachable(g, 5, 2));
    printf("Path from %d to %d, expected %d = %d \n",1, 5, 1, graph_is_reachable(g, 1, 5));
    printf("Path from %d to %d, expected %d = %d \n",4, 1, 1, graph_is_reachable(g, 4, 1));

    //Test graph_has_cycle() function
    int cycle = graph_has_cycle(g);
    printf("Cycle expected %d = %d \n",1, cycle);

    free_graph(g);
    return;
}

int main(){   
    // Test create graph function
    test_create_graph();

    // Test graph_add_node() function
    test_add_node();

    // Test find_node() function
    test_find_node();

    //Test graph_add_edge() function
    test_graph_add_edge();

    // Test contains_edge() function
    test_contains_edge();

    // Test graph_remove_edge() function
    test_graph_remove_edge();

    // Test graph_remove_node() function
    test_graph_remove_node();

    // Test getInNeighbors() function
    test_getInNeighbors();

    // Test getOutNeighbors() function
    test_getOutNeighbors();
    
    // Test graph_is_reachable() function
    test_graph_is_reachable();

    // Test has cycle 
    test_graph_has_cycle();
  
    // All tests passed
    printf("All tests passed.\n");

    return 0;
}
