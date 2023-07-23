// Header file for Flight Class

#ifndef J_CUBED_FLIGHTS_FLIGHT_H
#define J_CUBED_FLIGHTS_FLIGHT_H


#include <string>
#include <utility>

using namespace std;


class Flight {
private:
    //IATA code of the Airport object that it departs from
    string departureAirport;
    //IATA code of the Airport object that it arrives at.
    string arrivalAirport;
    //number of flights added to this airport
    int flightCount;
    //number of minutes from all flights combined.
    int totalMinutes;
public:
    //constructors
    Flight();
    Flight(string &depart, string &arrive) : departureAirport(depart),arrivalAirport(arrive),flightCount(0),totalMinutes(0) {}
    Flight(const Flight &copy) : departureAirport(copy.departureAirport),arrivalAirport(copy.arrivalAirport),flightCount(copy.flightCount),totalMinutes(copy.totalMinutes) {}

    //getters
    string getDeparture() const {return departureAirport;}
    string getArrival() const {return arrivalAirport;}
    int getFlightCount() const {return flightCount;}
    int getTotalMinutes() const {return totalMinutes;}
    int getAverageFlightTime() const {return (totalMinutes/flightCount);}

    //add the amount of time of a flight.
    void addFlightTime(int time);
};
//add the amount of time of a flight
void Flight::addFlightTime(int time) {
    flightCount++;
    totalMinutes += time;
}


#endif //J_CUBED_FLIGHTS_FLIGHT_H
