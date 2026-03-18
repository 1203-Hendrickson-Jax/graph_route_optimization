//This is the graph source file, which implements the graph header file.
#include "graph.h"
#include <iostream>
#include <fstream>
#include <queue>

Graph::Graph() {}

Graph::~Graph() {}

int Graph::getNumVertices() const {
    return MAX_VERTICES;
}

int Graph::getNumEdges() const {
    int numEdges = 0;
    for (int i = 0; i < MAX_VERTICES; ++i) {
        for (int j = 0; j < MAX_VERTICES; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                numEdges++;
            }
        }
    }
    return numEdges / 2;  
}

bool Graph::add(City start, City end, int edgeWeight) {
    if (start.getName().empty() || end.getName().empty()) {
        std::cerr << "Error: Invalid city names.\n";
        return false;
    }
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (cities[i].getName() == start.getName()) {
            startIndex = i;
        }
        if (cities[i].getName() == end.getName()) {
            endIndex = i;
        }
    }
    if (startIndex == -1 || endIndex == -1) {
        std::cerr << "Error: City not found.\n";
        return false;
    }
    if (adjacencyMatrix[startIndex][endIndex] != 0 || adjacencyMatrix[endIndex][startIndex] != 0) {
        std::cerr << "Error: Edge already exists.\n";
        return false;
    }
    adjacencyMatrix[startIndex][endIndex] = edgeWeight;
    adjacencyMatrix[endIndex][startIndex] = edgeWeight;
    return true;
}

bool Graph::remove(City start, City end) {
    if (start.getName().empty() || end.getName().empty()) {
        std::cerr << "Error: Invalid city names.\n";
        return false;
    }
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (cities[i].getName() == start.getName()) {
            startIndex = i;
        }
        if (cities[i].getName() == end.getName()) {
            endIndex = i;
        }
    }
    if (startIndex == -1 || endIndex == -1) {
        std::cerr << "Error: City not found.\n";
        return false;
    }
    if (adjacencyMatrix[startIndex][endIndex] == 0 || adjacencyMatrix[endIndex][startIndex] == 0) {
        std::cerr << "Error: Edge does not exist.\n";
        return false;
    }
    adjacencyMatrix[startIndex][endIndex] = 0;
    adjacencyMatrix[endIndex][startIndex] = 0;
    return true;
}

int Graph::getEdgeWeight(City start, City end) const {
    if (start.getName().empty() || end.getName().empty()) {
        std::cerr << "Error: Invalid city names.\n";
        return 0; 
    }
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (cities[i].getName() == start.getName()) {
            startIndex = i;
        }
        if (cities[i].getName() == end.getName()) {
            endIndex = i;
        }
    }
    if (startIndex == -1 || endIndex == -1) {
        std::cerr << "Error: City not found.\n";
        return 0; 
    }
    return adjacencyMatrix[startIndex][endIndex];
}

void Graph::depthFirstTraversal(City start, void visit(City&)) {
    if (start.getName().empty()) {
        std::cerr << "Error: Invalid city name.\n";
        return;
    }
    int startIndex = -1;
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (cities[i].getName() == start.getName()) {
            startIndex = i;
            break;
        }
    }
    if (startIndex == -1) {
        std::cerr << "Error: City not found.\n";
        return;
    }
    std::set<int> visitedVertices;
    depthFirstTraversalHelper(startIndex, visitedVertices, visit);
}

void Graph::depthFirstTraversalHelper(int vertexIndex, std::set<int>& visited, void visit(City&)) {
    visited.insert(vertexIndex);
    visit(cities[vertexIndex]);
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (adjacencyMatrix[vertexIndex][i] != 0 && visited.find(i) == visited.end()) {
            depthFirstTraversalHelper(i, visited, visit);
        }
    }
}

void Graph::breadthFirstTraversal(City start, void visit(City&)) {
    if (start.getName().empty()) {
        std::cerr << "Error: Invalid city name.\n";
        return;
    }
    int startIndex = -1;
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (cities[i].getName() == start.getName()) {
            startIndex = i;
            break;
        }
    }
    if (startIndex == -1) {
        std::cerr << "Error: City not found.\n";
        return;
    }
    std::set<int> visitedVertices;
    std::queue<int> queue;
    queue.push(startIndex);
    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        if (visitedVertices.find(currentVertex) == visitedVertices.end()) {
            visitedVertices.insert(currentVertex);
            visit(cities[currentVertex]);
            for (int i = 0; i < MAX_VERTICES; ++i) {
                if (adjacencyMatrix[currentVertex][i] != 0 && visitedVertices.find(i) == visitedVertices.end()) {
                    queue.push(i);
                }
            }
        }
    }
}

