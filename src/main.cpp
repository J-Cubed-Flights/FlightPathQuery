/*
 * Project 3: J Cubed Flights
 * Team Name: J Cubed
 * Team Members: Jason Li, Jan Torruellas, Jack Wang
 */
#include <iostream>
#include <chrono>
#include "directedgraph.h"


using namespace std;

// Main driver function, prevents the main() function from accessing memory directly
void mainDriver() {
    // Initialize an empty DirectedGraph object
    DirectedGraph flights;
    parseData(flights, "../data/airports.csv", "../data/transport_data_2015_january.csv");

    //useful timer
    chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
//    for listing all the airports
//    vector<string> names = flights.getAirportNames();
//    for(string s : names) {
//        cout << s << endl;
//    }

//    For testing the path finding with Djikstra's algorithm:
//    string from = "ABE";
//    string to = "ATL";
//    FlightPath result = flights.djikstraPath(from, to);
//    cout << result.toString(true) << " " << result.getStops().size();

//  For testing path finding with Floyd Warshall Algorithm:
//  Note: The first time it is called, it takes ~97 seconds to run,
//  then it takes less than 0.01 ms to run each call after that.
//    start = std::chrono::system_clock::now();
//    string from = "ABE";
//    string to = "ATL";
//    FlightPath result = flights.floydPath(from, to);
//    end = std::chrono::system_clock::now();
//    elapsed_seconds = end - start;
//    cout << result.toString(true) << endl;
//    cout << "completed in " << elapsed_seconds.count() << "s\n";
//
//    start = std::chrono::system_clock::now();
//    from = "SLC";
//    to = "GNV";
//    result = flights.floydPath(from, to);
//    end = std::chrono::system_clock::now();
//    elapsed_seconds = end - start;
//    cout << result.toString(true) << endl;
//    cout << "completed in " << elapsed_seconds.count() << "s\n";

//    For testing to make sure the airports actually have flights in them.
//    flights.getAirport(from).printFlights();
}


int main() {
    mainDriver();
    return 0;
}