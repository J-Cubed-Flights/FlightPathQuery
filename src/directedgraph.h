// Header file for DirectedGraph Class

#ifndef J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
#define J_CUBED_FLIGHTS_DIRECTEDGRAPH_H


#include "airport.h"

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;


class DirectedGraph {
private:
    unordered_map<string, Airport> airports; // string stores the Departure Airport's IATA Code (i.e. JFK)
public:
    // public function to add a flight into the unordered_map of airports
    void addFlight(string &airportFullName, string &departCode, string &arriveCode, int flightTime) {
        auto it = airports.find(departCode);

        if (it != airports.end()) {
            it->second.updateFlight(arriveCode, flightTime);
        } else {
            Airport newAirport(airportFullName, departCode);
            newAirport.updateFlight(arriveCode, flightTime);

            airports.insert(make_pair(departCode, newAirport));
        }
    }
};


#endif //J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
