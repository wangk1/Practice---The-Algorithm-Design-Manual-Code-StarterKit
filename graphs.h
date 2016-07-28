/*Starter Code for Graphs as seen in the book Algorithm Design Manual

License: Do whatever you want with it.
	It is encouraged to contribute to this code.

WARNING: THIS IS PRE ALPHA RELEASE CODE; as such, not all functionality are available.
	Moreover, it is not well tested. I WILL NOT be responsible for any issue occuring from
	the proper use of this code.

*/
#ifndef GRAPHS_H_
#define GRAPHS_H_

#define MAXV 1000 //Max # of vertices

#define MAXOUT 4 //Max # of out edges per node, only used for auto generation of graph


typedef struct edgenode {
	int y;
	int weight;
	edgenode *next;

} edgenode; 


typedef struct {
	struct edgenode *edges[MAXV + 1]; //adjacency info
	int degree[MAXV + 1]; //Outdegree of each vertex
	int nvertices; //number of vertices in graph
	int nedges; //number of edges in graph
	bool directed; //is the graph directed

} graph;

/*Auto generate the graph
Params:
 graph* g
 bool directed
 bool connected: Guarantee at least 1 outedge for each vertice

*/
void autogen_graph(graph* g,bool directed,bool connected=true);

//Manually generate the graph as seen in chapter 5 of Alg Des Man
void read_graph(graph *g, bool directed);

/*Print the graph. Its vertices and its edges

Format:
<vertex num>: <edge 1 num> <edge 2 num> ... <edge n num>
*/
void print_graph(graph* g);


#endif