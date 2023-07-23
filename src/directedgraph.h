// Header file for DirectedGraph Class

#ifndef J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
#define J_CUBED_FLIGHTS_DIRECTEDGRAPH_H


#include "airport.h"
#include "flightpath.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

class DirectedGraph {
private:
    const int INF = INT_MAX;
    const int layoverTime;
    bool updateFloydMatrix = true; //used to determine if we need to update the Floyd Warshall matrix next time we call it.

    // string stores the Departure Airport's IATA Code (i.e. JFK)
    unordered_map<string, Airport> airports;

    //used for quick access to match ID with airport code;
    vector<Airport*> airportVector;

    //store a null airport, which is used in getAirport when there is an invalid code.
    Airport nullAirport;

    //the matrixes below will be built the first time that the floydPath function.
    //this optimized the time needed to make the map after the first time it is called.
    vector<vector<int>> floydMatrix;
    vector<vector<int>> nextMatrix;

    //used for sorting the airportVector.
    void quickSort(vector<Airport*> &arr, int l, int r);

    //generates the floyd warshall  map if it is the first time.
    void generateFloydMap();

    //generates airport id's after alphabetizing them.
    void generateAirportIDs();

public:
    //constructor
    DirectedGraph() : layoverTime(120), updateFloydMatrix(false) {}

    //check if it is a valid code of an airport
    bool validCode(string &code) {return airports.find(code) != airports.end();}

    ////getters
    //returns the airport corresponding to the IATA code, or a null airport if the code is invalid
    Airport& getAirport(string &code);

    //returns a vector of the airport codes
    vector<string> getAirportCodes();

    //returns a vector of the airports' names in the format: "[code] - [name]"
    vector<string> getAirportNames();

    //returns the number of vertices in graph
    int size() {return airports.size();}

    ////Utility Functions
    //public function to add a flight into the unordered_map of airports
    void addFlight(string &airportFullName, string &departCode, string &arriveFullName, string &arriveCode, int flightTime);

    //Clears the graph.
    //Used in GUI to search new folder for data and generate new graph.
    void clear();

    //Resets the floyd warshall matrices the next time the algorithm is called.
    //Used in GUI to help reset the FloydPath without restarting the executable.
    void reset() {updateFloydMatrix = true;}

    ////Path finding algorithms
    //generate the shortest paths using floyd warshall algorithm
    FlightPath floydPath(std::string &origin, std::string &destination);

    //generate the shortest path as a vector using Djikstra's algorithm
    FlightPath djikstraPath(string &originCode, string &destinationCode);

    //Parse data from file locations and puts it into the graph
    //airportFile is used to get the IATA code and Airport name
    //flightFile is used to get the individual flights
    void parseData(string airportFile, string flightFile);
};
//generates the id's for the airport
void DirectedGraph::generateAirportIDs() {
    if(airportVector.size() == airports.size()) {
        return;
    }
    airportVector.clear();
    for(auto it = airports.begin(); it != airports.end(); it++)
    {
        Airport* cur = &(it->second);
        airportVector.push_back(cur);
    }
    quickSort(airportVector, 0, airportVector.size() - 1);
    //Assign each airport an ID (it's index).
    for(int i = 0; i < airportVector.size(); i++) {
        airportVector[i]->setID(i);
    }
}
//sorts the vector by airport code.
void DirectedGraph::quickSort(vector<Airport*> &arr, int l, int r) {
    //we will have the first index be the pivot.
    if(l >= r) {
        return;
    }
    int pivotI = l++;
    int end = r;
    while(l <= r) {
        while(l <= r && arr[l]->getAirportCode() < arr[pivotI]->getAirportCode()) {
            l++;
        }
        while(l <= r && arr[r]->getAirportCode() >= arr[pivotI]->getAirportCode()) {
            r--;
        }
        if(l < r && arr[l]->getAirportCode() >= arr[pivotI]->getAirportCode() && arr[pivotI]->getAirportCode() > arr[r]->getAirportCode()) {
            //swap
            Airport* temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    }
    //swap
    Airport* temp = arr[r];
    arr[r] = arr[pivotI];
    arr[pivotI] = temp;
    quickSort(arr, pivotI, r - 1);
    quickSort(arr, r + 1, end);
}
//generates the map used for Floyd Warshall
void DirectedGraph::generateFloydMap() {
    //Initialize: add all the existing direct paths to the matrix
    int n = airportVector.size();
    floydMatrix = vector<vector<int>>(n, vector<int>(n, INF));
    nextMatrix = vector<vector<int>>(n, vector<int>(n, -1));
    for(int i = 0; i < n; i++) {
        floydMatrix[i][i] = 0;
        Airport& current = *airportVector[i];
        for(auto it : current) {
            Flight& flight = it.second;
            int j = airports[flight.getArrival()].getID();
            floydMatrix[i][j] = flight.getAverageFlightTime();
            nextMatrix[i][j] = j;
        }
    }

    //modified Floyd Warshall Algorithm
    for(int mid = 0; mid < n; mid++) {
        for(int i = 0; i < n; i++) {
            if(floydMatrix[i][mid] != INF) {
                for (int j = 0; j < n; j++) {
                    if (floydMatrix[mid][j] == INF) {
                        continue;
                    }
                    if (floydMatrix[i][j] > floydMatrix[i][mid] + layoverTime + floydMatrix[mid][j]) {
                        floydMatrix[i][j] = floydMatrix[i][mid] + layoverTime + floydMatrix[mid][j];
                        nextMatrix[i][j] = nextMatrix[i][mid];
                    }
                }
            }
        }
    }
}
//get the airport using its IATA code. if it doesn't exist, return a null airport.
Airport& DirectedGraph::getAirport(string &code) {
    auto it = airports.find(code);
    if(it == airports.end()) {
        return nullAirport;
    }
    return airports.at(code);
}
//return a vector of strings of the airport codes;
vector<string> DirectedGraph::getAirportCodes() {
    generateAirportIDs();
    vector<string> result;
    for(auto it : airportVector) {
        result.push_back(it->getAirportCode());
    }
    return result;
}
//generates a vector of the airport names alphabetically, formatted as "[code] - [name]"
vector<string> DirectedGraph::getAirportNames() {
    generateAirportIDs();
    vector<string> result;
    for(Airport* port : airportVector) {
        result.push_back(port->getAirportCode() + " - " + port->getAirportName());
    }
    return result;
}
//clears the graph completely
void DirectedGraph::clear() {
    reset();
    airportVector.clear();
    airports.clear();
}
//add a flight to the directed graph
void DirectedGraph::addFlight(string &airportFullName, string &departCode, string &arriveFullName, string &arriveCode, int flightTime) {
    auto it = airports.find(departCode);

    if (it != airports.end()) {
        //if the airport exists, update the flight at that airport
        it->second.updateFlight(arriveCode, flightTime);
    } else {
        //if the airport doesn't exist, create it, then add the flight.
        Airport newAirport(airportFullName, departCode);
        newAirport.updateFlight(arriveCode, flightTime);
        //add airport to the map
        airports.emplace(departCode, newAirport);
    }
    //create destination airport if it doesn't exist.
    //this will prevent later issues in case that airport never had outgoing flights.
    it = airports.find(arriveCode);
    if(it == airports.end()) {
        Airport newAirport(arriveFullName, arriveCode);
        airports.emplace(arriveCode, newAirport);
    }
    //tell floyd warshall that it will need to update next time.
    updateFloydMatrix = true;
}

//Parse data from file locations and puts it into the graph
//airportFile is used to get the IATA code and Airport name
//flightFile is used to get the individual flights
void DirectedGraph::parseData(string airportFile, string flightFile) {
    //first, get all the airport iata values and their corresponding names.
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
            //get the iata and airport strings
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
                if (row[4] == "0" && row.size() == 7) {//if the flight was not canceled, add it.
                    string &origin = row[2];
                    string &dest = row[3];
                    int time = stoi(row[6]);
                    addFlight(airportNames[origin], origin, airportNames[dest], dest, time);
                }
            } catch (...) {
            }
        }
    }
    else {
        return;
    }
    getAirportCodes();
}

