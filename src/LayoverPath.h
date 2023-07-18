//
// Created by Jan Torruellas on 7/7/2023.
//

#ifndef J_CUBED_FLIGHTS_LAYOVERPATH_H
#define J_CUBED_FLIGHTS_LAYOVERPATH_H
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "airport.h"
#include "flight.h"
#include "directedgraph.h"
using namespace std;

class LayoverPath
{
private:
    vector<Flight> stops;
    int totalFlightTime;
    int totalWithLayover;
    //the matrix below will be built the first time that the floydPath function.
    //this optimized the time needed to make the map after the first time it is called.
    unordered_map<string, unordered_map<string, int>> floydMap;
    void generateMap();
public:
    LayoverPath() : totalFlightTime(0), totalWithLayover(0) {};
    int calculateFlightTime();
    int calculateWithLayover();
    void djikstraPath(DirectedGraph &graph, string &origin, string &destination);
    void floydPath(DirectedGraph &graph, string &origin, string &destination);
};

int LayoverPath::calculateFlightTime()
{
    return totalFlightTime;
}

int LayoverPath::calculateWithLayover()
{
    if (totalFlightTime < 0) {//if there is no flight path, then return -1;
        return -1;
    }// Here we are calculating total time with layovers in mind.
    // Adding 2 hours aka 120 minutes per extra stop(excluding the origin and destination) to totalFlightTime.
    totalWithLayover = 120 * (stops.size() - 2) + totalFlightTime;
    return totalWithLayover;
}

void LayoverPath::djikstraPath(DirectedGraph &airports, string &originCode, string &destinationCode)
{
    // This is intended to create the flight path from start to finish.
    // The data then can be used to calculate flight time.

    //make sure that both the origin and destination are valid
    if(airports.validCode(originCode) || airports.validCode(destinationCode)) {
        totalFlightTime = -1;
        return;
    }

    //this keeps track of the predecessor node/airport.
    //this will be used to build the final path.
    unordered_map<string, string> previous;
    //set to keep track of airports that have already been visited.
    unordered_set<string> visited;
    //we will start at
    visited.emplace(originCode);

    //use a priority queue to determine which airport to start at...
    //make sure to add origin


    /*** TODO: complete djikstra's algorithm
    // This is assuming the graph has already been sorted
    while(it->first == originCode)
    {
        // Check for direct flight.
        if(it->second.getAirportCode() == destinationCode)
            return;
        else
        {
            int shortestFlightTime = 0;
            // Here Ideally we begin with the shortest connected flight
            for(auto flightIt = it->second.flights.begin(); flightIt != it->second.flights.end(); flightIt++)
            {
                // Search through available flights to find the shortest flight.
                if(flightIt == it->second.flights.begin())
                    shortestFlightTime = flightIt->second.getAverageFlightTime();
                else
                {
                    if(flightIt->second.getAverageFlightTime() < shortestFlightTime)
                    {
                        Flight shortest = flightIt->second;
                        shortestFlightTime = flightIt->second.getAverageFlightTime();
                    }
                }
            }
            // Possibly implement a new function to check if flight connects to destination
        }
        it++;
    } ***/
}
//generates the floyd warshall  map if it is the first time.
void LayoverPath::generateMap() {
    //TODO
}
//generate path using floyd warshall algorithm
void LayoverPath::floydPath(DirectedGraph &graph, std::string &origin, std::string &destination) {
    //TODO
    if(floydMap.size() == 0) {//if the floydMap was never made, generate it first.
        generateMap();
    }
}
#endif //J_CUBED_FLIGHTS_LAYOVERPATH_H
