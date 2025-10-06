#pragma once
// File: ServiceArea.h
//
// Contains class definition for the Service Area class on the power grid
//
// erviceArea objects identify a location and the amount of power (megawatts) 
// that the location requires and has has been provided.  
// 
// They track how much power is currently being supplied and the amount 
// needed to fully to meet their power requirements.  They can also 
// quickly report on the status of if their requiermends are satisfied.
// 
#include <string>
using namespace std;

class ServiceArea {
protected:
    string          areaName;         
    double          powerRequired;  // Total power (MW) this area needs 
    double          powerReceived;  // Amount of power (MW) currently provided
    double          mwPrice;        // Price ($) this area pays per MW
 

public:
    // Constructors & Destructors
    ServiceArea(const string& areaName, double requiredCapacity, double price); 

    // Mutators
    void addCapacity(double amount); 
    const double getPowerDeficit() const { return powerRequired - powerReceived; }
    const double getTotalPriceForPower() const { return powerReceived * mwPrice; }

    // Accessors
    string getAreaName() const;
    double getPowerRequired() const;
    double getPowerProvided() const;
    double getMWPrice() const;
 
    // Print and debug
    void printAll() const;   // Prints information for debugging
};


