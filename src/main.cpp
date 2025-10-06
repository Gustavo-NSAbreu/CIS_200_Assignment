//
// File:  main.cpp
//
// This file contains the main() for the CIS200 F5 Power Grid assignment
// 
// It instantiates a PowerGrid type called myGrid.  The grid reads data
// files containing configurations of Plants, Service Area locations, 
// and transmission lines.  The plants, areas, and lines have varying
// levels of capacity, need, and efficiencies.
//
// The grid then calls a function to distribute the energy from the plants
// to the demand locations using the transmission lines.  All of the data
// is received in a sorted order and the distribution follows a simple
// algorithm.
//
// After the distribution, a well formatted report is produced showing
// various usage and efficiency characteristics of the power grid.
// 
// This project was designed by Richard Frost - UMich Dearborn.
// Please contact for permission to reuse!
//

#include "GridDef.h"
#include "PowerGrid.h"
#include <iostream>
#include <direct.h>     // For _getcwd in Windows
using namespace std;



//
// main():  Main function for Power Grid project
//
int main() {
    PowerGrid myGrid;   // The PowerGrid used throughout the program
    int rc;             // return code used throughout this function

    // Use this to print the directory the data files should be in
#if 1
    char cwd[256];
    bool x = _getcwd(cwd, sizeof(cwd));
    cout << "Current working directory: " << cwd << endl;
#endif


    // Initialize the Grid with values from the configuration data files
    rc = myGrid.initializeGrid(GRID_NAME, AREA_FILENAME, PLANTS_FILENAME, TRANSLINES_FILENAME);
    if (rc != 0) {
        cout << endl << "Grid Initilization Failed!  Status code:" << rc << endl << endl;
    }

        
    // Display the initial state of the Grid
    cout << "\t--- Initial Service Area Summary ---\n";
    myGrid.printServceAreas();
    
    cout << "\n\n\t--- Initial Power Plant Summary ---\n";
    myGrid.printPlants();   
     
    cout << "\n\n\t--- Initial Transmission Line Summary ---\n";
    myGrid.printTransLines();
    

    // Have each plant adjust for the conditions of the plant (Sunlight, Rain, Temperature, ...)
    myGrid.adjustPlantsForConditions();
    cout << "\n\n\t\t\t--- Power Plant Current Condition Summary ---\n";
    myGrid.printPlants();

    
    // Distribute power from plants to all areas using differnet allocation percentages
    cout << "\n\t--- Allocating power to the Service Areas ---\n";
    myGrid.distributePower(60);
    myGrid.distributePower(10);
    myGrid.distributePower(10);
    myGrid.distributePower(10);
    myGrid.distributePower(10);



    // Display the final state of the Grid
    cout << "\n\n\t--- Final Service Area Summary ---\n";
    myGrid.printServceAreas();

    cout << "\n\n\t--- Final Power Plant Summary ---\n";
    myGrid.printPlants();

    cout << "\n\n\t--- Final Transmission Line Summary ---\n";
    myGrid.printTransLines();

    // Generate report on usage and efficiency
    cout << endl << endl;
    myGrid.generateUsageReport();


    return 0;
}
