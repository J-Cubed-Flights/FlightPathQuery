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
    //this is just for making a null airport (used to ensure the getAirport function doesn't cause an error
    Airport() : name(""), airportCode("") {}
    Airport(string &n, string &a) : name(n), airportCode(a) {}
    Airport(const Airport& a) : name(a.name), airportCode(a.airportCode), flights(a.flights) {}

    unordered_map<string, Flight>::iterator begin() {
        return flights.begin();
    }
    unordered_map<string, Flight>::iterator end() {
        return flights.end();
    }
    unordered_map<string, Flight>::iterator find(string& code) {
        return flights.find(code);
    }

    string getAirportName() const {return name;}
    string getAirportCode() const {return airportCode;}
    bool isNull() {return name.length() == 0;}

    void updateFlight(string &arriveCode, int flightTime) {
        auto it = flights.find(arriveCode);

        if (it != flights.end()) {
            it->second.addFlightTime(flightTime);
        } else {
            Flight newFlight(airportCode, arriveCode);
            newFlight.addFlightTime(flightTime);

            flights.emplace(arriveCode, newFlight);
        }
    }
    //operators
    bool operator == (const Airport& a) {
        return airportCode == a.airportCode;
    }
    bool operator != (const Airport& a) {
        return airportCode != a.airportCode;
    }
    bool operator <= (const Airport& a) {
        return airportCode <= a.airportCode;
    }
    bool operator >= (const Airport& a) {
        return airportCode >= a.airportCode;
    }
    bool operator < (const Airport& a) {
        return airportCode < a.airportCode;
    }
    bool operator > (const Airport& a) {
        return airportCode > a.airportCode;
    }
};


#endif //J_CUBED_FLIGHTS_AIRPORT_H
