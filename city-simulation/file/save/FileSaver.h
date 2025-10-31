#include "../../city/City.h"
#include "../../building/Building.h"
#include "../../citizen/Citizen.h"
#include "../../simulation/Simulation.h"
#pragma once

class FileSaver {
public:
    static void saveSimulation(
        const Simulation* sim, 
        const char* simFile
    );

private:
    static void saveCitizen(const Citizen* c, std::ofstream& out);
    static void saveBuilding(const Building* b, std::ofstream& out);
    static void saveCity(const City* city, std::ofstream& out);

    static constexpr size_t OFFSETS_FILE_NAME_LEN = 20;
    static const char offsetsFileName[OFFSETS_FILE_NAME_LEN];
};