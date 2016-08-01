#pragma once

#include "graphs.h"

bool processed[MAXV + 1], discovered[MAXV + 1];

int parent[MAXV + 1];

/*Conduct a BFS of the graph start at node numbered start

WARNING: This function does not auto-init the graph. You must do so yourself.
*/
void bfs(graph *g, Vertex_t start);
