/*
 * Project 3: J Cubed Flights
 * Team Name: J Cubed
 * Team Members: Jason Li, Jan Torruellas, Jack Wang
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "directedgraph.h"


using namespace std;

// Main driver function, prevents the main() function from accessing memory directly
void mainDriver() {
    // Initialize an empty DirectedGraph object
    DirectedGraph flights;
    parseData(flights, "../data/airports.csv", "../data/transport_data_2015_january.csv");
}


int main() {
    mainDriver();
    return 0;
}