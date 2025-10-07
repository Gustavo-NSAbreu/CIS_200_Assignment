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
   TransLine(int id, const string& name, double capacity, double eff)
        : lineID(id), lineName(name), maxCapacity(capacity), capacityInUse(0.0), efficiency(eff) {}

    

    // Mutators
// Reduce available capacity and return remaining capacity
    double reduceCapacity(double powerAmount) {
        if (powerAmount > getRemainingCapacity()) {
            cout << "Warning: Requested power exceeds line capacity! Setting to maximum.\n";
            capacityInUse = maxCapacity;
        } else {
            capacityInUse += powerAmount;
        }
        return getRemainingCapacity();
    }

    // Return how much capacity is still available
    double getRemainingCapacity() const {
        return maxCapacity - capacityInUse;
    }
    // Accessors - Geters and Setters
   int getLineID() const { return lineID; }
    string getLineName() const { return lineName; }
    double getMaxCapacity() const { return maxCapacity; }
    double getEfficiency() const { return efficiency; }

// Reset line usage
    void resetCapacity() { capacityInUse = 0.0; }

void resetCapacity() { capacityInUse = 0.0; }
}; 
