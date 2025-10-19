#pragma once
// File: PowerGrid.h
//
// Contains class definition for the overall PowerGrid Object class
// 
// The PowerGrid class contains support, analysis, and modeling attribues 
// for the overall Grid
//
#include <vector>
#include <string>

#include "Plant.h"
#include "ServiceArea.h"
#include "TransmissionLine.h"

// Define the tolerance used for comparing floating point numbers
#define FP_ROUND(x) (x+double(0.001))


//
// Class PowerGrid
//
// This class is an aggregation of all the Plants, ServiceArea Locations, and
// Transmission Lines if the power Grid.   The information for each instance
// of these is stored in a vector in this class.
// 
// The class has functions to read a data file, add an instance to the grid,
// and print the components in the grid.
// 
// The class also has support and action function(s) includeiing:
//  1) Run a balancing routine to distribute power from the plants to
//     the locations over the transmission lines and track enrgy loss.
// 
//  2) Print a report of the distribution and effciency.
// 
//  Notes:  The initializeGrid function reads the data files for the objects and is
//          is in its own file initializeGrid.cpp.
// 
//          The plant, area, and line managment routines are in PowerGrid.cpp
// 
//          The distribute power function is in file distrubutePoer.cpp
// 
//          Most screen output and reports are in the file reports.cpp 
//
class PowerGrid {
private:
    // General information about the power grid
    string              gridName;
    static int          plantCount;   // Count of plants in the grid

    // Vectors containing instances of plants, demands, and transmission lines
    // ***** => In assignment 2 and beyond, the plant vector contains pointers to a plant object, not a plant object.  
    vector<PowerPlant*>      plants;
    vector<ServiceArea>      areas;
    vector<TransmissionLine>        transmissionLines;
    
    
    // Variables used for the power distribution algorithim
    int     linesHaveCapacity;      // Flag if any transmission lines have capacity
    int     plantsHaveCapacity;     // Flag if any areas have power avaialble
    int     areasRequirePower;      // Flag if any areas have unmet power requierments 
    int     nextLineIndex;          // Used to track what transLine to use




public:
    // Function called to read the data files and fill the data of the Grid
    int initializeGrid(const string gridName, const string plantFilename, const string TransLineFilename, const string AreaFilename);

    // Functions to add, remove, read data file, manage, and print the power plants
    void addPlantToGrid(PowerPlant* pPlant);
    int  readPlantData(const string& filename);
    void adjustPlantsForConditions();   // Calls each plant to adjust for unique conditions
    void printPlants() const;

    // Functions to add, remove, read data file, manage, and print the Service Area locations
    int  readServceAreaData(const string& filename);
    void addServiceArea(const string name, const double requiredCap, const double costPerMW);
    void printServceAreas() const;

    // Functions to add, remove, read data file, manage, and print the transmison lines
    int  readTransmissionLineData(const string& filename);
    void addTransmissionLine(int lineID, string lineName, double capacity, double efficiency);
    void printTransmissionLines() const;

    // Functions to distribute power : in file DistPower.cpp
    void distributePower(int percentOfRequired);    // Distributes power to the service areas
    void AllocatePowerToArea(ServiceArea& area, double powerRequested);  // Allocates power & line capacity to an area
    void generateUsageReport();                     // Generates a power report to the console
}; 

