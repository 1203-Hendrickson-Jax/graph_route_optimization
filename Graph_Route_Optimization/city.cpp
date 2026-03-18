//This is the city source file, which implements the city header file. 
#include "city.h"

City::City() : visited(false), index(-1) {}

City::City(const std::string& cityName) : name(cityName), visited(false), index(-1) {}

City::~City() {}

std::string City::getName() const {
    return name;
}

int City::getIndex() const {
    return index;
}

void City::setIndex(int newIndex) {
    index = newIndex;
}

void City::markVisited() {
    visited = true;
}

bool City::isVisited() const {
    return visited;
}

bool City::operator<(const City& other) const {
    return name < other.name;
}