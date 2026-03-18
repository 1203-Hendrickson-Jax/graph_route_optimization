//This is the graph class, which implements the graph interface, and provides additional functionality for the program to run. 
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <set>
#include "graphinterface.h"
#include "city.h"

class Graph : public GraphInterface<City> {
public:
    static const int MAX_VERTICES = 5;
    City cities[MAX_VERTICES];
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    Graph();
    virtual ~Graph();
    int getNumVertices() const override;
    int getNumEdges() const override;
    bool add(City start, City end, int edgeWeight) override;
    bool remove(City start, City end) override;
    int getEdgeWeight(City start, City end) const override;
    void depthFirstTraversal(City start, void visit(City&)) override;
    void depthFirstTraversalHelper(int vertexIndex, std::set<int>& visited, void visit(City&));
    void breadthFirstTraversal(City start, void visit(City&)) override;
    void printAllPaths(City allPaths[MAX_VERTICES][MAX_VERTICES], City currentPath[MAX_VERTICES], City start, std::set<City>& visited);
    void printAllPathsHelper(City allPaths[MAX_VERTICES][MAX_VERTICES], City currentPath[MAX_VERTICES], City current, std::set<City>& visited);
    void findOptimalPath(City optimalPath[MAX_VERTICES]);
    void findOptimalPathHelper(City optimalPath[MAX_VERTICES], City currentPath[MAX_VERTICES], City currentCity);
    int calculatePathCost(const City path[MAX_VERTICES]) const;
    void loadCityData(const std::string& filename);
    void printResults(City allPaths[MAX_VERTICES][MAX_VERTICES], City bestPath[MAX_VERTICES]) const;
    void printPath(const City path[MAX_VERTICES], std::ostream& output) const;
    const City* getCities() const;
};
#endif