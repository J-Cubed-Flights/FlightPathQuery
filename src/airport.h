// Header file for Airport Class

#ifndef J_CUBED_FLIGHTS_AIRPORT_H
#define J_CUBED_FLIGHTS_AIRPORT_H


#include "flight.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <sstream>

using namespace std;


class Airport {
private:
    string name;  // full name of airport, may not be needed later on
    string airportCode;  // 3-letter IATA Code (i.e. JFK)
    unordered_map<string, Flight> flights;  // string stores the Arrival Airport's IATA Code (i.e. JFK)
    int id;  // value used for storing index in sorted vector of airports for quick access.
public:
    // this is just for making a null airport (used to ensure the getAirport function doesn't cause an error
    Airport() : name(""), airportCode(""), id(0) {}
    Airport(string &n, string &a) : name(n), airportCode(a),id(0) {}
    Airport(const Airport& a) : name(a.name), airportCode(a.airportCode), flights(a.flights),id(a.id) {}

    // functions for accessing the flights map easier
    unordered_map<string, Flight>::iterator begin() {return flights.begin();}
    unordered_map<string, Flight>::iterator end() {return flights.end();}
    unordered_map<string, Flight>::iterator find(string& code) {return flights.find(code);}
    unordered_map<string, Flight>::iterator find(const string& code) {return flights.find(code);}
    Flight& operator[](string code){return flights[code];}

    // getter functions
    string getAirportName() const {return name;}
    string getAirportCode() const {return airportCode;}
    int getID() {return id;};
    bool isNull() {return name.length() == 0;}

    // setter
    void setID(int id) {this->id = id;}

    // update Flight
    void updateFlight(string &arriveCode, int flightTime);

    // operators
    bool operator == (const Airport& a) {return airportCode == a.airportCode;}
    bool operator != (const Airport& a) {return airportCode != a.airportCode;}
    bool operator <= (const Airport& a) {return airportCode <= a.airportCode;}
    bool operator >= (const Airport& a) {return airportCode >= a.airportCode;}
    bool operator < (const Airport& a) {return airportCode < a.airportCode;}
    bool operator > (const Airport& a) {return airportCode > a.airportCode;}


    // for testing purposes
    vector<string> printFlights();
};

// print all outgoing flights
vector<string> Airport::printFlights() {
    vector<string> ss;
    for (auto it : flights) {
        ss.push_back(it.second.getArrival() + " " + to_string(it.second.getAverageFlightTime()));
    }
    return ss;
}
// update a flight
void Airport::updateFlight(string &arriveCode, int flightTime) {
    auto it = flights.find(arriveCode);
    if (it != flights.end()) {
        // if flight exists, add flight time
        it->second.addFlightTime(flightTime);
    } else {
        // if flight doesn't exist, create flight, then add flight time.
        Flight newFlight(airportCode, arriveCode);
        newFlight.addFlightTime(flightTime);
        // add to flights map
        flights.emplace(arriveCode, newFlight);
    }
}

#endif //J_CUBED_FLIGHTS_AIRPORT_H
