// File: InitializeGrid.cpp
// 
// Contains the function code to read the data files and initialize Grid.
// This is currently a public member function of the PowerGrid class and 
// it primarily uses private member functions of the Grid class.
// 
#include "GridDef.h"
#include "PowerGrid.h"
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

    rc = readTransLineData(transLineFilename);
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
    double maxCapacity = 0.0;

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
        isPlant >> type >> maxCapacity >> costPerMW;
    };
 
    /// Skip the informational header linesat start of file
    string headerLine;
    do {
        getline(isPlant, headerLine);
    } while (headerLine != FILE_HEADER_DELIMTER);


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
            SolarFarm *pSolar = new SolarFarm(name, maxCapacity, costPerMW, numAcres, sunlightHours);
            addPlantToGrid(pSolar);
        }

        else if (type == PT_WIND) {
            int turbineCnt;
            double windSpeed = 0.0;
            double bladeLen = 0.0;
 ???
        }

        else if (type == PT_HYDRO) {
            double flowRate = 0.0;
            double drop = 0.0;
 ???
        }

        else if (type == PT_NUCLEAR) {
            int     fuelRodsInUse;
            isPlant >> fuelRodsInUse;
???
        }

        else if (type == PT_GEO_THERMAL) {
            GeothermalPlant* pGeo = new GeothermalPlant(name, maxCapacity, costPerMW);
???
        }

        else if (type == PT_GAS) {
???
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
int PowerGrid::readTransLineData(const string& fileName) {

    // Variables used to read transLine info from file
    int     lineID = 0;
    string  lineName;
    double  lineCapacity = 0.0;
    double  efficiency = 0.0;
    string  temp;


    // Declare input stream and open data file for reading
    ifstream isTransLine(fileName);
    if (!isTransLine) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return -1;
    }


    // Read and skip the header lines until the delimiter is econtered
    string headerLine;
    do {
        getline(isTransLine, headerLine);
    } while (headerLine != FILE_HEADER_DELIMTER);
 


    // Lambda function to read a line from file and parse into local varaibles
    auto readLineFromFile = [&]() {

        isTransLine >> lineID;    // first field is Line ID (an integer)

        // The name of line may be multiple words - read until we get a digit
        isTransLine >> lineName;        // Read first word
        isTransLine >> temp;            // Read next info in the file
        while (!isdigit(temp[0])) {     // If it does not start with a digit it is part of the name
            lineName = lineName + " " + temp;
            isTransLine >> temp;

            if (isTransLine.fail())     // Check if something went wrong in the stream
                return;
        }

        // The value in temp is the value for capacity
        lineCapacity = stod(temp);

        // Last value on line is the efficiency
        isTransLine >> efficiency;
     };

    // Read the first transLine record from the file using lambda function
    readLineFromFile();

    // Process the records in the file 
    while (!isTransLine.eof() && !isTransLine.fail()) {

 ???
    }

    isTransLine.close();
    return 0;
}
