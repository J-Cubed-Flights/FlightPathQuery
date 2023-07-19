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

class FlightPath
{
private:
    int totalFlightTime;
    int totalWithLayover;
public:
    vector<Flight> stops;
    FlightPath() : totalFlightTime(0), totalWithLayover(0) {};
    FlightPath(FlightPath& copy) : stops(copy.stops), totalFlightTime(copy.getFlightTime()), totalWithLayover(copy.getWithLayover()){};
    int getFlightTime();
    int getWithLayover();
};

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


#endif //J_CUBED_FLIGHTS_LAYOVERPATH_H
