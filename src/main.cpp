/*
 * Project 3: J Cubed Flights
 * Team Name: J Cubed
 * Team Members: Jason Li, Jan Torruellas, Jack Wang
 */

#include "directedgraph.h"

#include <iostream>
#include <chrono>

using namespace std;


// Main driver function, prevents the main() function from accessing memory directly
void mainDriver();
// Pathfinding test functions for both Dijkstra's algorithm and Floyd Warshall's algorithm
void testFloydPath(string from, string to, DirectedGraph flights);
void testDijkstraMinHeap(string from, string to, DirectedGraph flights);
void testDijkstraVector(string from, string to, DirectedGraph flights);

int main() {
    mainDriver();
    return 0;
}

// Main driver function, prevents the main() function from accessing memory directly
void mainDriver() {
    // useful timer
    auto start = chrono::system_clock::now();

    // Initialize an empty DirectedGraph object
    DirectedGraph flightGraph;

    // Possible file paths for data, add more possibilities as needed
    initializer_list<pair<string, string>> possibleFilePaths = {
        {"data/airports.csv", "data/transport_data_2015_january.csv"},
        {"../data/airports.csv", "../data/transport_data_2015_january.csv"},
        {"../../data/airports.csv", "../../data/transport_data_2015_january.csv"}
    };

    // Try different data file path possibilities until successfully parsed
    for (const auto& possiblePath : possibleFilePaths) {
        flightGraph.parseData(possiblePath.first, possiblePath.second);
        if (flightGraph.size() != 0) {
            break; // successfully parsed
        }
    }

    auto elapsed_seconds = chrono::system_clock::now() - start;
    cout << "Parsing completed in: " << elapsed_seconds.count() << "seconds\n";

    // for listing all the airports
    vector<string> names = flightGraph.getAirportNames();
    for (string s : names) {
        cout << s << endl;
    }
    cout << "size: " << flightGraph.size() << endl;

    string testFromAirport = "ABE";
    string testToAirport = "ABE";

    testFloydPath(testFromAirport, testToAirport, flightGraph);
    testDijkstraMinHeap(testFromAirport, testToAirport, flightGraph);
    testDijkstraVector(testFromAirport, testToAirport, flightGraph);
}

void testFloydPath(string from, string to, DirectedGraph flights) {
    auto start = chrono::system_clock::now();
    FlightPath result = flights.floydPath(from, to);
    auto elapsed_seconds = chrono::system_clock::now() - start;

    cout << "Floyd Path: " << result.toString() << endl;
    cout << "\tcompleted in " << elapsed_seconds.count() << "s\n";
}

void testDijkstraMinHeap(string from, string to, DirectedGraph flights) {
    auto start = std::chrono::system_clock::now();
    FlightPath result = flights.djikstraMinHeapPath(from, to);
    auto elapsed_seconds = chrono::system_clock::now() - start;

    cout << "Dijkstra Path MinHeap: " << result.toString() << endl;
    cout << "\tcompleted in " << elapsed_seconds.count() << "s\n\n";
}

void testDijkstraVector(string from, string to, DirectedGraph flights) {
    auto start = std::chrono::system_clock::now();
    FlightPath result = flights.djikstraVectorPath(from, to);
    auto elapsed_seconds = std::chrono::system_clock::now() - start;
    cout << "Dijkstra Path Vector: " << result.toString(true) << endl;
    cout << "\tcompleted in " << elapsed_seconds.count() << "s\n\n";
}
