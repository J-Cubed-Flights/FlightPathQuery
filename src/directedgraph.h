// Header file for DirectedGraph Class

#ifndef J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
#define J_CUBED_FLIGHTS_DIRECTEDGRAPH_H


#include "airport.h"
#include "flightpath.h"

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class DirectedGraph {
private:
    unordered_map<string, Airport> airports; // string stores the Departure Airport's IATA Code (i.e. JFK)
    Airport nullAirport; //store a null airport, which is used in getAirport
    void quickSort(vector<string> &arr, int l, int r) {
        //we will have the first index be the pivot.
        if(l >= r) {
            return;
        }
        int pivotI = l++;
        int end = r;
        while(l <= r) {
            while(l <= r && arr[l] < arr[pivotI]) {
                l++;
            }
            while(l <= r && arr[r] >= arr[pivotI]) {
                r--;
            }
            if(l < r && arr[l] >= arr[pivotI] && arr[pivotI] > arr[r]) {
                //swap
                string temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
                l++;
                r--;
            }
        }
        //swap
        string temp = arr[r];
        arr[r] = arr[pivotI];
        arr[pivotI] = temp;
        quickSort(arr, pivotI, r - 1);
        quickSort(arr, r + 1, end);
    }
    //the matrix below will be built the first time that the floydPath function.
    //this optimized the time needed to make the map after the first time it is called.
    unordered_map<string, unordered_map<string, int>> floydMap;
    unordered_map<string, unordered_map<string, int>> next;
    //TODO:build floyd warshall map generator
    //generates the floyd warshall  map if it is the first time.
    void generateMap() {
        //first, initialize: add all the existing direct paths to the matrix
//        int V = size();
//        for (auto fromIt : airports) {
//            Airport& current = fromIt.second;
//            for(auto toIt : )
//        }
    }
public:
    bool validCode(string &code) {
        return airports.find(code) != airports.end();
    }
    Airport& getAirport(string &code) {
        auto it = airports.find(code);
        if(it == airports.end()) {
            return nullAirport;
        }
        return airports.at(code);
    }

    // public function to add a flight into the unordered_map of airports
    void addFlight(string &airportFullName, string &departCode, string &arriveFullName, string &arriveCode, int flightTime) {
        auto it = airports.find(departCode);

        if (it != airports.end()) {
            it->second.updateFlight(arriveCode, flightTime);
        } else {
            Airport newAirport(airportFullName, departCode);
            newAirport.updateFlight(arriveCode, flightTime);

            airports.emplace(departCode, newAirport);
        }
        //create destination airport if it doesn't exist.
        //this will prevent later issues in case that airport never had outgoing flights.
        it = airports.find(arriveCode);
        if(it == airports.end()) {
            Airport newAirport(arriveFullName, arriveCode);
            airports.emplace(arriveCode, newAirport);
        }
    }
    vector<string> getAirportNames() {
        vector<string> result;
        string data;

        // Honestly think if we want it to be a sorted list we should just create sorted map
        // Then we should just be able to do the following - Jan (7/7/2023)

        //an unordered map is not sorted, but is faster than a sorted map for the standard operations. - Jason
        //over all, it would be faster to keep it as unordered, and just sort after we get the strings.
        //this is O(nlog(n)) time since each comparison will only be between the first 3 letters of each string anyways.
        for(auto it = airports.begin(); it != airports.end(); it++)
        {
            data = it->first + " - " + it->second.getAirportName();
            result.push_back(data);
        }
        quickSort(result, 0, result.size() - 1);
        return result;
    }
    int size() {
        return airports.size();
    }
    //generate the 3 shortest paths as a vector
    FlightPath djikstraPath(DirectedGraph &airports, string &originCode, string &destinationCode)
    {
        // This is intended to create the flight path from start to finish.
        // The data then can be used to calculate flight time.
        FlightPath path = FlightPath();
        //make sure that both the origin and destination are valid
        if(airports.validCode(originCode) || airports.validCode(destinationCode)) {
            return paths;
        }

        //this keeps track of the predecessor node/airport.
        //this will be used to build the final path.
        unordered_map<string, string> previous;
        //set to keep track of airports that have already been visited.
        unordered_set<string> visited;
        //we will start at
        visited.emplace(originCode);
        path.addToPath(airports[originCode]);

        Airport current_airport = airports[originCode];
        while(current_airport != airports[destinationCode])
        {
            int shortest_flight = 0;
            string next_flight;
            if(current_airport.flights.find(destinationCode) == current_airport.flights.end())
            {
                // Search all connected flights for shortest flight
                for(auto flightIt = current_airport.flights.begin(); flightIt != current_airport.flights.end(); flightIt++)
                {
                    // Check if airport has been visited
                    if(visited.find(flightIt->first) != visited.end())
                    {
                        // First flight in flights will be our base value
                        if (shortest_flight == 0) {
                            shortest_flight = flightIt->second.getAverageFlightTime();
                            next_flight = flightIt->first;
                        }
                        // Update shortest flight
                        else if (flightIt->second.getAverageFlightTime() < shortest_flight) {
                            shortest_flight = flightIt->second.getAverageFlightTime();
                            next_flight = flightIt->first;
                        }
                    }
                }
                // Update visited, current airport, and add stop to flight path
                visited.emplace(next_flight);
                current_airport = airports[next_flight];
                path.addToPath(airports[next_flight]);
            }
            else if(current_airport.flights.find(destinationCode) != current_airport.flights.end())
            {
                current_airport = airports[destinationCode];
                path.addToPath(airports[destinationCode]);
            }

        }
        return path;
    }
    //generate the 3 shortest paths using floyd warshall algorithm
    vector<FlightPath> floydPath(std::string &origin, std::string &destination) {
        //TODO
        if(floydMap.size() == 0) {//if the floydMap was never made, generate it first.
            generateMap();
        }
        //if the origin or destination don't exist as valid values, then return NULL

        if(airports.find(origin) == airports.end() || airports.find(destination) == airports.end()) {
            return NULL;
        }
    }
};

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

#endif //J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
