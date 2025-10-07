#pragma once
//
// File: GridDef.h
// Description: Contains all constants and configuration parameters
//              for the PowerGrid simulation
//

#include <string>

// Name of company that owns the power grid
const std::string GRID_NAME = "Rich's Amazing Energy Grid";

// Filenames for data input and reports
const std::string AREA_FILENAME       = "A2_ServiceAreas.txt"; 
const std::string PLANTS_FILENAME     = "A2_Plants.txt";
const std::string TRANSLINES_FILENAME = "A2_TransLines.txt";
const std::string REPORT_FILENAME     = "A2_Report.txt";

// Plant type identifiers (used when reading data files)
const std::string PT_SOLAR       = "Solar";
const std::string PT_WIND        = "Wind";
const std::string PT_HYDRO       = "Hydro";
const std::string PT_GAS         = "Gas";
const std::string PT_NUCLEAR     = "Nuclear";
const std::string PT_GEOTHERMAL  = "GeoTherm";

// File header delimiter (used in data files)
const std::string FILE_HEADER_DELIMITER = "&*****&";

// Transmission line constants
const int MAX_LINE_CONNECTIONS = 4;   // Maximum connections per line

// Environmental / plant-specific limits
const double MAX_SUNLIGHT_HOURS = 12.0;  // Maximum possible sunlight hours per day
const double MAX_WIND_SPEED      = 25.0; // Maximum wind speed used for output calculations
const int    MAX_FUEL_RODS       = 100;  // Maximum fuel rods for nuclear plants

// Optional: default values for new simulation features
const double DEFAULT_EFFICIENCY  = 95.0; // Default efficiency for transmission lines (%)
const double DEFAULT_THROTTLE    = 100.0; // Default throttle % for gas plants






