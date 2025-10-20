
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
    double availableCapacity = 0.0; // Available output (MW)

public:
    // Constructors & Destructors
    PowerPlant(const string& name, const string& type, double maxPowerOutput, double cost)
        : name(name), type(type), maxPowerOutput(maxPowerOutput), operatingCost(cost), currentOutput(0.0), availableCapacity(0.0) {}

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
    double getAvailableCapacity() const { return availableCapacity; }

    void reduceCapacity(double amount);
    double getCapacityAllocated() const;
    double getCostOfAllocatedPower() const;
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

    string getCurrentCondition() const override;

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
        : PowerPlant(name, PT_WIND,  maxPowerOutput, cost), turbineCount(turbines), bladeLength(bladeLen), avgWindSpeed(windSpeed) {}

    double calculateOutput() override;

    string getCurrentCondition() const override;

    double getBladeLength() const { return bladeLength; }
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

    string getCurrentCondition() const override;

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

    string getCurrentCondition() const override;

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

    string getCurrentCondition() const override;
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

    string getCurrentCondition() const override;

    void setThrottle(double throttle) { throttlePercent = throttle; }
    void setFuelType(const string& fuel) { fuelType = fuel; }
};