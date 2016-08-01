#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <queue>
#include <fstream>

#include "graphs.h"
#include "graph_algorithms.h"

//Random int b/w 0 and int
int randInt(int);

//================================BASIC GRAPH GENERATION=========================


/*Initializes the graph given the graph and directed information
*/
void initialize_graph(graph* g, int directed) {
	int i;

	srand(time(0));
	g->nedges=g->nvertices = 0;

	g->directed = directed;



	for (i = 1; i <= MAXV; i++) {
		g->degree[i] = 0;
		g->edges[i] = NULL;
		
	}


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
		int outDegree = randInt(MAXOUT)+connected;

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

bool save_to_file(graph *g, char* name) {
	using namespace std;
	bool success = false;

	ofstream outstream;

	outstream.open(name);

	if (outstream.is_open()) {
		outstream << "Number of Vertices:" << g->nvertices << endl;

		
		for (int i = 1; i <= g->nvertices; i++) {
			outstream << i << ": ";
			edgenode* p = g->edges[i];
			while (p != NULL) {
				outstream << " " << p->y;
				p = p->next;

			}
			outstream << endl;

		}
		outstream.close();

	}
	else {
		cout << "Failed to write to file";
		
	}

	return success;

}


//=================================GRAPH ALGORITHMS=========================

/*Resets the discoverable state of the nodes in the graph
*/
void init_discoverable(graph *g) {
	for (Vertex_t i = 0; i < MAXV; i++) {
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
}

void process_vertex_early(Vertex_t v) {
	std::cout << "Processed Vertex : " << v << std::endl;

}

void process_vertex(Vertex_t v, Vertex_t y) {


}

void process_edge(Vertex_t s, edgenode* e) {
	std::cout << "Processed edge b/w " << s << " and " << e->y << std::endl;

}

void process_vertex_late(Vertex_t) {


}

void bfs(graph *g, Vertex_t start) {
	using namespace std;

	init_discoverable(g);

	queue<int> q;
	Vertex_t v;	//curr vertex
	Vertex_t y; //successor
	edgenode *p; //temp pointer

	q.push(start);
	discovered[start] = true;

	while (!q.empty()) {
		v=q.front();
		q.pop();
		process_vertex_early(v);

		processed[v] = true;
		p = g->edges[v];
		//go through all edges
		while (p != nullptr) {
			y = p->y;

			if (!processed[y] || g->directed)
				process_edge(v, p);
			
			if (!discovered[y]) {
				q.push(y);
				parent[y] = v;
				discovered[y] = true;
			}

			p=p->next;
		}

		process_vertex_late(v);

	}


}