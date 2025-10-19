
//******************************************************
// File: Plant.h
// Author: Dheya Alrabeei and Gustavo Rameirez
// Date:   October 6 2024
// Description:
//   Contains class definitions for PowerPlant and all
//   derived types. Each plant type has unique attributes
//   and calculates its own power output based on conditions.
//******************************************************

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "GridDef.h"
using namespace std;


//******************************************************
//                Power Plant                      *****
//           Base class for all plants             *****
//******************************************************
//
// Plant:  Base class for all plants
//
class PowerPlant {
protected:
    string name;
    string type;
    double maxPowerOutput = 0.0;        // The absolute maximum capacity of the plant
    double operatingCost = 0.0;    // Cost per megawatt ($)
    double currentOutput = 0.0; // Current calculated output (MW)

public:
    // Constructors & Destructors
    PowerPlant(const string& name, const string& type, double maxPowerOutput, double cost)
        : name(name), type(type), maxPowerOutput(maxPowerOutput), operatingCost(cost), currentOutput(0.0) {}

    // Virtual destructor
    virtual ~PowerPlant() = default;

    // Pure virtual function for output calculation
    virtual double calculateOutput() = 0;

    // Virtual function for current conditions
    virtual string getCurrentCondition() const { return "Normal"; }

    // Getters and Setters
    string getName() const { return name; }
    string getType() const { return type; }
    double getMaxPowerOutput() const { return maxPowerOutput; }
    double getOperatingCost() const { return operatingCost; }
    double getCurrentOutput() const { return currentOutput; }

    double getAvailableCapacity() const {
        return maxPowerOutput - currentOutput;
    }

     
    // Prints all the information for the plant
    // virtual void printAll() const {
    //     cout << "----------------------------------------\n";
    //     cout << "Plant: " << name << " (" << type << ")\n";
    //     cout << "Max Power Output: " << maxPowerOutput << " MW\n";
    //     cout << "Operating Cost: $" << operatingCost << " per MW\n";
    //     cout << "Current Output: " << currentOutput << " MW\n";
    //     cout << "Current Conditions: " << getCurrentCondition() << endl;
    //     cout << "----------------------------------------\n";
    // }

    void reduceCapacity(double amount);
};





//******************************************************
//                  Solar Plant                    *****
//******************************************************
//
class SolarFarm : public PowerPlant {
private:
    double numAcres;
    double sunlightHours;   // hours of sunlight today (dynamic)

public:
    SolarFarm(const string& name, double maxOutput, double cost, double acres, double sunlightHours)
        : PowerPlant(name, PT_SOLAR, maxOutput, cost), numAcres(acres), sunlightHours(sunlightHours) {}

    // Dynamic sunlight affects output
    double calculateOutput() override;

    string getCurrentCondition() const override {
        return "Sunlight Hours: " + to_string(sunlightHours);
    }

    void setSunlightHours(double hours) { sunlightHours = hours; }
};


//******************************************************
//                  WindFarm Plant                 *****
//    Plant using a set of windmills (turbines)    *****
//******************************************************
class WindFarm : public PowerPlant {
private:
    int turbineCount;
    double avgWindSpeed;    // miles per hour
    double bladeLength;        // blade length

public:
    WindFarm(string& name, double maxPowerOutput, double cost, int turbines, double bladeLen, double windSpeed)
        : PowerPlant(name, PT_WIND,  maxPowerOutput, cost), turbineCount(turbines), bladeLength(bladeLength), avgWindSpeed(windSpeed) {}

    virtual double calculateOutput() override;

    string getCurrentCondition() const override {
        return "Average Wind Speed: " + to_string(avgWindSpeed) + " mph";
    }

    void setAvgWindSpeed(double speed) { avgWindSpeed = speed; }
};




//******************************************************
//                Hydro Electric Plant             *****
//******************************************************
class HydroPlant : public PowerPlant {
private:
    double inFlowRate;   // cubic meters/sec
    double verticalDrop; // meters

public:
    HydroPlant(const string& name, double maxOutput, double cost, double flowRate, double drop)
        : PowerPlant(name, PT_HYDRO, maxOutput, cost), inFlowRate(flowRate), verticalDrop(drop) {}

    double calculateOutput() override;

    string getCurrentCondition() const override {
        return "Flow: " + to_string(inFlowRate) + " m^3/s, Drop: " + to_string(verticalDrop) + " m";
    }

    void setFlowRate(double flow) { inFlowRate = flow; }
    void setVerticalDrop(double drop) { verticalDrop = drop; }
};

//******************************************************
//              Nuclear Electric Plant             *****
//******************************************************
class NuclearPlant : public PowerPlant {
private:
    int fuelRodsActive; // number of fuel rods

public:
    NuclearPlant(const string& name, double maxOutput, double cost, int rods)
        : PowerPlant(name, PT_NUCLEAR, maxOutput, cost), fuelRodsActive(rods) {}

    double calculateOutput() override;

    string getCurrentCondition() const override {
        return "Fuel Rods Active: " + to_string(fuelRodsActive);
    }

    void setFuelRods(int rods) { fuelRodsActive = rods; }
};


//******************************************************
//             Geothermal Electric Plant           *****
//******************************************************
class GeothermalPlant : public PowerPlant {
public:
    GeothermalPlant(const string& name, double maxOutput, double cost)
        : PowerPlant(name, PT_GEOTHERMAL, maxOutput, cost) {}

    double calculateOutput() override;

    // string getCurrentCondition() const override {
    //     return "Stable geothermal output";
    // }
};


//******************************************************
//                   Gas Fuel Plant                *****
// Plants using gas for fuel - natural, LP, Bio... *****
//******************************************************
class GasPlant : public PowerPlant {
private:
    string fuelType;
    double throttlePercent; // 0–100

public:
    GasPlant(const string& name, double capacity, double cost, const string& fuel, double throttlePer)
        : PowerPlant(name, PT_GAS, capacity, cost), fuelType(fuel), throttlePercent(throttlePer) {}

    double calculateOutput() override;

    string getCurrentCondition() const override {
        return "Fuel: " + fuelType + ", Throttle: " + to_string(throttlePercent) + "%";
    }

    void setThrottle(double throttle) { throttlePercent = throttle; }
    void setFuelType(const string& fuel) { fuelType = fuel; }
};


