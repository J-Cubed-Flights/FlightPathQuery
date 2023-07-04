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
    void addFlight(string &airportFullName, string &departCode, string &arriveFullName, string &arriveCode, int flightTime) {
        auto it = airports.find(departCode);

        if (it != airports.end()) {
            it->second.updateFlight(arriveCode, flightTime);
        } else {
            Airport newAirport(airportFullName, departCode);
            newAirport.updateFlight(arriveCode, flightTime);

            airports.insert(make_pair(departCode, newAirport));
        }
        //create destination airport if it doesn't exist.
        //this will prevent later issues in case that airport never had outgoing flights.
        it = airports.find(arriveCode);
        if(it == airports.end()) {
            Airport newAirport(arriveFullName, arriveCode);
            airports.insert(make_pair(arriveCode, newAirport));
        }
    }
    vector<string> getAirportNames() {
        // TODO: return a sorted list of airport names in the following format: "[iata] - [airport name]"
        // I will complete this tomorrow - Jason (7/3/2023)
        vector<string> result;
        return result;
    }
};


#endif //J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
