// Header file for Flight Class

#ifndef J_CUBED_FLIGHTS_FLIGHT_H
#define J_CUBED_FLIGHTS_FLIGHT_H


#include <string>
#include <utility>

using namespace std;


class Flight {
private:
    string departureAirport; // should be same IATA as the Airport object it is stored in
    string arrivalAirport;
    int flightCount;
    int totalMinutes;
public:
    Flight(){};
    Flight(string &depart, string &arrive) {
        departureAirport = depart;
        arrivalAirport = arrive;
        flightCount = 0;
        totalMinutes = 0;
    }
    Flight(const Flight &copy) {
        departureAirport = copy.departureAirport;
        arrivalAirport = copy.arrivalAirport;
        flightCount = copy.flightCount;
        totalMinutes = copy.totalMinutes;
    }

    string getDeparture() const {return departureAirport;}
    string getArrival() const {return arrivalAirport;}
    int getFlightCount() const {return flightCount;}
    int getTotalMinutes() const {return totalMinutes;}
    int getAverageFlightTime() const {return (totalMinutes/flightCount);}

    void addFlightTime(int time) {
        flightCount++;
        totalMinutes += time;
    }
};


#endif //J_CUBED_FLIGHTS_FLIGHT_H
