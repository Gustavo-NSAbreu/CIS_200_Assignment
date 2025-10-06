#pragma once
//
// File:  GridDef.h
//
// This file contains the constants and sizing parameters for the PowerGrid 
#include <string>


// Name of company that owns the power grid
const std::string GRID_NAME = "Rich's Amazing Energy Grid";

// Filenames and/or Location Constants
// Filenames and/or Location Constants
const std::string AREA_FILENAME = "A2_ServiceAreas.txt"; 
const std::string PLANTS_FILENAME = "A2_Plants.txt";
const std::string TRANSLINES_FILENAME = "A2_TransLines.txt";
const std::string REPORT_FILENAME = "A2_Report.txt";

// Plant information - used to determine plant type and read plant data file
const std::string PT_SOLAR = "Solar";
const std::string PT_WIND = "Wind";
const std::string PT_HYDRO = "Hydro";
const std::string PT_GAS = "Gas";
const std::string PT_NUCLEAR = "Nuclear";
const std::string PT_GEO_THERMAL = "GeoTherm";

const std::string FILE_HEADER_DELIMTER = "&*****&";

// Constansts used by Transmission line
const int	MAX_LINE_CONNECTIONS = 4;






