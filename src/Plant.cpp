// File: Plant.cpp
// 
// Contains the function definitions for the power Plant class
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include "../header/GridDef.h"
#include "../header/Plant.h"

//
// reduceCapacity() - reduces available capacity of a plant 
//
void PowerPlant::reduceCapacity(double amount) {
    assert(amount <= currentOutput);
    if (amount <= currentOutput) {
        currentOutput -= amount;
    }
}

//
// getCapacityAllocated()  -  Returns power capacity already allocated to areas
//
// double  PowerPlant::getCapacityAllocated() const { 
// //???
// }  


//
// getCostOfAllocated()  -  Returns cost of the power to allocated to areas
//
// double  PowerPlant::getCostOfAllocatedPower() const {
// //???
// }  

// Debug and Print functions
// void PowerPlant::printAll() const {
//     cout << this <<
//         "  Plant: " <<
//         setw(14) << left << plantName <<
//         setw(12) << left << type <<
//         setw(10) << right << maxPowerOutput << "mw" <<
//         setw(10) << right << currentOutput << "mw" <<
//         ",  " << getCurrentCondition() << endl;
// }


//******************************************************
//                  Solar Plant                    *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double SolarFarm::calculateOutput() {
    // Calculate and set the current output of this plant
    double output = numAcres * sunlightHours / 55;
    currentOutput = output;
    return output;
}


//
// getCurCondtions():  Returns the current conditons at the plant
// 
// string SolarFarm::getCurrentCondition() const {
//     stringstream oss;
//     oss << "Number of Acres: " << numAcres <<
//         ", Sunlight: " << sunlightHours << " Hrs";
//     return oss.str();
// }





//******************************************************
//                 Wind Farm Plant                 *****
//******************************************************
//
//  Constructors and Destructors
//


//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//

double WindFarm::calculateOutput() {
    double factor = min(avgWindSpeed / 25.0, 1.0); // cap at 1.0
    currentOutput = maxPowerOutput * factor;
    return currentOutput;
}


//
// getCurCondtions():  Returns the current conditions at the plant
// 
// string WindFarm::getCurrentCondition() const {
//     stringstream oss;
//  //???
//      return oss.str();
// }


//******************************************************
//               Hydro Electric Plant              *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double HydroPlant::calculateOutput() {
    // Simplified formula: power proportional to flow * drop
    double factor = min((inFlowRate * verticalDrop) / 1000.0, 1.0);
    currentOutput = maxPowerOutput * factor;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditions at the plant
// 
// string HydroPlant::getCurrentCondition() const {
//     stringstream oss;
//     oss << std::fixed << std::setprecision(2) <<
//         "Water Flow: " << inFlowRate << " m3/s"
//         ", Drop: " << verticalDrop << " m";
//     return oss.str();
// }




//******************************************************
//               Nuclear Power Plant               *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double NuclearPlant::calculateOutput() {
    double factor = min(fuelRodsActive / 100.0, 1.0); // max 100 rods
    currentOutput = maxPowerOutput * factor;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditions at the plant
// 
// string NuclearPlant::getCurrentCondition() const {
//     stringstream oss;
//     oss <<
//         "Number of fuels rods active: " << fuelRodsActive;
//     return oss.str();
// }


//******************************************************
//            Geothermal Power Plant               *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double GeothermalPlant::calculateOutput() {
    // Stable output, just use max
    currentOutput = maxPowerOutput;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
// string GeothermalPlant::getCurrentCondition() const {
//     return "Geothermal conditions normal";
// }


//******************************************************
//                Gas Fuel Plant                *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double GasPlant::calculateOutput() {
    double factor = throttlePercent / 100.0;
    currentOutput = maxPowerOutput * factor;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
// string GasPlant::getCurrentCondition() const {
//     stringstream oss;
// //???
//     return oss.str();
// }


