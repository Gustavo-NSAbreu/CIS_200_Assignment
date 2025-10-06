#pragma once
// File: TransLine.h
//
// Contains class definition for the Transmission Lines that connect 
// the power plants to demand locations
//
// The transmission lines connect the power plants to the demand locations.
//		Each line has a lineID, a name, a capacity, and an efficiency.
// 
// The Capacity is maximum amount of power that can travel on the line. 
// The Efficiency value helps model the energy lost transmitting the power from a plant to the demand.
//
// Note: All functions in the class are inLine.  There is no TransLine.cpp in the project
//
#include <string>
using namespace std;

class TransLine{
protected:
    int     lineID;
    string  lineName;
    double  maxCapacity;    // The maximum amount of power this line can transmit. (In megawatts)
    double  capacityInUse;  // The amount of power currently in use (gross - before efficency drop)
    double  efficiency;     // Indicates how much supplied power is actually delivered (range: 0-100)  


    // All methods must be inline for this class !!!

public:
    // Constructors & Destructors
    TransLine(const int lineID, const string& lineName, double capacity, double efficiency);
    

    // Mutators
    double reduceCapacity(const double powerAmount); // Reduces available capacity and returns capacity remaining 
    double getRemainingCapacity() const;

    // Accessors - Geters and Setters
    int     getLineID() const;
    string  getLineName() const; 
    double  getMaxCapacity() const;
    double  getEfficiency() const;
};


