// Header file for Airport Class

#ifndef J_CUBED_FLIGHTS_AIRPORT_H
#define J_CUBED_FLIGHTS_AIRPORT_H


#include "flight.h"

#include <string>
#include <unordered_map>
#include <utility>

using namespace std;


class Airport {
private:
    string name; // full name of airport, may not be needed later on
    string airportCode; // 3-letter IATA Code (i.e. JFK)
    unordered_map<string, Flight> flights; // string stores the Arrival Airport's IATA Code (i.e. JFK)
public:
    Airport(string &n, string &a) {
        name = std::move(n);
        airportCode = std::move(a);
    }

    string getAirportName() const {return name;}
    string getAirportCode() const {return airportCode;}

    void updateFlight(string &arriveCode, int flightTime) {
        auto it = flights.find(arriveCode);

        if (it != flights.end()) {
            it->second.addFlightTime(flightTime);
        } else {
            Flight newFlight(airportCode, arriveCode);
            newFlight.addFlightTime(flightTime);

            flights.insert(make_pair(arriveCode, newFlight));
        }
    }
};


#endif //J_CUBED_FLIGHTS_AIRPORT_H
