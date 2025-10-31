// #include "FileLoader.h"
// #include <fstream>
// #include <stdexcept>
// #include <cstring>

// Simulation* FileLoader::loadSimulation(const char* filename) {
//     std::ifstream in(filename, std::ios::binary);
//     if (!in.is_open()) {
//         throw std::ios_base::failure(("Failed to open file: %s", filename));
//     }

//     size_t startingDay;
//     size_t currentDay;
//     size_t snapshotCount;
//     size_t snapshotCapacity;

//     in.read(reinterpret_cast<char*>(&startingDay), sizeof(startingDay));
//     in.read(reinterpret_cast<char*>(&currentDay), sizeof(currentDay));
//     in.read(reinterpret_cast<char*>(&snapshotCount), sizeof(snapshotCount));
//     in.read(reinterpret_cast<char*>(&snapshotCapacity), sizeof(snapshotCapacity));

//     Simulation* sim = new Simulation(
//         startingDay,
//         currentDay,
//         snapshotCount,
//         snapshotCapacity
//     );

//     for (size_t i = 0; i < snapshotCount; ++i) {
//         City* snapshotCity = loadCity(in);
//         sim->loadSnapshot((new SimulationMemento(snapshotCity, i)), i);
//     }

//     in.close();

//     return sim;
// }

// City* FileLoader::loadCity(std::ifstream& in) {
//     size_t n;
//     size_t m;
//     in.read(reinterpret_cast<char*>(&n), sizeof(n));
//     in.read(reinterpret_cast<char*>(&m), sizeof(m));

//     City* city = new City(n, m);

//     for (size_t i = 0; i < n; i++) {
//         for (size_t j = 0; j < m; j++) {
//             Building* building = loadBuilding(in);
//             city->loadBuilding(i, j, *building);
//         }
//     }

//     return city;
// }

// Building* FileLoader::loadBuilding(std::ifstream& in) {
//     BuildingType buildingType;
//     in.read(reinterpret_cast<char*>(&buildingType), sizeof(buildingType));

//     size_t citizenCount;
//     size_t capacity;
//     double rent;
//     in.read(reinterpret_cast<char*>(&citizenCount), sizeof(citizenCount));
//     in.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));
//     in.read(reinterpret_cast<char*>(&rent), sizeof(rent));

//     LocationType locationType;
//     in.read(reinterpret_cast<char*>(&locationType), sizeof(locationType));

//     Building* building = nullptr;
//     switch (locationType) {
//         case LocationType::CENTRAL:
//             building = new CentralBuilding(buildingType, citizenCount, capacity); break;
//         case LocationType::ORDINARY:
//             building = new OrdinaryBuilding(buildingType, citizenCount, capacity); break;
//         case LocationType::PERIPHERAL:
//             building = new PeripheralBuilding(buildingType, citizenCount, capacity); break;
//         default:
//             building = nullptr;break;
//     }

//     if (building) {
//         for (size_t i = 0; i < citizenCount; ++i) {
//             Citizen* citizen = loadCitizen(in);
//             building->addCitizen(citizen);
//         }
//     }

//     return building;
// }

// Citizen* FileLoader::loadCitizen(std::ifstream& in) {
//     CitizenType citizenType;
//     in.read(reinterpret_cast<char*>(&citizenType), sizeof(citizenType));

//     size_t nameLen;
//     in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
//     char* name = new char[nameLen + 1];
//     in.read(name, nameLen);
//     name[nameLen] = '\0';

//     size_t happiness;
//     size_t monthlySalary; 
//     size_t life;
//     double money;
//     in.read(reinterpret_cast<char*>(&happiness), sizeof(happiness));
//     in.read(reinterpret_cast<char*>(&monthlySalary), sizeof(monthlySalary));
//     in.read(reinterpret_cast<char*>(&money), sizeof(money));
//     in.read(reinterpret_cast<char*>(&life), sizeof(life));

//     Citizen* citizen = nullptr;
//     switch (citizenType) {
//         case CitizenType::MINER:
//             citizen = new Miner(name, happiness, monthlySalary, money, life);
//             break;
//         case CitizenType::PROGRAMMER:
//             citizen = new Programmer(name, happiness, monthlySalary, money, life);
//             break;
//         case CitizenType::TEACHER:
//             citizen = new Teacher(name, happiness, monthlySalary, money, life);
//             break;
//         case CitizenType::UNEMPLOYED:
//             citizen = new Unemployed(name, happiness, monthlySalary, money, life);
//             break;
//         default:
//             citizen = nullptr;
//             break;
//     }

//     delete[] name;
//     return citizen;
// }