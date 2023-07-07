//
// Created by Jan Torruellas on 7/7/2023.
//

#ifndef J_CUBED_FLIGHTS_LAYOVERPATH_H
#define J_CUBED_FLIGHTS_LAYOVERPATH_H
#include <vector>
using namespace std;

class LayoverPath
{
private:
    vector<string> Stops;
    int totalFlightTime;
    int totalWithLayover;
public:
    LayoverPath(){totalFlightTime = 0, totalWithLayover = 0};
    int calculateFlightTime();
    int calculateWithLayover();
    void createPath();

};

int LayoverPath::calculateFlightTime()
{
    return totalFlightTime;
}

int LayoverPath::calculateWithLayover()
{
    // Here we are calculating total time with layovers in mind.
    // Adding 2 hours aka 120 minutes per stop to totalFlightTime.
    totalWithLayover = 120 * stops.size() + totalFlightTime;
    return totalWithLayover;
}

void LayoverPath::createPath()
{
    // This is intended to create the flight path from start to finish.
    // The data then can be used to calculate flight time.
}
#endif //J_CUBED_FLIGHTS_LAYOVERPATH_H
