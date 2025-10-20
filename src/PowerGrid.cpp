// File: PowerGrid.cpp
// 
// Contains the function code for the overall PowerGrid class
// 
// This class contains the plants, demands, and lines of the grid and
// this file contains member functions for reading, inserting, and 
// printing the key components of the grid.
//
//
//  Note: Many functions for the PowerGrid have been grouped in separte files
//        based on functionality.  These are:
//            InitializeGrid.cpp:  Contains functions to read the data files and initalize the Grid state
//            DistributePower.cpp: Contains the function(s) to perform the modeling algorithim.
// 
#include <cassert>
#include "../header/PowerGrid.h"

using namespace std;

//********************************************************
//*****       Static Variable for Power Plants       *****
//********************************************************
int PowerGrid::plantCount = 0;


//********************************************************
//*****        Functions for Power Plants            *****
//********************************************************

//
// addPlantToGrid() Adds a new plant to the grid.  
//          Receives a reference to a plant object and places it plant vector 
//
void PowerGrid::addPlantToGrid(PowerPlant* pPlant) {
    // Insert the pointer to the plant into the vector and increment count
    plants.push_back(pPlant);
    plantCount++;
}

//
// adjustPlantsForConditions():  Adjust the available capacity of each plant by
//                      calling each plants virtual function calculateOutput.
//
void PowerGrid::adjustPlantsForConditions() {
    // In assignment 2 and beyond, the plant vector contains pointers to a
    // plant object, not a plant object.   When we itereate, the iteration variable
    // is a pointer so need to use the -> notation instead of the . notation.

    // Loop and call the calculateOutput for each plant.
    for (const auto& plant : plants) {
        plant->calculateOutput();
    }
}

//********************************************************
//*****         Functions for Service Areas          *****
//********************************************************

//
// addServiceArea()
//
void PowerGrid::addServiceArea(const string name, const double requestedCap, const double costPerMW) {
 
    // Declare a new local object and have constructor set the values.
    ServiceArea newSvcArea (name, requestedCap, costPerMW);
    
    // Insert into vector
    areas.push_back(newSvcArea);
}

//********************************************************
//*****      Functions for Transmission Lnes         *****
//********************************************************

//
// addTransLine()
//
void PowerGrid::addTransmissionLine(int lineID, string lineName, double capacity, double efficiency) {
    
    // Declare Transmissionline object and have constructor set the values.
    TransmissionLine newTransmissionLine(lineID, lineName, capacity, efficiency);

    // Insert into vector
    transmissionLines.push_back(newTransmissionLine);
}