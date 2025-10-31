#include "../building/Building.h"
#include "../random-generator/citizen/RandomCitizenGenerator.h"
#include <stdexcept>
#include <cstring>
#include "../utils/Utils.h"

const size_t Building::MODERN_BUILDING_RENT = 1000; 
const size_t Building::PANEL_BUILDING_RENT = 500; 
const size_t Building::DORM_BUILDING_RENT = 40; 

// namespace Utils {
//     const char* mapBuildingTypeToString(BuildingType type) {
//         switch (type) {
//             case BuildingType::MODERN: return "Modern";
//             case BuildingType::PANEL:  return "Panel";
//             case BuildingType::DORM:   return "Dorm";
//             default:                   return "Unknown";
//         }
//     }
// }

bool Building::addCitizen(Citizen* toAdd) {
    if (citizenCount == capacity) {
        std::cout << "Building is already full, cannot add more citizens to it" << std::endl;

        return false;
    }

    citizens[citizenCount] = toAdd;
    citizenCount++;

    return true;
}

bool Building::removeCitizen(const char* toRemove) {
    for (size_t i = 0; i < citizenCount; i++) {
        if (std::strcmp(citizens[i]->getName(), toRemove) == 0) {
            std::swap(citizens[i], citizens[citizenCount - 1]);
            citizenCount--;

            return true;
        }
    }

    return false;
}

unsigned Building::step(bool isFirstOfTheMonth) {
    unsigned deadCitizensCount = 0;

    for (size_t i = 0; i < citizenCount; i++) {
        if (isFirstOfTheMonth) {
            citizens[i]->firstOfTheMonthUpdate(getRequiredRent());
        } else {
            citizens[i]->payDaily();
        }

        if (
            citizens[i]->getHappiness() == 0 &&
            citizens[i]->getLife() == 0 && 
            citizens[i]->getMoney() == 0.0
        ) {
            std::swap(citizens[i], citizens[citizenCount]);
            citizenCount--;

            deadCitizensCount++;
        }
    }

    return deadCitizensCount;
}

void Building::printCitizen(const char* name) const {
    for (size_t i = 0; i < citizenCount; i++) {
        if (std::strcmp(citizens[i]->getName(), name) == 0) {
            citizens[i]->print();
            return;
        }
    }

    throw std::invalid_argument(("Citizen %s does not live in the building!", name));
}

void Building::printCitizensNames() const {
    std::cout << "Building type: "                      << Utils::mapBuildingTypeToString(type)     << "\n"
              << "Citizens in the building: "           << citizenCount                             << "\n"
              << "Building capacity: "                  << capacity                                 << "\n"
              << "Required rent on a monthly basis: "   << requiredRent                             << "\n"
              << "Citizens in the building: ";
    
    for (size_t i = 0; i < citizenCount; i++) {
        std::cout << citizens[i]->getName();

        if (i != citizenCount - 1) {
            std::cout << ", ";
        }
    }

    std::cout << std::endl;
}

void Building::printFullInfo() const {
    std::cout << "\tBuilding type: " << Utils::mapBuildingTypeToString(type) << "\n";

    for (size_t i = 0; i < citizenCount; i++) {
        citizens[i]->print();
    }
}

Building::Building() : 
    citizens(nullptr), 
    citizenCount(0), 
    capacity(0), 
    requiredRent(0.0) {}

Building::Building(
    BuildingType type,
    size_t citizenCount,
    size_t capacity
) :
    type(type),
    citizenCount(citizenCount),
    capacity(capacity)
{
    citizens = new Citizen*[capacity];

    for (size_t i = 0; i < capacity; i++) {
        citizens[i] = RandomCitizenGenerator::generateCitizen();
    }
}

Building::Building(const Building& other) :
    type(other.type),
    citizenCount(other.citizenCount),
    capacity(other.capacity),
    requiredRent(other.requiredRent)
{
    citizens = new Citizen*[capacity];

    for (size_t i = 0; i < citizenCount; i++) {
        citizens[i] = other.citizens[i]->clone();
    }
}

Building& Building::operator=(const Building& other) {
    if (this != &other) {
        Citizen** temp = new Citizen*[other.capacity];
        
        try {
            for (size_t i = 0; i < other.citizenCount; i++) {
                temp[i] = other.citizens[i]->clone();
            }
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;

            for (size_t i = 0; i < other.citizenCount; i++) {
                delete temp[i];
            }

            delete[] temp;

            throw ex;
        }

        freeDynamic();
        citizens = temp;

        type = other.type;
        citizenCount = other.citizenCount;
        capacity = other.capacity;
        requiredRent = other.requiredRent;
    }

    return *this;
}

void Building::freeDynamic() {
    for (size_t i = 0; i < citizenCount; i++) {
        delete citizens[i];
    }

    delete[] citizens;
    citizens = nullptr;
}

Building::~Building() noexcept {
    freeDynamic();
}

BuildingType Building::getType() const {
    return type;
}

Citizen** Building::getCitizens() const {
    return citizens;
}

size_t Building::getCitizenCount() const {
    return citizenCount;
}

size_t Building::getCapacity() const {
    return capacity;
}

double Building::getRequiredRent() const {
    return requiredRent;
}

void Building::setRequiredRent() {
    switch (type) {
        case BuildingType::MODERN: requiredRent = MODERN_BUILDING_RENT; break;
        case BuildingType::PANEL:  requiredRent = PANEL_BUILDING_RENT; break;
        case BuildingType::DORM:   requiredRent = DORM_BUILDING_RENT; break;
        default:                   requiredRent = 0.0;
    }
}