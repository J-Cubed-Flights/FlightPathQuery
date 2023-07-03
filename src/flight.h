// Header file for Flight Class

#ifndef J_CUBED_FLIGHTS_FLIGHT_H
#define J_CUBED_FLIGHTS_FLIGHT_H


#include <string>
#include <utility>

using namespace std;


class Flight {
private:
    string departureAirport; // should be same name as the Airport Node it is stored in
    string arrivalAirport;
    int flightCount;
    int totalMinutes;
public:
    Flight(string &depart, string &arrive) {
        departureAirport = std::move(depart);
        arrivalAirport = std::move(arrive);
        flightCount = 0;
        totalMinutes = 0;
    }

    int getFlightCount() const {return flightCount;}
    int getTotalMinutes() const {return totalMinutes;}
    int getAverageFlightTime() const {return (flightCount/totalMinutes);}

    int addFlightTime(int time) {
        flightCount++;
        totalMinutes += time;
    }
};


#endif //J_CUBED_FLIGHTS_FLIGHT_H
