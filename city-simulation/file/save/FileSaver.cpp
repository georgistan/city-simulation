#include "FileSaver.h"
#include <fstream>
#include <cstring>
#include <stdexcept>

const char FileSaver::offsetsFileName[OFFSETS_FILE_NAME_LEN] = "offsets.bin";

void FileSaver::saveSimulation(const Simulation* sim, const char* filename) {
    if (!sim) return;

    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + filename);
    }

    std::ofstream offsets(offsetsFileName, std::ios::binary);
    if (!offsets.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + offsetsFileName);
    }

    // Съхраняваме примитивните стойности правилно
    int startingDay = sim->getStartingDay();
    int currentDay = sim->getCurrentDay();
    size_t snapshotCount = sim->getSnapshotCount();
    size_t snapshotCapacity = sim->getSnapshotCapacity();

    out.write(reinterpret_cast<const char*>(&startingDay), sizeof(startingDay));
    out.write(reinterpret_cast<const char*>(&currentDay), sizeof(currentDay));
    out.write(reinterpret_cast<const char*>(&snapshotCount), sizeof(snapshotCount));
    out.write(reinterpret_cast<const char*>(&snapshotCapacity), sizeof(snapshotCapacity));

    offsets.write(reinterpret_cast<const char*>(&snapshotCount), sizeof(snapshotCount));

    for (size_t i = 0; i < snapshotCount; ++i) {
        std::streampos pos = out.tellp();
        offsets.write(reinterpret_cast<const char*>(&pos), sizeof(pos));

        saveCity(sim->getSnapshots()[i]->getCitySnapshot(), out);
    }

    out.close();
    offsets.close();
}

void FileSaver::saveCity(const City* city, std::ofstream& out) {
    if (!city) {
        size_t zero = 0;
        out.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
        return;
    }

    size_t n = city->getN();
    size_t m = city->getM();

    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    out.write(reinterpret_cast<const char*>(&m), sizeof(m));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            saveBuilding(city->getBuilding(i, j), out);
        }
    }
}

void FileSaver::saveBuilding(const Building* building, std::ofstream& out) {
    if (!building) {
        int typeMarker = -1;
        out.write(reinterpret_cast<const char*>(&typeMarker), sizeof(typeMarker));
        return;
    }

    BuildingType type = building->getType();
    size_t citizenCount = building->getCitizenCount();
    size_t capacity = building->getCapacity();
    double rent = building->getRequiredRent();

    out.write(reinterpret_cast<const char*>(&type), sizeof(type));
    out.write(reinterpret_cast<const char*>(&citizenCount), sizeof(citizenCount));
    out.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    out.write(reinterpret_cast<const char*>(&rent), sizeof(rent));

    for (size_t i = 0; i < citizenCount; ++i) {
        saveCitizen(building->getCitizens()[i], out);
    }
}

void FileSaver::saveCitizen(const Citizen* citizen, std::ofstream& out) {
    if (!citizen) {
        int typeMarker = -1; // Means no citizen
        out.write(reinterpret_cast<const char*>(&typeMarker), sizeof(typeMarker));
        return;
    }

    CitizenType type = citizen->getType();
    out.write(reinterpret_cast<const char*>(&type), sizeof(type));

    size_t nameLen = std::strlen(citizen->getName());
    out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    out.write(citizen->getName(), nameLen);

    size_t happiness = citizen->getHappiness();
    size_t monthlySalary = citizen->getMonthlySalary();
    double money = citizen->getMoney();
    size_t life = citizen->getLife();

    out.write(reinterpret_cast<const char*>(&happiness), sizeof(happiness));
    out.write(reinterpret_cast<const char*>(&monthlySalary), sizeof(monthlySalary));
    out.write(reinterpret_cast<const char*>(&money), sizeof(money));
    out.write(reinterpret_cast<const char*>(&life), sizeof(life));
}