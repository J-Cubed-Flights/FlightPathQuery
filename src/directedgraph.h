// Header file for DirectedGraph Class

#ifndef J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
#define J_CUBED_FLIGHTS_DIRECTEDGRAPH_H


#include "airport.h"

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
};


#endif //J_CUBED_FLIGHTS_DIRECTEDGRAPH_H
