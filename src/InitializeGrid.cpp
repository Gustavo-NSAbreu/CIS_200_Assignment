// File: InitializeGrid.cpp
// 
// Contains the function code to read the data files and initialize Grid.
// This is currently a public member function of the PowerGrid class and 
// it primarily uses private member functions of the Grid class.
// 
#include "../header/GridDef.h"
#include "../header/PowerGrid.h"
#include <cassert>

using namespace std;

//*******************************************************
//*****       Grid Initilization Function           *****
//*******************************************************
int PowerGrid::initializeGrid(const string name, 
    const string demandFilename, const string plantFilename, const string transLineFilename) {
    
    int rc;     // muilt-use return Code

    cout << "Grid initialization beginning for " << name << endl;
    gridName = name;
        
    // Read the data files and populate the vector for each major object 
    rc = readServceAreaData(demandFilename);
    if (rc != 0)  return rc;
    cout << "Demand data successfully completed." << endl;
     
    rc = readPlantData(plantFilename);
    if (rc != 0)  return rc;
    cout << "Plant data successfully completed." << endl;

    rc = readTransmissionLineData(transLineFilename);
    if (rc != 0)  return rc;
    cout << "Transmission Line data successfully completed." << endl;

    cout << endl;
    return 0;
}



//********************************************************
//*****               Service Area                   *****
//********************************************************

//
//  readServiceAreaData():   Reads the information about each service area
//             from the data file and adds them to the grid
//
int PowerGrid::readServceAreaData(const string& filename) {

    // Variables used to read demand info from file
    string  location;
    double  requestedPower;
    double  mwPricePaid;

    // Declare input stream and open data file for reading
    ifstream isDemand(filename);
    if (!isDemand) {
        cerr << "Error: Unable to open file " << filename << endl;
        return -1;
    }

    // Read and skip the two header lines
    string  headerLine;
    getline(isDemand, headerLine);
    getline(isDemand, headerLine);

    // Read the first demand record
    isDemand >> location >> requestedPower >> mwPricePaid;

    // Process all records in the file 
    while (!isDemand.eof() && !isDemand.fail()) {

        // Add the demand location and required capacity to the grid
        addServiceArea(location, requestedPower, mwPricePaid);

        // Read next record
        isDemand >> location >> requestedPower >> mwPricePaid;
    }

    isDemand.close();
    return 0;
}


//********************************************************
//*****               Power Plants                   *****
//********************************************************

