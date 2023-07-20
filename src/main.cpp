/*
 * Project 3: J Cubed Flights
 * Team Name: J Cubed
 * Team Members: Jason Li, Jan Torruellas, Jack Wang
 */
#include <iostream>
#include "directedgraph.h"


using namespace std;

// Main driver function, prevents the main() function from accessing memory directly
void mainDriver() {
    // Initialize an empty DirectedGraph object
    DirectedGraph flights;
    parseData(flights, "../data/airports.csv", "../data/transport_data_2015_january.csv");

//    for listing all the airports
//    vector<string> names = flights.getAirportNames();
//    for(string s : names) {
//        cout << s << endl;
//    }

//    For testing the path finding:
//    string from = "ABC";
//    string to = "ABC";
//    FlightPath result = flights.djikstraPath(flights, from, to);
//    cout << result.toString(true);
}


int main() {
    mainDriver();
    return 0;
}