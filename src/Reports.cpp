// File: Reports.cpp
// 
// Contains the functions for PowerGrid class to generate reports.
// 
// These functions are part of the PowerGrid class and declared in PowerGrid.h
// 
// 
//     
//
#include "PowerGrid.h"
using namespace std;


//***********************************************
//
// printServiceAreas()
//
//***********************************************
void PowerGrid::printServceAreas() const {

    // Variables to accumlate totals
    double reqTotal = 0;
    double supTotal = 0;
    double priceTotal = 0;


    // Print column headings
    cout << " Location      Demand     MW Price($)   Supplied   Total Price\n";
    cout << "----------    --------    -----------   --------   -----------\n";

    // Loop and print all information for each area.
???
}



//***********************************************
//
// printPlants()
//
//***********************************************
void PowerGrid::printPlants() const {

    // Variable to accumlate totals
    double maxTotal = 0;
    double curTotal = 0;
    double availTotal = 0;


    // Print column headings
    cout << "     Plant           Type       Max Cap      Cur Cap   Avail Cap\n";
    cout << "---------------    --------     --------    --------   ---------\n";

    // Loop and print all information for each Plant.
???
}



//***********************************************
// 
// printTransLines()
//
//***********************************************
void PowerGrid::printTransLines() const {

    // Variables to accumlate totals
    double maxTotal = 0;
    double remainTotal = 0;


    // Print column headings
    cout << " ID           Name         Efficiency    Capacity   Remaining\n";
    cout << "----   ------------------  ----------    --------   ---------\n";

    // Loop and print all information for each transLine.
???
}

//***********************************************
//
//      generateUsage Report()
//
//***********************************************
void PowerGrid::generateUsageReport() {
    double totalPowerRequested = 0;
    double totalPowerSupplied = 0;

    // Print Headings
    cout << "\t\t" << gridName << endl;
    cout << "\t\t -- Grid Simulation Report --" << endl;
    cout << "Location   | Required(MW) | Supplied(MW) | Percent |   Price    |" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    // Loop through Demands and print status of each demand location
    for (auto& area : areas) {
        double powerRequired = area.getPowerRequired();    // Power the area needs
        double powerProvided = area.getPowerProvided();    // Power that the Grid could supply
        double percentProvided = powerProvided / powerRequired;
        double powerPrice = area.getTotalPriceForPower();

        // Print out the demand inforamtion
        cout << std::setw(10) << std::left << area.getAreaName() << " | "
            << std::setprecision(2) << std::setw(12) << std::right << powerRequired << " | "
            << std::setprecision(2) << std::setw(12) << std::right << powerProvided << " | "
            << std::setprecision(2) << std::setw(5) << std::right << percentProvided << "%  | "
            << std::setprecision(2) << std::setw(10) << std::right << powerPrice << " | "
            << endl;

        // Collect the total requested and supplied Demand
        totalPowerRequested += powerRequired;
        totalPowerSupplied += powerProvided;
    }

    // Loop through the plants and total how much capacity was used.
    double totalPlantUsage = 0;
    for (auto& plant : plants) {
        double plantUsage = plant->getCapacityAllocated();
        totalPlantUsage += plantUsage;
    }

    cout << endl << endl << "Overall Grid Performance:" << endl;
    cout << "    Total Demand Request:  " << totalPowerRequested << " MW" << endl;
    cout << "    Total Demand supplied: " << totalPowerSupplied << " MW" << endl;
    cout << "    Percent of demand met: " << (totalPowerSupplied / totalPowerRequested) << "%" << endl;
    cout << endl;
    cout << "    Plant Capacity used:   " << totalPlantUsage << " MW" << endl;
    cout << "    Average Delivery Efficiency %: " << (totalPowerSupplied / totalPlantUsage) << endl;


    //
    // Determine the profit or loss for operating the grid
    //
    ???
}
