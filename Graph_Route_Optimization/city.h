//This is the City class, containing all of the information necessary to create a city type object, and provides additional functionality for both graph.h, and the main driver. 
#ifndef CITY_H
#define CITY_H
#include <string>

class City {
public:
    City();
    City(const std::string& name);
    ~City();
    std::string getName() const;
    int getIndex() const;
    void setIndex(int newIndex);
    void markVisited();
    bool isVisited() const;
    bool operator<(const City& other) const;
private:
    std::string name;
    int index;   
    bool visited; 
};

#endif