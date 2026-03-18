travelingsalesman: main.o graph.o city.o
	g++ -o travelingsalesman main.o graph.o city.o
main.o: main.cpp graph.h city.h
	g++ -c main.cpp
graph.o: graph.cpp graph.h city.h
	g++ -c graph.cpp
city.o: city.cpp city.h
	g++ -c city.cpp
clean: 
	rm travelingsalesman *.o 