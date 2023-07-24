// Header file for DirectedGraph Class

#ifndef J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
#define J_CUBED_FLIGHTS_DIRECTEDGRAPH_H


#include "airport.h"
#include "flightpath.h"

#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

class DirectedGraph {
private:
    const int INF = INT_MAX;
    unordered_map<string, Airport> airports; // string stores the Departure Airport's IATA Code (i.e. JFK)
    Airport nullAirport; //store a null airport, which is used in getAirport
    const int layoverTime;
    bool update = true; //used to determine if we need to update the Floyd Warshall matrix next time we call it.

    //the matrixes below will be built the first time that the floydPath function.
    //this optimized the time needed to make the map after the first time it is called.
    vector<vector<int>> floydMatrix;
    vector<vector<int>> nextMatrix;
    //used for quick access to match ID with airport code;
    unordered_map<string, int> idMap;
    vector<string> airportCodes;


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

    //generates the floyd warshall  map if it is the first time.
    void generateFloydMap() {
        //Initialize: add all the existing direct paths to the matrix
        int n = airportCodes.size();
        floydMatrix = vector<vector<int>>(n, vector<int>(n, INF));
        nextMatrix = vector<vector<int>>(n, vector<int>(n, -1));
        for(int i = 0; i < n; i++) {
            floydMatrix[i][i] = 0;
            Airport& current = airports.at(airportCodes[i]);
            for(auto it : current) {
                Flight& flight = it.second;
                int j = idMap[flight.getArrival()];
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
public:
    DirectedGraph() : layoverTime(120), update(true) {}
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
        update = true;
    }
    vector<string> getAirportCodes() {
        if(airportCodes.size() == airports.size()) {
            return airportCodes;
        }
        for(auto it : airports)
        {
            airportCodes.push_back(it.first);
        }
        quickSort(airportCodes, 0, airportCodes.size() - 1);
        //Assign each airport an ID (it's index).
        for(int i = 0; i < airportCodes.size(); i++) {
            idMap[airportCodes[i]] = i;
        }
        return airportCodes;
    }
    vector<string> getAirportNames() {
        if(airportCodes.size() != airports.size()) {
            getAirportCodes();
        }
        vector<string> result;
        for(string code : airportCodes)
        {
            result.push_back(code + " - " + airports[code].getAirportName());
        }
        return result;
    }
    int size() {
        return airports.size();
    }
    //generate the 3 shortest paths as a vector
    FlightPath djikstraPath(string &originCode, string &destinationCode)
    {

        FlightPath path = FlightPath();
        if(!validCode(originCode) || !validCode(destinationCode)) {
            return path;
        }
        //set to keep track of airports that have already been visited.
        unordered_set<string> visited;
        unordered_set<string> unvisited;

        //Arrays to store distances and predecessors
        unordered_map<string, int> flight_time;
        unordered_map<string, string> predecessor;

        //Initialize variables
        for(auto AirportIt = airports.begin(); AirportIt != airports.end(); AirportIt++)
        {
            // Adding all vertexes
            unvisited.emplace(AirportIt->first);

            //Adding all predecessors
            if(AirportIt->first == originCode)
                predecessor[AirportIt->first] = "NULL";
            else
                predecessor[AirportIt->first] = originCode;

            //Adding weights, if original 0; if no edge setting to -1; if edge set to weight
            if(AirportIt->first == originCode)
                flight_time[AirportIt->first] = 0;
            else if(airports[originCode].flights.find(AirportIt->first) == airports[originCode].flights.end())
                flight_time[AirportIt->first] = INF;
            else
                flight_time[AirportIt->first] = airports[originCode].flights[originCode].getAverageFlightTime();
        }

        //Used in while loop
        Airport current_airport = airports[originCode];
        string shortest_flight;
        int path_time = 0;
        int time = 0;

        while(!unvisited.empty())
        {
            // Find the shortest flight from origin
            time = 0;
            visited.emplace(current_airport.getAirportCode());
            unvisited.erase(current_airport.getAirportCode());

            for(string code : unvisited) {
                // Check if a path exists from current airport to code
                if(current_airport.flights.find(code) != current_airport.flights.end() && unvisited.find(code) != unvisited.end())
                {
                    if (time == 0) {
                        shortest_flight = code;
                        time = current_airport.flights[code].getAverageFlightTime();
                    }
                    if (time > current_airport.flights[code].getAverageFlightTime()) {
                        shortest_flight = code;
                        time = current_airport.flights[code].getAverageFlightTime();
                    }
                }
            }

            // Move the shortest flight to visited
            visited.emplace(shortest_flight);
            unvisited.erase(shortest_flight);
            path_time = flight_time[shortest_flight];


            //Update adjacent flight times and predecessors.
            for(auto it = airports[shortest_flight].flights.begin(); it != airports[shortest_flight].flights.end(); it++)
            {
                // Check if new flight time is less than saved flight time and change if necessary
                if(flight_time[it->first] != INF && flight_time[it->first] > path_time + current_airport.flights[it->first].getAverageFlightTime())
                {
                    flight_time[it->first] = path_time + current_airport.flights[it->first].getAverageFlightTime();
                    predecessor[it->first] = shortest_flight;
                }
                else
                {
                    flight_time[it->first] = current_airport.flights[it->first].getAverageFlightTime();
                    predecessor[it->first] = shortest_flight;
                }
            }

            //Checking if no connecting airports are available return to origin
            // Used when dead end is reached.
            auto it = unvisited.begin();
            if(current_airport.getAirportCode() == shortest_flight)
                current_airport = airports[*it];
            else
                current_airport = airports[shortest_flight];

            cout << current_airport.getAirportCode() << endl;
        }

        //Used to build Path once data is calculated. May cause reversed path.
        string airport = destinationCode;
        /*while(airport != originCode)
        {
            path.addToPath(&airports[airport]);
            airport = predecessor[airport];
        }*/

        return path;
    }
    //generate the 3 shortest paths using floyd warshall algorithm
    FlightPath floydPath(std::string &origin, std::string &destination) {

        FlightPath path;

        //if the origin or destination don't exist as valid airports, then return NULL
        if(!validCode(origin) || !validCode(destination)) {
            return path;
        }

        if(update) {//if the floydMap was never made or if there were any flights added, generate it first.
            //Multithreading will be faster if there is more data.
            //generateFloydMapMT();
            generateFloydMap();
            update = false;
        }
        int from = idMap[origin];
        int to = idMap[destination];
        //return empty path if there is no path.
        if(nextMatrix[from][to] == -1) {
            if(from == to) {//If the path is to itself
                path.addToPath(&airports.find(origin)->second);
            }
            return path;
        }
        path.addToPath(&airports.find(origin)->second);
        while(from != to) {
            from = nextMatrix[from][to];
            path.addToPath(&airports.find(airportCodes[from])->second);
        }
        return path;
    }

    void parseData(string airportFile, string flightFile) {
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
};



#endif //J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
