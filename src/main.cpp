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
    //useful timer
    chrono::time_point<std::chrono::system_clock> start;
    std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();


    // Initialize an empty DirectedGraph object
    DirectedGraph flights;
    flights.parseData("../data/airports.csv", "../data/transport_data_2015_january.csv");
    elapsed_seconds = std::chrono::system_clock::now() - start;
    cout << "parsing completed in " << elapsed_seconds.count() << "s\n";
    //cout << "parsing complete" << endl;
    //for listing all the airports
//    vector<string> names = flights.getAirportNames();
//    for(string s : names) {
//        cout << s << endl;
//    }
//    cout << "size:" << names.size() << endl;

    //For testing the path finding with Djikstra's algorithm:
//    start = std::chrono::system_clock::now();
//    string from = "SLC";
//    string to = "GNV";
//    FlightPath result = flights.djikstraPath(from, to);
//    end = std::chrono::system_clock::now();
//    elapsed_seconds = end - start;
//    cout << result.toString(true) << endl;
//    cout << "completed in " << elapsed_seconds.count() << "s\n";

//  For testing path finding with Floyd Warshall Algorithm:
// ----------------------- Completed------------------------
//    start = std::chrono::system_clock::now();
//    string from = "ABE";
//    string to = "ATL";
//    FlightPath result = flights.floydPath(from, to);
//    elapsed_seconds = std::chrono::system_clock::now() - start;
//    cout << result.toString(true) << endl;
//    cout << "completed in " << elapsed_seconds.count() << "s\n";
//
//    start = std::chrono::system_clock::now();
//    from = "SLC";
//    to = "GNV";
//    result = flights.floydPath(from, to);
//    elapsed_seconds = std::chrono::system_clock::now() - start;
//    cout << result.toString(true) << endl;
//    cout << "completed in " << elapsed_seconds.count() << "s\n";

//    For testing to make sure the airports actually have flights in them.
//    flights.getAirport(from).printFlights();

//    cout << "max threads is: " << thread::hardware_concurrency() << endl;
}


int main() {
    mainDriver();
    return 0;
}