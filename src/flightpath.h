// Header file for FlightPath Class

#ifndef J_CUBED_FLIGHTS_LAYOVERPATH_H
#define J_CUBED_FLIGHTS_LAYOVERPATH_H


#include "airport.h"
#include "flight.h"
#include "directedgraph.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>

using namespace std;


class FlightPath {
private:
    int flightTimeNoLayover;
    int flightTimeWithLayover;
    vector<Airport*> stops;
    const int layover = 120;

public:
    // constructors
    FlightPath() : flightTimeNoLayover(0), flightTimeWithLayover(0) {};
    FlightPath(const FlightPath& copy) : stops(copy.getStops()), flightTimeNoLayover(copy.getFlightTimeNoLayover()) {};

    // operator
    FlightPath& operator=(const FlightPath& other) {
        flightTimeNoLayover = other.flightTimeNoLayover;
        stops = other.stops;
        return *this;
    }
    // getters
    int getFlightTimeNoLayover() const {return flightTimeNoLayover;};
    int getFlightTimeWithLayover() const {return flightTimeWithLayover;}
    const vector<Airport*>& getStops() const {return stops;}  // return the vector of airports in the path

    // toString()
    string toString(bool withLayover);
    string toString(){return toString(true);}

    // adding airport to path
    void addToPath(Airport* stop);
    void addToPath(Airport& stop) {addToPath(&stop);}
};


// add an airport stop to the back of the path
void FlightPath::addToPath(Airport* stop)  {
    if (!stops.empty()) {
        string fromAirport = stops.back()->getAirportCode();
        string to = stop->getAirportCode();
        int flightTime = stop->find(fromAirport)->second.getAverageFlightTime();

        flightTimeNoLayover += flightTime;
        flightTimeWithLayover += flightTime;

        // if there are 2 or more airports already in the path, then layover penalty is necessary
        if (stops.size() >= 2) {
            flightTimeWithLayover += layover;
        }
    }
    stops.push_back(stop);
}

// return a flight path as a string
string FlightPath::toString(bool withLayover) {
    if (stops.size() == 0) {
        return "No flight path";
    }
    stringstream sstr;
    int n = stops.size() - 1;
    for (int i = 0 ; i <= n; i++) {
        sstr << stops[i]->getAirportCode();
        if (i < n) {
            sstr << " -> ";
        }
    }
    if (withLayover) {
        sstr << " (Average total time: " << getFlightTimeWithLayover() << " minutes)";
    } else {
        sstr << " (Average total time: " << getFlightTimeNoLayover() << " minutes)";
    }
    return sstr.str();
}


#endif //J_CUBED_FLIGHTS_LAYOVERPATH_H
