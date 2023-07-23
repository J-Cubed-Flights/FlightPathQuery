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
public:
    FlightPath() : totalFlightTime(0) {};
    FlightPath(FlightPath& copy) : stops(copy.getStops()), totalFlightTime(copy.getFlightTime()) {};
    FlightPath& operator=(const FlightPath& other) {
        totalFlightTime = other.totalFlightTime;
        stops = other.stops;
        return *this;
    }

    int getFlightTime();
    int getWithLayover();
    string toString(bool withLayover);
    string toString();
    void addToPath(Airport* stop);
    void addTime(int t);
    vector<Airport*> getStops();
};

vector<Airport*> FlightPath::getStops() {
    return stops;
}

void FlightPath::addTime(int t) {
    totalFlightTime += t;
}

void FlightPath::addToPath(Airport* stop)  {
    stops.push_back(stop);
}

int FlightPath::getFlightTime()
{
    totalFlightTime = 0;
    for(int i = 1; i < stops.size(); i++) {
        string s = stops[i]->getAirportCode();
        totalFlightTime += stops[i - 1]->find(s)->second.getAverageFlightTime();
    }
    return totalFlightTime;
}

int FlightPath::getWithLayover()
{
    if (totalFlightTime < 0 || stops.size() == 0) {//if there is no flight path, then return -1;
        return -1;
    }// Here we are calculating total time with layovers in mind.
    // Adding 2 hours aka 120 minutes per extra stop(excluding the origin and destination) to totalFlightTime.
    int totalWithLayover = getFlightTime();
    if(stops.size() > 2) {
        totalWithLayover += 120 * (stops.size() - 2);
    }
    return totalWithLayover;
}
string FlightPath::toString() {
    return toString(true);
}
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
