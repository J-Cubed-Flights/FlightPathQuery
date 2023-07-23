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

    //Map to store a unique lock for each airport
    vector<mutex> mutexVector;

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
    void threadWorkerInitRow(int i) {
        Airport& current = airports.at(airportCodes[i]);
        for(auto it : current) {
            Flight& flight = it.second;
            int j = idMap[flight.getArrival()];
            floydMatrix[i][j] = flight.getAverageFlightTime();
            nextMatrix[i][j] = j;
        }
    }
    void threadWorkerCompute(int i, int mid, int n) {
        mutex *curLock = &mutexVector[i];
        for(int j = 0; j < n; j++) {
            if (floydMatrix[mid][j] == INF) {
                continue;
            }
            std::lock_guard<std::mutex> lock(*curLock);
            if (floydMatrix[i][j] > floydMatrix[i][mid] + layoverTime + floydMatrix[mid][j]) {
                floydMatrix[i][j] = floydMatrix[i][mid] + layoverTime + floydMatrix[mid][j];
                nextMatrix[i][j] = nextMatrix[i][mid];
            }
        }
    }
    void generateFloydMapMT() {
        //Initialize: add all the existing direct paths to the matrix
        int max = thread::hardware_concurrency();
        vector<thread> threads(max);
        int c = 0;

        int n = airportCodes.size();
        floydMatrix = vector<vector<int>>(n, vector<int>(n, INF));
        nextMatrix = vector<vector<int>>(n, vector<int>(n, -1));
        mutexVector = vector<mutex>(n);

        for(int i = 0; i < n; i++) {
            floydMatrix[i][i] = 0;
            threads[c++] = thread(&DirectedGraph::threadWorkerInitRow, this, i);
            c %= max;
            if(threads[c].joinable())
                threads[c].join();
        }
        for(c = 0; c < max; c++) {
            if(threads[c].joinable())
            threads[c].join();
        }
        c = 0;
        //modified Floyd Warshall Algorithm
        for(int mid = 0; mid < n; mid++) {
            for(int i = 0; i < n; i++) {
                if(floydMatrix[i][mid] != INF) {
                    threads[c++] = thread(&DirectedGraph::threadWorkerCompute, this, i, mid, n);
                    c %= max;
                    if(threads[c].joinable())
                        threads[c].join();
                }
            }
        }
        for(c = 0; c < max; c++) {
            if(threads[c].joinable())
                threads[c].join();
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
