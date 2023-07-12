//
// Created by Jan Torruellas on 7/7/2023.
//

#ifndef J_CUBED_FLIGHTS_LAYOVERPATH_H
#define J_CUBED_FLIGHTS_LAYOVERPATH_H
#include <vector>
#include <string>
#include <unordered_map>
#include "airport.h"
#include "flight.h"
using namespace std;

class LayoverPath
{
private:
    vector<Flight> stops;
    int totalFlightTime;
    int totalWithLayover;
public:
    LayoverPath() : totalFlightTime(0), totalWithLayover(0) {};
    int calculateFlightTime();
    int calculateWithLayover();
    void djikstraPath(unordered_map<string, Airport> airports, string origin, string destination);
};

int LayoverPath::calculateFlightTime()
{
    return totalFlightTime;
}

int LayoverPath::calculateWithLayover()
{
    // Here we are calculating total time with layovers in mind.
    // Adding 2 hours aka 120 minutes per stop to totalFlightTime.
    totalWithLayover = 120 * stops.size() + totalFlightTime;
    return totalWithLayover;
}

void LayoverPath::djikstraPath(unordered_map<string, Airport> airports, string originCode, string destinationCode)
{
    // This is intended to create the flight path from start to finish.
    // The data then can be used to calculate flight time.


    auto it = airports.begin();

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
    }

}
#endif //J_CUBED_FLIGHTS_LAYOVERPATH_H
