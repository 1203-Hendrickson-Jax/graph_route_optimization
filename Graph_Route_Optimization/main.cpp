//Author: Jax Hendrickson
//Purpose: To create all possible paths between 5 cities using graphs, and to find which path is the most cost-efficient out of the bunch. 
#include "graph.h"

int main() {
    Graph graph;
    graph.loadCityData("input.txt");
    City allPaths[Graph::MAX_VERTICES][Graph::MAX_VERTICES];
    City bestPath[Graph::MAX_VERTICES];
    std::set<City> visited;
    graph.printAllPaths(allPaths, bestPath, graph.getCities()[0], visited);
    graph.findOptimalPath(bestPath);
    graph.printResults(allPaths, bestPath);
    return 0;
}
