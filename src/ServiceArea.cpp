// File: ServiceArea.cpp
// 
// Contains the function definitions for the power grid ServiceAreaclass
//
#include <iostream>
#include <iomanip>
#include "../header/ServiceArea.h"

//
// addCapacity() -- Adds capacity to the service area - 
// Signifies the grid is commiting an amount of power to this location
//
void ServiceArea::addCapacity(double amount) {
    powerReceived += amount;
}