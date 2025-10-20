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

    // Print totals
    cout << "-- Total --" << "   "
        << fixed << setprecision(2) << setw(8) << right << reqTotal << "   "
        << setw(23) << right << supTotal << "   "
        << setw(11) << right << priceTotal
        << endl;
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
            << setw(10) << right << availableCapacity << "   "
            << left << plant->getCurrentCondition() << endl;

        // Total sum
        maxTotal += maxCapacity;
        curTotal += currentOutput;
        availTotal += availableCapacity;
    }

    // Print totals
    cout << "-- Total --" << "   "
        << fixed << setprecision(2) << setw(26) << right << maxTotal << "   "
        << setw(9) << right << curTotal << "   "
        << setw(10) << right << availTotal << "   "
        << endl;
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

    // Print totals
    cout << "       -- Total --" << "   "
        << fixed << setprecision(0) << setw(30) << right << maxTotal << "   "
        << setw(9) << right << remainTotal << endl;
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
        double percentProvided = powerProvided / powerRequired * 100; // Percent of power supplied
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
        totalPlantUsage += plant->getCapacityAllocated();;
    }

    cout << endl << endl << "Overall Grid Performance:" << endl;
    cout << "    Total Demand Request:  " << totalPowerRequested << " MW" << endl;
    cout << "    Total Demand supplied: " << totalPowerSupplied << " MW" << endl;
    cout << "    Percent of demand met: " << (totalPowerSupplied / totalPowerRequested) * 100 << "%" << endl;
    cout << endl;
    cout << "    Plant Capacity used:   " << totalPlantUsage << " MW" << endl;
    cout << "    Average Delivery Efficiency %: " << (totalPowerSupplied / totalPlantUsage) * 100 << endl;
    cout << endl << endl;

    //
    // Determine the profit or loss for operating the grid
    //

    double grossPay = 0.0;
    double totalCost = 0.0;
    double profit = 0.0;

    // Loop through each area to total up the gross payment
    for (const auto& area : areas) {
        grossPay += area.getTotalPriceForPower();
    }

    // Loop through each plant to total up the operating cost
    for (const auto& plant : plants) {
        totalCost += plant->getCostOfAllocatedPower();
    }

    // Determine profit
    profit = grossPay - totalCost;

    cout << "Total price by all areas paid for power they used today: $" << grossPay << endl;
    cout << "Total cost of producing this power: $" << totalCost << endl;
    cout << "Operating profit for my Power Grid today: $" << profit << endl;

}