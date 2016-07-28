#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "graphs.h"

//Random int b/w 0 and int
int randInt(int);

/*Initializes the graph given the graph and directed information
*/
void initialize_graph(graph* g, int directed) {
	int i;

	srand(time(0));
	g->nedges=g->nvertices = 0;

	g->directed = directed;

	for (i = 1; i <= MAXV; i++) g->degree[i] = 0;
	for (i = 1; i <= MAXV; i++) g->edges[i] = NULL;


}


void insert_edge(graph* g, int x, int y, bool directed) {

	edgenode *p = new edgenode{};

	p->weight = 0;
	p->y = y;
	p->next = g->edges[x]; //Add to LL of edges

	g->edges[x] = p; 

	g->degree[x]++;

	if (directed)
		g->nedges++;

	else
		insert_edge(g, y, x, true);

}

/*Auto generates the graph

As of now, each node will always have an income or outgoing edge
*/
void autogen_graph(graph* g, bool directed,bool connected) {
	using namespace std;
	cout << "AUTO GENERATING VERTICES......" << endl<<endl;

	initialize_graph(g, directed);

	g->nvertices = randInt(MAXV-1)+1;

	cout << "Number of vertices: " << g->nvertices<<endl;

	//vertices have to start 1 for some reason
	for (int i = 1; i <= g->nvertices; i++) {
		int outDegree = randInt(MAXOUT-connected)+connected;

		for (int o = 0; o < outDegree; o++) {
			//ensure the other vertice is from 1...n
			insert_edge(g, i, randInt(g->nvertices-connected)+connected, directed);
			g->nedges++;
		}

	}



}

int randInt(int max) {
	return  (rand() % (max));


}

void read_graph(graph *g, bool directed) {
	int i; //counter
	int m; //num of edges
	int x,y; //vertices in edge (x,y)

	initialize_graph(g, directed);

	printf("Numer of Vertices: ");
	scanf("%d", &(g->nvertices));
	printf("\nNumber of Edges: ");
	scanf("%d", &m);

	printf("Please Specify Edges now in format \"X Y\", where X is src and y is dest edge\n");
	for (i = 1; i <= m; i++) {
		scanf("%d %d", &x, &y);
		insert_edge(g, x, y, directed);

	}
	
}

void print_graph(graph* g) {
	int i; //Counter
	edgenode *p;


	printf("\n---Outputting Edge information---\n");
	printf("How to interpret: \"src: dest1 dest2 ...\"\n");
	for (i = 1; i <= g->nvertices; i++) {
		printf("%d: ", i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d", p->y);
			p = p->next;

		}
		
		printf("\n");

	}
}