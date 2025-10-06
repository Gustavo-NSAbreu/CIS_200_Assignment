// File: Plant.cpp
// 
// Contains the function definitions for the power Plant class
#include "GridDef.h"
#include "Plant.h"
#include <iostream>
#include <sstream>
#include <iomanip>

//
//  Constructors and Destructors
//
PowerPlant::PowerPlant(const string& name, const string& type, const double maxCapacity, const double cost)
    : plantName(name), type(type), maxCapacity(maxCapacity), costPerMW(cost) {}



//
// reduceCapacity() - reduces available capacity of a plant 
//
void PowerPlant::reduceCapacity(double amount) {
    assert(amount <= availCapacity);

    if (amount <= availCapacity) {
        availCapacity -= amount;
    }
}

//
// getCapacityAllocated()  -  Returns power capacity already allocated to areas
//
double  PowerPlant::getCapacityAllocated() const { 
???
}  


//
// getCostOfAllocated()  -  Returns cost of the power to allocated to areas
//
double  PowerPlant::getCostOfAllocatedPower() const {
???
}  

// Debug and Print functions
void PowerPlant::printAll() const {
    cout << this <<
        "  Plant: " <<
        setw(14) << left << plantName <<
        setw(12) << left << type <<
        setw(10) << right << maxCapacity << "mw" <<
        setw(10) << right << availCapacity << "mw" <<
        setw(10) << right << curCapacity << "mw" <<
        ",  " << getCurConditions() << endl;
}


//******************************************************
//                  Solar Plant                    *****
//******************************************************
//
//  Constructors and Destructors
//
SolarFarm::SolarFarm(const string& name, double capacity, double cost, double numAcres, double sunlightHours) :
    PowerPlant(name, PT_SOLAR, capacity, cost), numAcres(numAcres), sunlightHours(sunlightHours) {
}

//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double SolarFarm::calculateOutput() {

    // Calculate and set the current output of this plant
    double output = numAcres * sunlightHours / 55;
    curCapacity = output;
    availCapacity = output;
    return output;

}


//
// getCurCondtions():  Returns the current conditons at the plant
// 
string SolarFarm::getCurConditions() const {
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
WindFarm::WindFarm(string& name, double maxCapacity, double cost, int turbines, double bladeLen, double windSpeed) :
    PowerPlant(name, PT_WIND,  maxCapacity, cost), turbineCount(turbines), bladeLen(bladeLen), avgWindSpeed(windSpeed) {
}

//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double WindFarm::calculateOutput() {
 ???
    return  output;
}


//
// getCurCondtions():  Returns the current conditions at the plant
// 
string WindFarm::getCurConditions() const {
    stringstream oss;
 ???
     return oss.str();
}


//******************************************************
//               Hydro Electric Plant              *****
//******************************************************
//
//  Constructors and Destructors
//
HydroPlant::HydroPlant(const string& name, double maxCapacity, double cost, double flowRate, double(drop)) :
    PowerPlant(name, PT_HYDRO, maxCapacity, cost), inFlowRate(flowRate), verticalDrop(drop) {
}


//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double HydroPlant::calculateOutput() {
    double output;
 ???
    return output;
}

//
// getCurCondtions():  Returns the current conditions at the plant
// 
string HydroPlant::getCurConditions() const {
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
//  Constructors and Destructors
//
NuclearPlant::NuclearPlant(const string& name, double maxCapacity, double cost, int fuelRods) :
    PowerPlant(name, PT_NUCLEAR, maxCapacity,cost), fuelRodsActive(fuelRods) {
}

//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double NuclearPlant::calculateOutput() {
    double output;
 ???
    return output;
}

//
// getCurCondtions():  Returns the current conditions at the plant
// 
string NuclearPlant::getCurConditions() const {
    stringstream oss;
    oss <<
        "Number of fuels rods active: " << fuelRodsActive;
    return oss.str();
}


//******************************************************
//            Geothermal Power Plant               *****
//******************************************************
//
//  Constructors and Destructors
//
GeothermalPlant::GeothermalPlant(const string& name, double maxCapacity, double cost) :
    PowerPlant(name, PT_GEO_THERMAL, maxCapacity, cost) {
}

//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double GeothermalPlant::calculateOutput() {
 ???
    return curCapacity;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string GeothermalPlant::getCurConditions() const {
    return "Geothermal conditions normal";
}


//******************************************************
//                Gas Fuel Plant                *****
//******************************************************
//
//  Constructors and Destructors
//
GasPlant::GasPlant(const string& name, double capacity, double cost, const string& fuel, double throttlePer) :
    PowerPlant(name, PT_GAS, capacity, cost), fuelType(fuel), throttlePercent(throttlePer) {
}

//
// calcuateOutput():  Overrided function to calculate output of the plant
// This adjusts the available capacity of the plant based on the factors unique to this plant
//
double GasPlant::calculateOutput() {
    double output;
???
    return output;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string GasPlant::getCurConditions() const {
    stringstream oss;
???
    return oss.str();
}


