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
#include <sstream>

#include "airport.h"
#include "flight.h"
#include "directedgraph.h"
using namespace std;

class FlightPath
{
private:
    int totalFlightTime;
    vector<Airport*> stops;
    const int layover = 120;
    //determine if totalFlightTime needs to be updated next time it is called
    bool update;
public:
    //constructors
    FlightPath() : totalFlightTime(0), update(false) {};
    FlightPath(FlightPath& copy) : stops(copy.getStops()), totalFlightTime(copy.getFlightTime()),update(copy.update) {};

    //operator
    FlightPath& operator=(const FlightPath& other) {
        totalFlightTime = other.totalFlightTime;
        stops = other.stops;
        return *this;
    }
    //getters
    int getFlightTime();
    int getWithLayover();
    vector<Airport*> getStops();

    //toString()
    string toString(bool withLayover);
    string toString(){return toString(true);}

    //adding airport to path
    void addToPath(Airport* stop);
    void addToPath(Airport& stop);
};

//return the vector of airports in the path
vector<Airport*> FlightPath::getStops() {
    return stops;
}
//add an airport stop to the back of the path
void FlightPath::addToPath(Airport* stop)  {
    stops.push_back(stop);
    update = true;
}
//add an airport stop to the back of the path
void FlightPath::addToPath(Airport& stop)  {
    stops.push_back(&stop);
    update = true;
}
//return the flight time
int FlightPath::getFlightTime()
{
    if (update) {
        totalFlightTime = 0;
        for (int i = 1; i < stops.size(); i++) {
            string s = stops[i]->getAirportCode();
            totalFlightTime += stops[i - 1]->find(s)->second.getAverageFlightTime();
        }
        update = false;
    }
    return totalFlightTime;
}
//return the flight time including layovers at each intermediate stop
int FlightPath::getWithLayover()
{
    //if there is no flight path, then return 0
    if (stops.size() == 0) {
        return 0;
    }
    // Here we are calculating total time with layovers in mind.
    // Adding 2 hours aka 120 minutes per extra stop(excluding the origin and destination) to totalFlightTime.
    int totalWithLayover = getFlightTime();
    if(stops.size() > 2) {
        totalWithLayover += layover * (stops.size() - 2);
    }
    return totalWithLayover;
}

//return a flight path as a string
string FlightPath::toString(bool withLayover) {
    if(stops.size() == 0) {
        return "No flight path";
    }
    stringstream sstr;
    int n = stops.size() - 1;
    for(int i = 0 ; i <= n; i++) {
        sstr << stops[i]->getAirportCode();
        if(i < n) {
            sstr << " -> ";
        }
    }
    if(withLayover) {
        sstr << " (Average total time: " << getWithLayover() << " minutes)";
    } else {
        sstr << " (Average total time: " << totalFlightTime << " minutes)";
    }
    return sstr.str();
}


#endif //J_CUBED_FLIGHTS_LAYOVERPATH_H
