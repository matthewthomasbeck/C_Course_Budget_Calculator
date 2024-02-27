#ifndef _graph_h
#define _graph_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "hashTable.h"
#include "point2D.h"
#include "priorityQueuePoint2D.h"

typedef Point2D graphType;

typedef struct Vertex
{
    graphType data;
    bool visited;   /* store whether this vertex has been visited */

    /* the successors are stored in the matrix at this index */
    int index;
    int currentSuccessorIndex;
    int currentPredecessorIndex;

}  Vertex;

typedef struct Graph
{
    hashTable* vertexTable; // mapping betweeen coordinate on x,y plane -> vertex (e.g. if on our x-y plane at coordinate 2,3 we have arbitrary_vertex, the value at key (2,3) will be arbitrary_vertex
    Vertex* vertexArray; // when was vertex inserted -> vertex, LIST OF ALL VERTECIES (e.g. if we say vertexArray[3] = arbitrary_vertext, this means arbitrary vertex was the 4th (i = 3) vertex to be inserted into the graph)
    int numVertices; // how many vertices do you currently have in the graph
    int capacity; // maximum vertices allowed in a graph

    /* weights of edges are stored in this matrix (-1 if edge isn't present) */ // EDGE IS THE LINE BETWEEN TWO ADJACENT VERTICES
    double** adjacencyMatrix; // matrix where the weight between the ith and jth adjacent vertices is stored (e.g. if adjacencyMatrix[2][3] = 5, there is a weight of 5 between vertex 2 and vertex 3)

    bool changed;           /* check for changes to know whether paths needs to be updated */
    int** pathsArray;       /* keep list of next vertex to visit on shortest path */
    double** distance;      /* shortest path distance between the pair of vertices, map of shortest i, j locations where i and j are indexes for the vertex */

} Graph;


Graph* createGraph( int numVertex );
void freeGraph( Graph* g );

void addVertex( Graph* g, graphType p );
bool isVertex( Graph* g, graphType p );
bool getVertexByIndex( Graph* g, int index, graphType* next );

void setEdge( Graph* g, graphType p1, graphType p2, double value );
double getEdge( Graph* g, graphType p1, graphType p2 );

bool getSuccessor( Graph* g, graphType start, graphType* pnext );
bool getPredecessor( Graph* g, graphType start, graphType* pprev );

void setVisited( Graph* g, graphType p, bool value );
bool getVisited( Graph* g, graphType p );

void setDistance( Graph* g, graphType from, graphType to, double dist );
double getDistance( Graph* g, graphType from, graphType to );

void dijkstrasAlg( Graph* g, graphType start );

#endif