//generate the shortest paths using floyd warshall algorithm
FlightPath DirectedGraph::floydPath(std::string &origin, std::string &destination) {

    FlightPath path;

    //if the origin or destination don't exist as valid airports, then return NULL
    if(!validCode(origin) || !validCode(destination)) {
        return path;
    }

    if(updateFloydMatrix) {//if the floydMap needs to be updated, generate it first.
        generateFloydMap();
        updateFloydMatrix = false;
    }
    //get the ids of the two airports
    int from = airports[origin].getID();
    int to = airports[destination].getID();

    //return empty path if there is no path.
    if(nextMatrix[from][to] == -1) {
        if(from == to) {//If the path is just itself
            path.addToPath(&airports.find(origin)->second);
        }
        return path;
    }
    //add the starting airport to the path
    path.addToPath(&airports.find(origin)->second);
    while(from != to) {
        //go to next airport in the path
        from = nextMatrix[from][to];
        //add that airport to the path
        path.addToPath(airportVector[from]);
    }
    return path;
}
//generate the shortest path as a vector using Djikstra's algorithm
FlightPath DirectedGraph::djikstraPath(string &originCode, string &destinationCode) {
    // This is intended to create the flight path from start to finish.
    // The data then can be used to calculate flight time.
    FlightPath path = FlightPath();
    //make sure that both the origin and destination are valid
    if(!validCode(originCode) || !validCode(destinationCode)) {
        return path;
    }

    //this keeps track of the predecessor node/airport.
    //this will be used to build the final path.
    unordered_map<string, string> previous;
    //set to keep track of airports that have already been visited.
    unordered_set<string> visited;
    //we will start at
    visited.emplace(originCode);
    path.addToPath(&airports[originCode]);

    Airport current_airport = airports[originCode];
    while(current_airport != airports[destinationCode])
    {
        int shortest_flight = 0;
        string next_flight;
        if(current_airport.find(destinationCode) == current_airport.end())
        {
            // Search all connected flights for shortest flight
            for(auto flightIt = current_airport.begin(); flightIt != current_airport.end(); flightIt++)
            {
                // Check if airport has been visited
                if(visited.find(flightIt->first) != visited.end())
                {
                    // First flight in flights will be our base value
                    if (shortest_flight == 0) {
                        shortest_flight = flightIt->second.getAverageFlightTime();
                        next_flight = flightIt->first;
                    }
                        // Update the shortest flight
                    else if (flightIt->second.getAverageFlightTime() < shortest_flight) {
                        shortest_flight = flightIt->second.getAverageFlightTime();
                        next_flight = flightIt->first;
                    }
                }
            }
            // Update visited, current airport, and add stop to flight path
            visited.emplace(next_flight);
            current_airport = airports[next_flight];
            path.addToPath(&airports[next_flight]);
        }
        else if(current_airport.find(destinationCode) != current_airport.end())
        {
            current_airport = airports[destinationCode];
            path.addToPath(&airports[destinationCode]);
        }

    }
    return path;
}


#endif //J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
