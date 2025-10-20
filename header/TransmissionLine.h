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
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class TransmissionLine{
protected:
    int     lineID;
    string  lineName;
    double  maxCapacity;    // The maximum amount of power this line can transmit. (In megawatts)
    double  capacityInUse;  // The amount of power currently in use (gross - before efficency drop)
    double  availableCapacity;
    double  efficiency;     // Indicates how much supplied power is actually delivered (range: 0-100)


    // All methods must be inline for this class !!!

public:
    // Constructors & Destructors
   TransmissionLine(int id, const string& name, double capacity, double eff)
        : lineID(id), lineName(name), maxCapacity(capacity), capacityInUse(0.0), availableCapacity(maxCapacity), efficiency(eff) {}

    

    // Mutators
// Reduce available capacity and return remaining capacity
    void reduceCapacity(double powerAmount) {
        if(powerAmount <= availableCapacity) {
            capacityInUse += powerAmount;
            availableCapacity -= powerAmount; // Reduces the available capacity
        }
    }

    // Return how much capacity is still available
    double getRemainingCapacity() const {
        return availableCapacity;
    }
    // Accessors - Geters and Setters
    int getLineID() const { return lineID; }
    string getLineName() const { return lineName; }
    double getMaxCapacity() const { return maxCapacity; }
    double getEfficiency() const { return efficiency; }

// Reset line usage
    void resetCapacity() { capacityInUse = 0.0; }
}; 
