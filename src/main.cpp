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

//parse the data and insert into the flights graph.
void parseData(DirectedGraph& flights, string airportFile, string flightFile) {
    //first, get all the airport iata values.
    unordered_map<string, string> airportNames;
    fstream file (airportFile);
    if(file.is_open())
    {
        //skip the first line, since it is the column names.
        string line;
        getline(file, line);
        //while the lines exist
        while(getline(file, line))
        {
            stringstream str(line);
            //just need the first two values: the IATA & Airport name
            string iata, airport;
            getline(str, iata, ',');
            getline(str, airport, ',');
            //now insert into the map.
            airportNames.emplace(iata, airport);
        }
        file.close();
    } else {
        return;
    }
    //now open the flights file to start adding flights to the graph
    file.open(flightFile);
    if(file.is_open())
    {
        string line;
        vector<string> row;
        //skip first line (column names)
        getline(file, line);
        //while the lines exist
        while(getline(file, line))
        {
            row.clear();
            string word;
            stringstream str(line);
            while(getline(str, word, ',')) {
                row.push_back(word);
            }
            //the columns are as follows: (index),flight_date,origin,dest,cancelled,distance,actual_elapsed_time
            //we need indexes 2,3,4,6 -> origin,dest,cancelled, actual_elapsed_time
            try {//in case there is a parsing error, skip the line and continue.
                if (row[4] == "0") {//if the flight was not canceled, add it.
                    string &origin = row[2];
                    string &dest = row[3];
                    int time = stoi(row[6]);
                    flights.addFlight(airportNames[origin], origin, airportNames[dest], dest, time);
                }
            } catch (...) {
            }
        }
    }
    else {
        return;
    }
}
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