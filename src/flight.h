// Header file for Flight Class

#ifndef J_CUBED_FLIGHTS_FLIGHT_H
#define J_CUBED_FLIGHTS_FLIGHT_H


#include <string>

using namespace std;


class Flight {
private:
    string departureAirport; // should be same name as the Airport Node it is stored in
    string arrivalAirport;
    int flightCount;
    int totalMinutes;
public:
    Flight(string depart, string arrive) {
        departureAirport = depart;
        arrivalAirport = arrive;
        flightCount = 0;
        totalMinutes = 0;
    }

    int getFlightCount() {return flightCount;}
    int getTotalMinutes() {return totalMinutes;}
    int getAverageFlightTime() {return (flightCount/totalMinutes);}

    int addFlightTime(int time) {
        flightCount++;
        totalMinutes += time;
    }
};


#endif //J_CUBED_FLIGHTS_FLIGHT_H
