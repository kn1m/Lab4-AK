//
// Created by m3sc4 on 02.06.15.
//

#ifndef DIJKSTRA_ALGO_H
#define DIJKSTRA_ALGO_H

#include <vector>
#include <stdio.h>
#include <limits.h>

#define GraphSize 9

using namespace std;

class DijkstraAlgo
{
    public:

        int Graph[GraphSize][GraphSize];
        int vertex;


        DijkstraAlgo(vector<vector<int>> Graph, int vertex)
        {
            setup(Graph, (int)Graph.size(), (int)Graph.size());
            this->vertex = vertex;
        };


        void setup(vector<vector<int> > &vals, int N, int M)
        {
            for(int i=0; (i < GraphSize); i++)
            {
                for(int j=0; (j < GraphSize); j++)
                {
                    Graph[i][j] = vals[i][j];
                }
            }
        };

        int minDistance(int dist[], bool sptSet[])
        {
            // Initialize min value
            int min = INT_MAX, min_index;

            for (int v = 0; v < GraphSize; v++) {
                if (sptSet[v] == false && dist[v] <= min)
                    min = dist[v], min_index = v;
            }
            return min_index;
        };

        vector<int> Dijkstra(int graph[GraphSize][GraphSize], int src)
        {

            int dist[GraphSize];     // The output array.  dist[i] will hold the shortest
            // distance from src to i

            bool sptSet[GraphSize]; // sptSet[i] will true if vertex i is included in shortest
            // path tree or shortest distance from src to i is finalized

            // Initialize all distances as INFINITE and stpSet[] as false
            for (int i = 0; i < GraphSize; i++)
                dist[i] = INT_MAX, sptSet[i] = false;

            // Distance of source vertex from itself is always 0
            dist[src] = 0;

            // Find shortest path for all vertices
            for (int count = 0; count < GraphSize-1; count++)
            {
                // Pick the minimum distance vertex from the set of vertices not
                // yet processed. u is always equal to src in first iteration.
                int u = minDistance(dist, sptSet);

                // Mark the picked vertex as processed
                sptSet[u] = true;

                // Update dist value of the adjacent vertices of the picked vertex.
                for (int v = 0; v < GraphSize; v++)

                    // Update dist[v] only if is not in sptSet, there is an edge from
                    // u to v, and total weight of path from src to  v through u is
                    // smaller than current value of dist[v]
                    if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                        && dist[u]+graph[u][v] < dist[v])
                        dist[v] = dist[u] + graph[u][v];
            }


            vector<int> v(begin(dist), end(dist));
            // print the constructed distance array
            printSolution(dist);
            return v;

        };

        void printSolution(int dist[])
        {
            printf("Vertex   Distance from Source\n");
            for (int i = 0; i < GraphSize; i++)
                printf("%d \t\t %d\n", i, dist[i]);
        };
};

#endif
