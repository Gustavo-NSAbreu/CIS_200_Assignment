// File: Plant.cpp
// 
// Contains the function definitions for the power Plant class
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include "../header/GridDef.h"
#include "../header/Plant.h"

//
// reduceCapacity() - reduces available capacity of a plant 
//
void PowerPlant::reduceCapacity(double amount) {
    //assert(amount <= availableCapacity);
    if (amount <= availableCapacity) {
        availableCapacity -= amount; // Reduces the available output or capacity
    }
}

//
// getCapacityAllocated()  -  Returns power capacity already allocated to areas
//
double PowerPlant::getCapacityAllocated() const { 
    return currentOutput - availableCapacity;
}


//
// getCostOfAllocated()  -  Returns cost of the power to allocated to areas
//
double  PowerPlant::getCostOfAllocatedPower() const {
    return getCapacityAllocated() * operatingCost;
}



//******************************************************
//                  Solar Plant                    *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double SolarFarm::calculateOutput() {
    // Calculate and set the current output of this plant
    currentOutput = numAcres * sunlightHours / 55;
    availableCapacity = currentOutput;
    return currentOutput;
}


//
// getCurCondtions():  Returns the current conditons at the plant
// 
string SolarFarm::getCurrentCondition() const {
    stringstream oss;
    oss << "Number of Acres: " << numAcres <<
        ", Sunlight: " << sunlightHours << " Hrs";
    return oss.str();
}





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
    currentOutput = turbineCount * avgWindSpeed / 9.8;
    availableCapacity = currentOutput;
    return currentOutput;
}


//
// getCurCondtions():  Returns the current conditions at the plant
// 
string WindFarm::getCurrentCondition() const {
    stringstream oss;
    oss << "# Turbines: " << turbineCount
        << ", Blade Len: " << bladeLength
        << " ft., Wind: " << avgWindSpeed;
     return oss.str();
}


//******************************************************
//               Hydro Electric Plant              *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double HydroPlant::calculateOutput() {
    currentOutput = inFlowRate * verticalDrop / 600;
    availableCapacity = currentOutput;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditions at the plant
// 
string HydroPlant::getCurrentCondition() const {
    stringstream oss;
    oss << std::fixed << std::setprecision(2) <<
        "Water Flow: " << inFlowRate << " m3/s"
        ", Drop: " << verticalDrop << " m";
    return oss.str();
}




//******************************************************
//               Nuclear Power Plant               *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double NuclearPlant::calculateOutput() {
    currentOutput = fuelRodsActive * 20;
    availableCapacity = currentOutput;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditions at the plant
// 
string NuclearPlant::getCurrentCondition() const {
    stringstream oss;
    oss << "Number of fuels rods active: " << fuelRodsActive;
    return oss.str();
}


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
    availableCapacity = currentOutput;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditons at the plant
//
string GeothermalPlant::getCurrentCondition() const {
    return "Geothermal conditions normal";
}


//******************************************************
//                Gas Fuel Plant                *****
//******************************************************
//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double GasPlant::calculateOutput() {
    currentOutput = maxPowerOutput * throttlePercent / 100.0;
    availableCapacity = currentOutput;
    return currentOutput;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string GasPlant::getCurrentCondition() const {
    stringstream oss;
    oss << "Fuel Type: " << fuelType << ", Throttle open %: " << throttlePercent;
    return oss.str();
}