void Graph::printAllPaths(City allPaths[MAX_VERTICES][MAX_VERTICES], City currentPath[MAX_VERTICES], City start, std::set<City>& visited) {
    currentPath[0] = start;
    visited.insert(start);
    printAllPathsHelper(allPaths, currentPath, start, visited);
    visited.erase(start);
}

void Graph::printAllPathsHelper(City allPaths[MAX_VERTICES][MAX_VERTICES], City currentPath[MAX_VERTICES], City current, std::set<City>& visited) {
    if (visited.find(current) != visited.end()) {
        return;
    }
    if (currentPath[MAX_VERTICES - 1].getIndex() != -1) {
        for (int i = 0; i < MAX_VERTICES; ++i) {
            allPaths[i][i] = currentPath[i];
        }
        return;
    }
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (adjacencyMatrix[current.getIndex()][i] != 0 && visited.find(cities[i]) == visited.end()){
            currentPath[MAX_VERTICES - 1] = cities[i];
            visited.insert(cities[i]);
            printAllPathsHelper(allPaths, currentPath, cities[i], visited);
            currentPath[MAX_VERTICES - 1].setIndex(-1);
            visited.erase(cities[i]);
        }
    }
}

void Graph::findOptimalPath(City optimalPath[MAX_VERTICES]) {
    City currentPath[MAX_VERTICES];
    currentPath[0] = cities[0];
    currentPath[MAX_VERTICES - 1].setIndex(-1);  
    cities[0].markVisited();
    findOptimalPathHelper(optimalPath, currentPath, cities[0]);
    cities[0].markVisited();
}

void Graph::findOptimalPathHelper(City optimalPath[MAX_VERTICES], City currentPath[MAX_VERTICES], City currentCity) {
    if (currentPath[MAX_VERTICES - 1].getIndex() != -1) {
        int currentPathCost = calculatePathCost(currentPath);
        int optimalPathCost = calculatePathCost(optimalPath);
        if (optimalPath[0].getIndex() == -1 || currentPathCost < optimalPathCost) {
            for (int i = 0; i < MAX_VERTICES; ++i) {
                optimalPath[i] = currentPath[i];
            }
        }
        return;
    }
    for (int i = 0; i < MAX_VERTICES; ++i) {
        if (!cities[i].isVisited()) {
            cities[i].markVisited();
            currentPath[MAX_VERTICES - 1] = cities[i];
            findOptimalPathHelper(optimalPath, currentPath, cities[i]);
            cities[i].markVisited();
            currentPath[MAX_VERTICES - 1].setIndex(-1);
        }
    }
}

int Graph::calculatePathCost(const City path[MAX_VERTICES]) const {
    int cost = 0;
    for (int i = 0; i < MAX_VERTICES - 1; ++i) {
        cost += getEdgeWeight(path[i], path[i + 1]);
    }
    cost += getEdgeWeight(path[MAX_VERTICES - 1], path[0]);
    return cost;
}

void Graph::loadCityData(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return;
    }
    int numCities = static_cast<int>(MAX_VERTICES);
    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            int distance;
            inputFile >> distance;
            if (i != j) {
                add(cities[i], cities[j], distance);
            }
        }
    }
    inputFile.close();
}

void Graph::printResults(City allPaths[MAX_VERTICES][MAX_VERTICES], City bestPath[MAX_VERTICES]) const {
    std::ofstream outputFile("results.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing results\n";
        return;
    }
    outputFile << "All possible paths:\n";
    printPath(allPaths[0], outputFile);  
    outputFile << "\nBest path:\n";
    printPath(bestPath, outputFile);
    int bestPathCost = calculatePathCost(bestPath);
    outputFile << "\nCost of the best path: " << bestPathCost << " miles\n";
    outputFile.close();
}

void Graph::printPath(const City path[MAX_VERTICES], std::ostream& output) const {
    for (int i = 0; i < MAX_VERTICES; ++i) {
        output << path[i].getName() << " -> ";
    }
    output << path[0].getName() << "\n"; 
}

const City* Graph::getCities() const {
    return cities;
}