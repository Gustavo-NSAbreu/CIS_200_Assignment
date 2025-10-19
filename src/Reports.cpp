// File: Reports.cpp
// 
// Contains the functions for PowerGrid class to generate reports.
// 
// These functions are part of the PowerGrid class and declared in PowerGrid.h
// 
// 
//     
//
#include "../header/PowerGrid.h"

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
    for (const auto& area : areas) {
        string areaName =  area.getAreaName();
        double powerRequired = area.getPowerRequired();
        double powerProvided = area.getPowerProvided();
        double totalPriceForPower = area.getTotalPriceForPower();
        double mwPrice = area.getMWPrice();

        // Print out the area information
        cout << setw(10) << left << areaName << "   "
            << fixed << setprecision(2) << setw(9) << right << powerRequired << "   "
            << setw(12) << right << mwPrice << "   "
            << setw(8) << right << powerProvided << "   "
            << setw(11) << right << totalPriceForPower << endl;

        // Total sum
        reqTotal += powerRequired;
        supTotal += powerProvided;
        priceTotal += totalPriceForPower;
    }
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
    cout << "     Plant            Type      Max Cap     Cur Cap    Avail Cap\n";
    cout << "---------------     --------   ---------   ---------  -----------\n";

    // Loop and print all information for each Plant.
    for (const auto& plant : plants) {
        string plantName = plant->getName();
        string plantType = plant->getType();
        double maxCapacity = plant->getMaxPowerOutput();
        double currentOutput = plant->getCurrentOutput();
        double availableCapacity = plant->getAvailableCapacity();

        // Print out the plant information
        cout << setw(17) << left << plantName << "   "
            << setw(8) << left << plantType << "   "
            << fixed << setprecision(2) << setw(9) << right << maxCapacity << "   "
            << setw(9) << right << currentOutput << "   "
            << setw(10) << right << availableCapacity << endl;

        // Total sum
        maxTotal += maxCapacity;
        curTotal += currentOutput;
        availTotal += availableCapacity;
    }
}



//***********************************************
// 
// printTransmissionLines()
//
//***********************************************
void PowerGrid::printTransmissionLines() const {

    // Variables to accumlate totals
    double maxTotal = 0;
    double remainTotal = 0;


    // Print column headings
    cout << " ID           Name           Efficiency    Capacity   Remaining\n";
    cout << "----   ------------------    ----------    --------   ---------\n";

    // Loop and print all information for each transmission line.
    for (const auto& line : transmissionLines) {
        int lineID = line.getLineID();
        string lineName = line.getLineName();
        double efficiency = line.getEfficiency();
        double capacity = line.getMaxCapacity();
        double remainingCapacity = line.getRemainingCapacity();

        cout << setw(4) << left << lineID << "   "
            << setw(17) << left << lineName << "   "
            << fixed << setprecision(2) << setw(12) << right << efficiency << "   "
            << fixed << setprecision(0) << setw(9) << right << capacity << "   "
            << fixed << setprecision(0) << setw(9) << right << remainingCapacity << endl;

        // Total sum
        maxTotal += capacity;
        remainTotal += remainingCapacity;
    }
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
        cout << setw(10) << left << area.getAreaName() << " | "
            << fixed << setprecision(2) << setw(12) << right << powerRequired << " | "
            << fixed << setprecision(2) << setw(12) << right << powerProvided << " | "
            << fixed << setprecision(2) << setw(5) << right << percentProvided << "%  | "
            << fixed << setprecision(2) << setw(10) << right << powerPrice << " | "
            << endl;

        // Collect the total requested and supplied Demand
        totalPowerRequested += powerRequired;
        totalPowerSupplied += powerProvided;
    }

    // Loop through the plants and total how much capacity was used.
    double totalPlantUsage = 0;
    for (auto& plant : plants) {
        double plantUsage = plant->getCurrentOutput();
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
    //???
}
