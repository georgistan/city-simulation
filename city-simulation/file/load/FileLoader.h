// #include "../../city/City.h"
// #include "../../building/Building.h"
// #include "../../building/CentralBuilding.h"
// #include "../../building/OrdinaryBuilding.h"
// #include "../../building/PeripheralBuilding.h"
// #include "../../citizen/Citizen.h"
// #include "../../citizen/Miner.h"
// #include "../../citizen/Programmer.h"
// #include "../../citizen/Teacher.h"
// #include "../../citizen/Unemployed.h"
// #include "../../simulation/Simulation.h"
// #pragma once

// class FileLoader {
// public:
//     static Simulation* loadSimulation(
//         const char* filename
//     );

// private:
//     static Citizen* loadCitizen(std::ifstream& in);
//     static Building* loadBuilding(std::ifstream& in);
//     static City* loadCity(std::ifstream& in);

//     static constexpr size_t OFFSETS_FILE_NAME_LEN = 20;
//     static const char offsetsFileName[OFFSETS_FILE_NAME_LEN];
// };