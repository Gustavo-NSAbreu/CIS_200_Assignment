// File: ServiceArea.cpp
// 
// Contains the function definitions for the power grid ServiceAreaclass
//
#include "ServiceArea.h"
#include <iostream>
#include <iomanip>


//
//  Constructors and Destructors
//
ServiceArea::ServiceArea(const string& name, double requiredCapacity, double price)
    : areaName(name), powerRequired(requiredCapacity), powerReceived(0), mwPrice(price) 
{
    //allocStatus = ACTIVE;
    //status = NOT_MET;
}


//
// addCapacity() -- Adds capacity to the service area - 
// Signifies the grid is commiting an amount of power to this location
//
void ServiceArea::addCapacity(double amount) {

    // Update the amount of power supplied and the status 
    powerReceived += amount;

}


//
// Setters and Getters
//
string ServiceArea::getAreaName() const { return areaName; }
double ServiceArea::getPowerRequired() const { return powerRequired; }
double ServiceArea::getPowerProvided() const { return powerReceived; }
double ServiceArea::getMWPrice() const { return mwPrice; }

//
// Debug and Print functions
//
void ServiceArea::printAll() const {
    cout << this << fixed << 
        "  Area: " << setw(12) << left << areaName <<
        setw(8) << right << powerRequired <<
        setw(12) << right << mwPrice <<
        setw(8)  << right << powerReceived << 
        endl;
}
