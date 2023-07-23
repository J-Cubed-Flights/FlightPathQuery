// Header file for Airport Class

#ifndef J_CUBED_FLIGHTS_AIRPORT_H
#define J_CUBED_FLIGHTS_AIRPORT_H


#include "flight.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <mutex>

using namespace std;


class Airport {
private:
    string name; // full name of airport, may not be needed later on
    string airportCode; // 3-letter IATA Code (i.e. JFK)
    unordered_map<string, Flight> flights; // string stores the Arrival Airport's IATA Code (i.e. JFK)
    int id;
public:
    //this is just for making a null airport (used to ensure the getAirport function doesn't cause an error
    Airport() : name(""), airportCode(""), id(0) {}
    Airport(string &n, string &a, int id = 0) : name(n), airportCode(a), id(id) {}
    Airport(const Airport& a) : name(a.name), airportCode(a.airportCode), flights(a.flights), id(a.id) {}

    //getters
    string getAirportName() const {return name;}
    string getAirportCode() const {return airportCode;}
    int getID() {return id;}
    bool isNull() {return name.length() == 0;}

    //setter
    void setID(int val){id = val;}


    //operators
    bool operator == (const Airport& a) {return airportCode == a.airportCode;}
    bool operator != (const Airport& a) {return airportCode != a.airportCode;}
    bool operator <= (const Airport& a) {return airportCode <= a.airportCode;}
    bool operator >= (const Airport& a) {return airportCode >= a.airportCode;}
    bool operator < (const Airport& a) {return airportCode < a.airportCode;}
    bool operator > (const Airport& a) {return airportCode > a.airportCode;}

    //Iterator Functions
    unordered_map<string, Flight>::iterator begin() {return flights.begin();}
    unordered_map<string, Flight>::iterator end() {return flights.end();}
    unordered_map<string, Flight>::iterator find(string& code) {return flights.find(code);}

    //for testing purposes
    string printFlights();

    //update flight function
    void updateFlight(string &arriveCode, int flightTime);
};
//print all outgoing flights
string Airport::printFlights() {
    stringstream ss;
    for(auto it : flights) {
        ss << it.second.getArrival() << " " << it.second.getAverageFlightTime() << "\n";
    }
    return ss.str();
}
//update a flight
void Airport::updateFlight(string &arriveCode, int flightTime) {
    auto it = flights.find(arriveCode);

    if (it != flights.end()) {
        //if flight does exist add a flight to existing flight.
        it->second.addFlightTime(flightTime);
    } else {
        //if the flight doesn't exist, create a new one.
        Flight newFlight(airportCode, arriveCode);
        newFlight.addFlightTime(flightTime);

        flights.emplace(arriveCode, newFlight);
    }
}

#endif //J_CUBED_FLIGHTS_AIRPORT_H
