// File: DistPower.cpp
// 
// Contains the functions for Power Distribution functions of the PowerGrid class
// 
// These functions implement algorithms for analyzing demand, capacity, 
// grid topology, efficiency, and environmental impact to satisfy power
// demands.

// The algorithm is to repeatedly loop through each demand location and check if it has
// outstanding power requirements.  If so, it calls the tryToAllocatePower function.  That
// function searches for a power plant with power, uses the next available transmission line 
// and supplies power from the plant to the demand location. 
//
// There are 3 conditions that cause  the algorithm to terminate:
//  1) All demand locations have all their power requirements completly fulfilled
//  2) The power plants have allocated all of their power so no more can be fulfilled
//  3) The transmission lines are saturated  so they cannot carry and additional power.
//       
//
#include "../header/PowerGrid.h"

using namespace std;

//
// distributePower(int percentRequested): Distributes power to all service areas
// 
// 
//
// This is the fuction called to initiate the power distrubution algorithm. 
// It setsp up the control variables and loops until one of the algorithm termination
// conditions becomes true.
// 
//  percentRequested is the ammount of an area's power needs we try to allocate. 
// 
void PowerGrid::distributePower(int areaPercentage) {

    // Print status message
    cout << endl << "Distributing power based on " << areaPercentage << "% allocation." << endl;

    // Setup inital conditions in control variable in PowerGrid object
    plantsHaveCapacity = 1;
    linesHaveCapacity = 1;
    
    // Loop through each service area and check if it needs power
    for (auto& area : areas) {

        // Check if this location requires more power and allocate power to it
        if (area.getPowerDeficit() > FP_ROUND(0)) {

            // The amount of power to request for this area is either the 
            // requested percent of its needs or the amount to fulfill 
            // its total power needs,(i.e  powerDeficit), whichever is smaller 
            double percentOfRequested = area.getPowerRequired() * areaPercentage / 100.0;
            double deficit = area.getPowerDeficit();
            double power = min(percentOfRequested, deficit);

            // Try to find and deliver power for the area
            allocatePowerToArea(area, power);
        }

    } // for

}


//
//  AllocatePowerToArea()
// 
// Allocates power and line capacity to a service area from a single plant using a 
// single line.  If a plant and line cannot be found, then the area is deemed to only
// have partial power neds met.
// 
void PowerGrid::allocatePowerToArea(ServiceArea &area, double powerRequested) {

    // Display initial request.
    cout << std::setw(12) << std::left << area.getAreaName()
         << " is requesting " 
         << std::right << std::setprecision(2)<< std::setw(6) << powerRequested << " mw.  ";

 
    // Find the transmission line to use, In Assgin-2 we search the lines in the order
    // provided and use the first one that has the capacity to carry the power need.
    TransmissionLine* pCurLine = NULL;

    for (auto& line : transmissionLines) {
        if (line.getRemainingCapacity() >= powerRequested) {
            pCurLine = &line; // Found a line with capacity
            break;
        }
    }

    // Check if no line has any avaialble capacity
    if (pCurLine == NULL) {
        linesHaveCapacity = false;     // Set flag that no plants have capacity
        cout << "No Lines have capacity" << endl;
        return;
    }


    // Adjust the amount of power required based on the transmission line efficency
    double plantPowerRequested = powerRequested * pCurLine->getEfficiency();

    // Search the plants to find the first plant that has enough power to provide
    PowerPlant* pCurPlant = NULL;
    for (auto& plant : plants) {
        if (plant->getAvailableCapacity() >= plantPowerRequested) {
            pCurPlant = plant; // Found a plant with capacity
            break;
        }
    }

    // Check if no power plants had any avaialble capacity
    if (pCurPlant == NULL) {
        plantsHaveCapacity = 0;     // Set flag that no plants have capacity
        cout << "No Plants have capacity" << endl;
        return;
    }


    // We located a line and plant - allocate to power to the area and adjust levels
    cout << "Allocating: "
        << setprecision(2) << setw(6) << right << plantPowerRequested
        << " mw from " << setw(17) << left << pCurPlant->getName()
        << " On: " << pCurLine->getLineID()
        << ", " << pCurLine->getLineName()
        << endl;


    // Allocate the power to the area by adjusting the plant, area, and line capacities
    area.addCapacity(plantPowerRequested);                   // Add the power capacity to the area
    pCurPlant->reduceCapacity(powerRequested);    // Reduce the plant's avaiable capacity
    pCurLine->reduceCapacity(plantPowerRequested);           // Reduce the avaiable capacity of the line
}

