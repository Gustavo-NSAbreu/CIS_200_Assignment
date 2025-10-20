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
#include <cmath>

using namespace std;

class ServiceArea {
protected:
    string          areaName;         
    double          powerRequired;  // Total power (MW) this area needs 
    double          powerReceived;  // Amount of power (MW) currently provided
    double          mwPrice;        // Price ($) this area pays per MW
    enum AllocStatus { ACTIVE, INACTIVE } allocStatus;
    enum SupplyStatus { NOT_MET, PARTIAL_MET, FULLY_MET } status;
 

public:
  // Constructor
    ServiceArea(const string& name, double requiredCapacity, double price)
        : areaName(name), powerRequired(requiredCapacity), powerReceived(0.0), mwPrice(price) {
        allocStatus = ACTIVE;
        status = NOT_MET;
    }

    // Add power to the area (capped by requirement)
    void addCapacity(double amount);

    // Returns how much more power is needed
    double getPowerDeficit() const { 
        return fabs(powerRequired - powerReceived); 
    }


    // Returns total cost for power received
    double getTotalPriceForPower() const { 
        return powerReceived * mwPrice; 
    }

    // Accessors
    string getAreaName() const { return areaName; }
    double getPowerRequired() const { return powerRequired; }
    double getPowerProvided() const { return powerReceived; }
    double getMWPrice() const { return mwPrice; }

    // Status check: true if fully supplied
    bool isFullySupplied() const {
        return powerReceived >= powerRequired;
    }
    
    void resetPower() { powerReceived = 0.0; }
};