//
//  readPlantData():   Reads the information about each plant from the data
//                  file and adds them to the grid
//
int PowerGrid::readPlantData(const string& filename) {
 
    // Variables used to read demand info from file
    string name, type;
    double costPerMW = 0.0;
    double maxOutput = 0.0;

    // Declare input stream and open data file for reading
    ifstream isPlant(filename);
    if (!isPlant) {
        cerr << "Error: Unable to open Plant file " << filename << endl;
        return -1;
    }

    // Lambda function to read first 3 fields of a line into local variables
    auto readLineFromFile = [&]() {
        isPlant >> std::ws;     // Skip all leading whitespace
        getline(isPlant, name, ',');

        // Read the remainder of the values on the line
        isPlant >> type >> maxOutput >> costPerMW;
    };
 
    /// Skip the informational header linesat start of file
    string headerLine;
    do {
        getline(isPlant, headerLine);
    } while (headerLine != FILE_HEADER_DELIMITER);


    // Read the first line of file into local variables using local lambda function
    readLineFromFile();       

    // Process all records in the file 
    while (!isPlant.eof() && !isPlant.fail()) {

        // Read the rest of the data depending on the type of the plant and add theplant to the grid
        if (type == PT_SOLAR) {
            double numAcres, sunlightHours;

            // Read additional fields and declare solar farm
            isPlant >> numAcres >> sunlightHours;
            
            // Allocate a solar farm object with information read
            SolarFarm *pSolar = new SolarFarm(name, maxOutput, costPerMW, numAcres, sunlightHours);
            addPlantToGrid(pSolar);
        }

        else if (type == PT_WIND) {
            int turbineCnt;
            double windSpeed;
            double bladeLen;

            // Read additional fields and declare wind farm
            isPlant >> turbineCnt >> bladeLen >> windSpeed;

            // Allocate a wind farm object with information read
            WindFarm *pWind = new WindFarm(name, maxOutput, costPerMW, turbineCnt, bladeLen, windSpeed);
            addPlantToGrid(pWind);
        }

        else if (type == PT_HYDRO) {
            double flowRate;
            double drop;

            // Read additional fields and declare hydro plant
            isPlant >> flowRate >> drop;

            // Allocate a hydro plant object with information read
            HydroPlant *pHydro = new HydroPlant(name, maxOutput, costPerMW, flowRate, drop);
            addPlantToGrid(pHydro);
        }

        else if (type == PT_NUCLEAR) {
            int fuelRodsInUse;

            // Read additional fields and declare nuclear plant
            isPlant >> fuelRodsInUse;

            // Allocate a nuclear plant object with information read
            NuclearPlant* pNuclear = new NuclearPlant(name, maxOutput, costPerMW, fuelRodsInUse);
            addPlantToGrid(pNuclear);
        }

        else if (type == PT_GEOTHERMAL) {
            // Allocate a geothermal plant object with information read
            GeothermalPlant* pGeothermal = new GeothermalPlant(name, maxOutput, costPerMW);
            addPlantToGrid(pGeothermal);
        }

        else if (type == PT_GAS) {

            string fuelType;
            double throttlePercent;
            isPlant >> fuelType >> throttlePercent;

            // Allocate a gas plant object with information read
            GasPlant* pGas = new GasPlant(name, maxOutput, costPerMW, fuelType, throttlePercent);
            addPlantToGrid(pGas);
        }


        else {
            cerr << "\nUnkown plant type found: " << type << endl;
            assert(false);
        }
        
        // Read the next line of the file using local lambda function
        readLineFromFile();        
    }

    // Close the file and return
    isPlant.close();
    return 0;
 }




//********************************************************
//*****             Transmission Lines               *****
//********************************************************

//
//  readTransLineData():   Reads the information about each transLine 
//              from the data file and adds them to the grid
//
int PowerGrid::readTransmissionLineData(const string& fileName) {

    // Variables used to read transmission line info from file
    int     lineID = 0;
    string  lineName;
    double  lineCapacity = 0.0;
    double  efficiency = 0.0;
    string  temp;


    // Declare input stream and open data file for reading
    ifstream isTransmissionLine(fileName);
    if (!isTransmissionLine) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return -1;
    }


    // Read and skip the header lines until the delimiter is econtered
    string headerLine;
    do {
        getline(isTransmissionLine, headerLine);
    } while (headerLine != FILE_HEADER_DELIMITER);
 


    // Lambda function to read a line from file and parse into local varaibles
    auto readLineFromFile = [&]() {

        isTransmissionLine >> lineID;    // first field is Line ID (an integer)

        // The name of line may be multiple words - read until we get a digit
        isTransmissionLine >> lineName;        // Read first word
        isTransmissionLine >> temp;            // Read next info in the file
        while (!isdigit(temp[0])) {     // If it does not start with a digit it is part of the name
            lineName = lineName + " " + temp;
            isTransmissionLine >> temp;

            if (isTransmissionLine.fail())     // Check if something went wrong in the stream
                return;
        }

        // The value in temp is the value for capacity
        lineCapacity = stod(temp);

        // Last value on line is the efficiency
        isTransmissionLine >> efficiency;
     };

    // Read the first transLine record from the file using lambda function
    readLineFromFile();
    
    // Process the records in the file 
    while (!isTransmissionLine.eof() && !isTransmissionLine.fail()) {

        addTransmissionLine(lineID, lineName, lineCapacity, efficiency);

        // Read the next line of the file using local lambda function
        readLineFromFile();
    }

    isTransmissionLine.close();
    return 0;
}
