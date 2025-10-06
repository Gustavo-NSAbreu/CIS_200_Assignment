#pragma once
// File: Plant.h
//
// Contains class definition for the power Plant class
//
// Plants generate the electricity and supply it to demand location 
// using transmission lines.
//
// Plants have varying characteriscs such as Fuel Type, Capacity, Age, 
// cost to produce electricty, hours of operation, and environmental 
// impact.
//
// Plants understand their total capacity and track how much power
// has already been committed and the amount available to provide.
// 

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
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
    string  plantName;
    string  type;
    double  maxCapacity = 0.0;        // The absolute maximum capacity of the plant
    double  curCapacity = 0.0;        // The current capacity of the plant based weather, rain,..
    double  availCapacity = 0.0;      // The capacity that is avaiable for demand locations. (not already allocated)
    double  costPerMW = 0.0;          // Average cost to produce including capital costs
    
public:
    // Constructors & Destructors
    PowerPlant(const string& name, const string& type, const double cost, const double maxCapacity);
    //virtual ~Plant();                 // Virtual destructor

    // Mutators
    void reduceCapacity(double amount);         // Reduce the available capacity for the plant when it is allocated to a location
    double  getCapacityAllocated() const;       // Retruns capacity already allocated to areas
    double  getCostOfAllocatedPower() const;    // returns cost of the power to allocated to areas
    virtual double calculateOutput() = 0;       // Pure virtual function for calculating output today
    virtual string getCurConditions() const { return "Normal";} // Returns string with current conditons at plant - Each type should override

  
    // Getters and Setters
    string getPlantName() const { return plantName; }
    string getType() const { return type; }
    double getMaxCapacity() const { return maxCapacity; }
    double getCurCapacity() const { return curCapacity; }
    double getAvailCapacity() const { return availCapacity; }
    double getCostPerMW() const { return costPerMW; }
 
    

    // Print and debug 
    virtual void printAll() const;          // Prints all the information for the plant

};



//******************************************************
//                  Solar Plant                    *****
//******************************************************
//
class SolarFarm : public PowerPlant {
private:
    double numAcres;        // Land size of solar farm in acres
    double sunlightHours;   // Daily sunlight hours

public:
    // Constructors and Destructors
    SolarFarm(const string& name, double maxCapacity, double costPerMW, double numAcres, double sunlightHours);

    double calculateOutput() override;                  // Calculate output for this plant
    virtual string getCurConditions() const override;   // Get current conditons at plant
};

//******************************************************
//                  WindFarm Plant                 *****
//    Plant using a set of windmills (turbines)    *****
//******************************************************
class WindFarm : public PowerPlant {
private:
    int     turbineCount;   // Number of turbines
    double  bladeLen;       // Length of each blade (in feet)
    double  avgWindSpeed;   // Average wind speed in miles/hrs

public:
    // Constructors and Destructors
    WindFarm(string& name, double maxCapacity, double cost, int turbines, double bladeLen, double windSpeed);

    double calculateOutput() override;          // Calculate output for this plant
    string getCurConditions() const override;   // Get current conditons at plant
};



//******************************************************
//                Hydro Electric Plant             *****
//******************************************************
class HydroPlant : public PowerPlant {
    double  inFlowRate;         // Water inflow (cubic meters per second)
    double  verticalDrop;       // Drop for water to drive the generators (meters)

public:
    // Constructors and Destructors
    HydroPlant(const string& name, double maxCapacity, double cost, double flowRate, double(drop));

    double calculateOutput() override;              // Calculate output for this plant
    string getCurConditions() const override;       // Get current conditons at plant
};


//******************************************************
//              Nuclear Electric Plant             *****
//******************************************************
class NuclearPlant : public PowerPlant {
    int     fuelRodsActive;     // Number of fuel rods inserted in the reactor

public:
    // Constructors and Destructors
    NuclearPlant(const string& name, double maxCapacity, double cost, int fuelRodCount);

    double calculateOutput() override;                  // Calculate output for this plant
    virtual string getCurConditions() const override;   // Get current conditons at plant
};

//******************************************************
//             Geothermal Electric Plant           *****
//******************************************************
class GeothermalPlant : public PowerPlant {
    // No plant specific varaibles - at this time :-)

public:
    // Constructors and Destructors
    GeothermalPlant(const string& name, double maxCapacity, double cost);

    double calculateOutput() override;                  // Calculate output for this plant
    virtual string getCurConditions() const override;   // Get current conditons at plant
};


//******************************************************
//                   Gas Fuel Plant                *****
// Plants using gas for fuel - natural, LP, Bio... *****
//******************************************************
class GasPlant : public PowerPlant {
    string      fuelType;           // Type of fuel (coal, naturalgas, ...)
    double      throttlePercent;    // Percent opening of throttle (0.0 - 100.0)

public:
    // Constructors and Destructors
    GasPlant(const string& name, double capacity, double cost, const string& fuel, double throttlePer);

    double calculateOutput() override;                  // Calculate output for this plant
    virtual string getCurConditions() const override;   // Get current conditons at plant
};


