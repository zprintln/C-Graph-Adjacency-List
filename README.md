# Graph Data Structure and Algorithms

This project implements a graph data structure along with various graph algorithms in C. The project includes functionalities to create, modify, and analyze a graph using an adjacency list representation.

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
- [Graph Functions](#graph-functions)
- [Test Functions](#test-functions)
- [Resources](#resources)

## Overview

A graph is a data structure that consists of a set of nodes (vertices) connected by edges (links). Each edge connects two nodes and can be directed or undirected, depending on the type of graph.

The main components of the graph implementation include:
- `graph_t`: The graph structure that holds the number of nodes, number of edges, and a doubly linked list of nodes.
- `graph_node_t`: The node structure representing a single node in the graph. It contains data, in-neighbors, and out-neighbors.
- `dll_t`: The doubly linked list used to store in-neighbors and out-neighbors of each node.

Graph functions include adding nodes, adding edges, removing nodes, removing edges, finding nodes, checking if an edge exists, getting in-neighbors and out-neighbors, checking reachability between nodes, and detecting cycles in the graph.

## Getting Started

### Prerequisites

Before running the project, ensure that you have the following prerequisites:
- C Compiler (e.g., GCC)

### Compilation

To compile the project, follow these steps:
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Use the C compiler to build the project:

```bash
gcc -o main main.c my_dll.c my_graph.c -lm
```

4. Execute the compiled program:

```bash
./main
```

## Graph Functions

The graph functions implemented in `my_graph.c` are as follows:

- `graph_t* create_graph()`: Creates and initializes a new graph.

- `graph_node_t* create_graph_node(int value)`: Creates a new graph node with the given value.

- `int graph_add_node(graph_t* g, int value)`: Adds a new node with the given value to the graph.

- `graph_node_t* find_node(graph_t* g, int value)`: Finds and returns the node with the given value in the graph.

- `int contains_edge(graph_t* g, int source, int destination)`: Checks if an edge exists between the source and destination nodes.

- `int graph_add_edge(graph_t* g, int source, int destination)`: Adds an edge from the source to the destination node.

- `int graph_remove_edge(graph_t* g, int source, int destination)`: Removes an edge from the source to the destination node.

- `int graph_remove_node(graph_t* g, int value)`: Removes a node and all its associated edges from the graph.

- `dll_t* getInNeighbors(graph_t* g, int value)`: Returns the in-neighbors of the node with the given value.

- `dll_t* getOutNeighbors(graph_t* g, int value)`: Returns the out-neighbors of the node with the given value.

- `int graph_is_reachable(graph_t* g, int source, int dest)`: Checks if a path exists between the source and destination nodes using Breadth-First Search (BFS).

- `int graph_has_cycle(graph_t* g)`: Checks if the graph contains a cycle using Depth-First Search (DFS).

- `void free_graph(graph_t* g)`: Frees the memory occupied by the graph and its components.

## Test Functions

The test functions provided in `main.c` are used to validate the functionality of the graph operations:

- `test_create_graph()`: Tests the creation of a new graph.

- `test_add_node()`: Tests adding a new node to the graph.

- `test_find_node()`: Tests finding a node in the graph.

- `test_graph_add_edge()`: Tests adding an edge between nodes in the graph.

- `test_contains_edge()`: Tests checking if an edge exists between nodes in the graph.

- `test_graph_remove_edge()`: Tests removing an edge between nodes in the graph.

- `test_graph_remove_node()`: Tests removing a node from the graph.

- `test_getInNeighbors()`: Tests retrieving in-neighbors of a node.

- `test_getOutNeighbors()`: Tests retrieving out-neighbors of a node.

- `test_graph_is_reachable()`: Tests checking reachability between nodes.

- `test_graph_has_cycle()`: Tests checking if the graph contains a cycle.

## Resources

The following resources were used to learn about graphs and implement the project:
- Knuth, D. E. (1997). The Art of Computer Programming, Volume 1: Fundamental Algorithms (3rd ed.).
- Sedgewick, R. (2011). Algorithms in C (3rd ed.).
- Tarjan, R. E. (1972). Depth-First Search and Linear Graph Algorithms. SIAM Journal on Computing, 1(2), 146-160.
- Tarjan, R. E. (1974). Efficient Algorithms for Graph Manipulation. Communications of the ACM, 16(9), 517-522.
- Wikipedia. (2023, April 7). Adjacency List. In Wikipedia, The Free Encyclopedia. Retrieved April 7, 2023, from https://en.wikipedia.org/wiki/Adjacency_list.
- Wikipedia. (2023, April 7). Graph (Abstract Data Type). In Wikipedia, The Free Encyclopedia. Retrieved April 7, 2023, from https://en.wikipedia.org/wiki/Graph_(abstract_data_type).
- GeeksforGeeks. (https://www.geeksforgeeks.org/)
- YouTube. (https://www.youtube.com/)

Feel free to use, modify, and expand upon this project for your own purposes. Happy coding!
