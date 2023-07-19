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
    int totalWithLayover;
    vector<Airport*> stops;
public:
    FlightPath() : totalFlightTime(0), totalWithLayover(0) {};
    FlightPath(FlightPath& copy) : stops(copy.getStops()), totalFlightTime(copy.getFlightTime()), totalWithLayover(copy.getWithLayover()){};
    int getFlightTime();
    int getWithLayover();
    string toString(bool withLayover);
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
    return totalFlightTime;
}

int FlightPath::getWithLayover()
{
    if (totalFlightTime < 0 || stops.size() == 0) {//if there is no flight path, then return -1;
        return -1;
    }// Here we are calculating total time with layovers in mind.
    // Adding 2 hours aka 120 minutes per extra stop(excluding the origin and destination) to totalFlightTime.
    if(stops.size() > 2) {
        totalWithLayover = 120 * (stops.size() - 2) + totalFlightTime;
    }
    return totalWithLayover;
}

string FlightPath::toString(bool withLayover) {
    stringstream sstr;
    int n = stops.size() - 1;
    for(int i = 0 ; i <= n; i++) {
        sstr << stops[i]->getAirportCode();
        if(i < n) {
            sstr << " <- ";
        }
    }
    if(withLayover) {
        sstr << " (Average total time: " << getWithLayover() << " minutes)";
    } else {
        sstr << " (Average total time: " << getWithLayover() << " minutes)";
    }
    return sstr.str();
}


#endif //J_CUBED_FLIGHTS_LAYOVERPATH_H
