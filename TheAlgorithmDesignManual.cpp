// TheAlgorithmDesignManual.cpp : Defines the entry point for the console application.
//
// This is mainly just used for testing

#include "graphs.h"

//TODO: CONVERT TO C++!!
int main()
{
	graph g;

	autogen_graph(&g, true);
	//read_graph(&g, true);

	print_graph(&g);

    return 0;
}

