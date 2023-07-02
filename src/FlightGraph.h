//
// Created by jason on 7/2/2023.
//

#ifndef SRC_FLIGHTGRAPH_H
#define SRC_FLIGHTGRAPH_H
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class FlightGraph {
    public:
        class Airport{
            private:
                string name;
                string abbrv;
            public:
                Airport(string n, string a) : name(n), abbrv(a) {}
                struct FlightData {
                    int flightCount;
                    int totalMinutes;
                    FlightData() : flightCount(0), totalMinutes(0) {}
                    int addFlight(int time);
                    int getAvg();
                };
                string getName();
                string getAbbrv();
            private:
                unordered_map<int, FlightData> flights;
            public:
        };
        Airport getAirport(string abbrv);
    private:
        unordered_map<string, int> airportIDs;
        vector<Airport> airports;
};

 // std

#endif //SRC_FLIGHTGRAPH_H
