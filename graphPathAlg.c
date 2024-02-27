#include "graph.h"
#include "graphPathAlg.h"



/***** PRINT STUDENT NAME *****/

void printName() {                                                                                                                                // DONE

    printf("This solution was completed by:\n");
    printf("Matthew Beck (vax202)\n");
}



/***** BUILD GRAPH *****/

Graph* buildGraph(array2D* maze, bool isTunnelable) {                                                                              // DONE
    
    int i, j;
    
    Graph* g; // declare a Graph* type displayGraph
    
    g = createGraph(maze->length * maze->width); // takes capacity from maze and sets a new empty graph with a pointer to it, where graph displayGraph->capacity is the total num verticies

    if (isTunnelable == false) {    
    
      for (i = 0; i < maze->width; i++) {
      
        for (j = 0; j < maze->length; j++) {
        
          if (maze->array2D[i][j] != 'X') { // check if initial position is not X
            
            if (maze->array2D[i][j + 1] != 'X') { // if up not X, set edge to 1
            
              setEdge(g, createPoint(i, j), createPoint(i, j + 1), 1);
            }
            
            if (maze->array2D[i][j - 1] != 'X') { // if down not X, set edge to 1
            
              setEdge(g, createPoint(i, j), createPoint(i, j - 1), 1);
            }
            
            if (maze->array2D[i - 1][j] != 'X') { // if left not X, set edge to 1
            
              setEdge(g, createPoint(i, j), createPoint(i - 1, j), 1);
            }
            
            if (maze->array2D[i + 1][j] != 'X') { // if right not X, set edge to 1
            
              setEdge(g, createPoint(i, j), createPoint(i + 1, j), 1);
            }
          }
        }
      }
    }
    
    else { // if the maze allows for tunneling, then isTunnelable is true and proceed through entire maze array2D
    
      for (i = 0; i < maze->width; i++) {
      
        for (j = 0; j < maze->length; j++) {
          
          if (j + 1 < maze->length) { // check if in bounds
        
            if (maze->array2D[i][j + 1] == 'X') { // if up is or is not X, set to 1 or 0 for edge
            
              setEdge(g, createPoint(i, j), createPoint(i, j + 1), 1); 
            }
            
            else {
            
              setEdge(g,createPoint(i,j), createPoint(i, j + 1), 0);
            }
          }
            
          if (j - 1 >= 0) { // check if in bounds
            
            if (maze->array2D[i][j - 1] == 'X') { // if down is or is not X, set to 1 or 0 for edge
            
              setEdge(g, createPoint(i, j), createPoint(i, j - 1), 1);
            }
            
            else {
            
              setEdge(g,createPoint(i,j), createPoint(i, j - 1), 0);
            }
          }
            
          if (i + 1 < maze->width) { // check if in bounds
            
            if (maze->array2D[i + 1][j] == 'X') { // if left is or is not X, set to 1 or 0 for edge
            
              setEdge(g, createPoint(i, j), createPoint(i + 1, j), 1);
            }
            
            else {
            
              setEdge(g,createPoint(i, j), createPoint(i + 1, j), 0);
            }
          }
            
          if (i - 1 >= 0) { // check if in bounds
            
            if (maze->array2D[i - 1][j] == 'X') { // if right is or is not X, set to 1 or 0 for edge
            
              setEdge(g, createPoint(i, j), createPoint(i - 1, j), 1);
            }
            
            else {
            
              setEdge(g,createPoint(i,j), createPoint(i - 1, j), 0);
            }
          }
        }
      }
    }

    return g; /* TODO: Replace with your graph representing maze */ //4 return maze
}



/***** FIND IF THERE IS A POSSIBLE PATH *****/

pathResult hasPath(array2D *maze) {                                                                                                            // DONE
    
    int i, j, pathResult;
    
    Graph* g = buildGraph(maze, false);
    
    graphType s, f;
    
    for (i = 0; i < maze->width; i++) { // loop to find S and F
    
      for (j = 0; j < maze->length; j++) {
      
        if (maze->array2D[i][j] == 'S') { // if character is S, set S
        
          s = createPoint(i, j);
        }
        
        if (maze->array2D[i][j] == 'F') { // if character is F, set F
        
          f = createPoint(i, j);
        }
      }
    }
    
    dijkstrasAlg(g, s); // edits the 2D distance matrix in g
    
    pathResult = getDistance(g, s, f); // find a resultant path length
    
    if (pathResult == INT_MAX) { // if pathResult some ridiculously high number, path not possible
    
      return PATH_IMPOSSIBLE;
    }
    
    else {
    
      return PATH_FOUND;
    }
      
    freeGraph(g); // free memory
}



/***** FIND THE NEAREST F *****/

pathResult findNearestFinish(array2D *maze, int *spDist) {                                                                                        // DONE
    
    Graph* g = buildGraph(maze, false);
    
    if (hasPath(maze) == PATH_IMPOSSIBLE) {
    
      (*spDist) = INT_MAX;
    
      return PATH_IMPOSSIBLE;
    }
    
    else {
    
      int i, j;
      
      graphType s, f;
      
      for (i = 0; i < maze->width; i++) { // loop to find S and F
      
        for (j = 0; j < maze->length; j++) {
        
          if (maze->array2D[i][j] == 'S') {
          
            s = createPoint(i, j);
          }
          
          if (maze->array2D[i][j] == 'F') {
          
            f = createPoint(i, j);
          }
        }
      }
      
      dijkstrasAlg(g, s); // edits the 2D distance matrix in g
      
      for (i = 0; i < maze->width; i++) { // loop to find the shortest F path
      
        for (j = 0; j < maze->length; j++) {
        
          if (maze->array2D[i][j] == 'F') {
          
            if (getDistance(g, s, createPoint(i, j)) < getDistance(g, s, f)) { // if new F is shorter than old F, set new F
            
              f = createPoint(i, j);
            }
          }
        }
      }
    
      (*spDist) = getDistance(g, s, f); // return path length
      
      freeGraph(g); // free memory
    
      return PATH_FOUND;
    }
}



/***** FIND A POSSIBLE TUNNEL ROUTE *****/

pathResult findTunnelRoute(array2D *maze, int k) /* k is tunnel len */ {                                                                                                  // DONE
    
    int i, j;
    
    Graph* g = buildGraph(maze, true); // make a new graph under the parameters of 'isTunnelable = true'
    
    graphType s, f;
    
    for (i = 0; i < maze->width; i++) { // loop to find S and F (works)
    
      for (j = 0; j < maze->length; j++) {
      
        if (maze->array2D[i][j] == 'S') { // find S
        
          s = createPoint(i, j);
        }
        
        if (maze->array2D[i][j] == 'F') { // find F
        
          f = createPoint(i, j);
        }
      }
    }
    
    dijkstrasAlg(g, s);
    
    if (getDistance(g, s, f) <= k) { // if resultant path length is less than k, path viable
    
      freeGraph(g); // free memory
    
      return PATH_FOUND;
    }
    
    else {
    
      freeGraph(g); // free memory
    
      return PATH_IMPOSSIBLE;
    }
}
