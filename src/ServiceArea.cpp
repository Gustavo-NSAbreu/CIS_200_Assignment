// File: ServiceArea.cpp
// 
// Contains the function definitions for the power grid ServiceAreaclass
//
#include "../header/ServiceArea.h"
#include <iostream>
#include <iomanip>

//
// addCapacity() -- Adds capacity to the service area - 
// Signifies the grid is commiting an amount of power to this location
//
void ServiceArea::addCapacity(double amount) {

    if (amount < 0) {
        cout << "Warning: Cannot add negative power. Ignored.\n";
        return;
    }

    powerReceived += amount;
    if (powerReceived > powerRequired) {
        cout << "Warning: Power supplied exceeds requirement. Capping to requirement.\n";
        powerReceived = powerRequired;
    }
}

//
// Debug and Print functions
//
// void ServiceArea::printAll() const {
//     cout << this << fixed << 
//         "  Area: " << setw(12) << left << areaName <<
//         setw(8) << right << powerRequired <<
//         setw(12) << right << mwPrice <<
//         setw(8)  << right << powerReceived << 
//         endl;
// }
