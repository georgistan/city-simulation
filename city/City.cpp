#include "../city/City.h"
#include "../random-generator/building/RandomBuildingGenerator.h"
#include <stdexcept>
#include <cmath>

const double City::CENTRAL_BUILDING_DISTANCE_DIVIDER = 8;
const double City::PERIPHERAL_BUILDING_DISTANCE_MULTIPLIER = 6;

bool City::addCitizen(size_t x, size_t y, Citizen* toAdd) {
    if (x > n || x < 0 || y < 0 || y > m) {
        throw std::invalid_argument("Invalid building coordinates");
    }

    return buildings[x][y]->addCitizen(toAdd);
}

bool City::removeCitizen(size_t x, size_t y, const char* name) {
    return buildings[x][y]->removeCitizen(name);
}

unsigned City::step(bool isFirstOfTheMonth) {
    unsigned deadCitizens = 0;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            deadCitizens += buildings[i][j]->step(isFirstOfTheMonth);
        }
    }

    return deadCitizens;
}

void City::printSpecificCitizen(size_t x, size_t y, const char* name) const {
    if (x < 0 || x > n || y < 0 || y > m) {
        throw std::invalid_argument("Invalid building coordinates");
    }

    buildings[x][y]->printCitizen(name);
}

void City::printSpecificBuilding(size_t x, size_t y) const {
    if (x < 0 || x > n - 1 || y < 0 || y > m - 1) {
        throw std::invalid_argument("Invalid building coordinates");
    }

    buildings[x][y]->printCitizensNames();
}

void City::printFullInfo() const {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            std::cout << "Location (" << i << ", " << j << "):" << "\n";
            buildings[i][j]->printFullInfo();
        }
    }
}

void City::loadBuilding(size_t i, size_t j, Building& building) {
    this->buildings[i][j] = building.clone();
}

size_t City::getN() const {
    return n;
}

size_t City::getM() const {
    return m;
}

const Building* City::getBuilding(size_t i, size_t j) const {
    return buildings[i][j];
}

City::City(size_t n, size_t m) : n(n), m(m) {
    buildings = new Building**[n];

    for (size_t i = 0; i < n; i++) {
        buildings[i] = new Building*[m];
        
        for (size_t j = 0; j < m; j++) {
            buildings[i][j] = RandomBuildingGenerator::generateBuilding(calcLocationType(i, j));
        }
    }
}

City::City(const City& other) : n(other.n), m(other.m) {
    buildings = new Building**[n];

    for (size_t i = 0; i < n; i++) {
        buildings[i] = new Building*[m];

        for (size_t j = 0; j < m; j++) {
            buildings[i][j] = other.buildings[i][j]->clone();
        }
    }
}

City& City::operator=(const City& other) {
    if (this != &other) {
        Building*** temp = new Building**[other.n] {nullptr};

        try {
            for (size_t i = 0; i < other.n; i++) {
                temp[i] = new Building*[other.m];

                for (size_t j = 0; j < other.m; j++) {
                    temp[i][j] = other.buildings[i][j]->clone();
                }
            }
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;

            deleteBuildings(temp, other.n, other.m);

            throw ex;
        }

        deleteBuildings(this->buildings, this->n, this->m);
        buildings = temp;

        n = other.n;
        m = other.m;
    }

    return *this;
}

City::~City() noexcept {
    deleteBuildings(buildings, n, m);
}

void City::deleteBuildings(Building*** buildings, size_t n, size_t m) {
    if (!buildings) {
        return;
    }

    for (size_t i = 0; i < n; i++) {
        if (buildings[i]) {
            for (size_t j = 0; j < m; j++) {
                delete buildings[i][j];
                buildings[i][j] = nullptr;
            }

            delete[] buildings[i];
            buildings[i] = nullptr;
        }
    }

    delete[] buildings;
    buildings = nullptr;
}

LocationType City::calcLocationType(size_t x, size_t y) {
    double centerX = n / 2.0;
    double centerY = m / 2.0;
    
    double dx = x - centerX;
    double dy = y - centerY;
    double distance = sqrt(dx * dx + dy * dy);
    
    double minSide = std::min(n, m);
    double centralThreshold = minSide / CENTRAL_BUILDING_DISTANCE_DIVIDER;
    double peripheralThreshold = (PERIPHERAL_BUILDING_DISTANCE_MULTIPLIER * minSide) / CENTRAL_BUILDING_DISTANCE_DIVIDER;
    
    if (distance <= centralThreshold) {
        return LocationType::CENTRAL;
    } else if (distance > peripheralThreshold) {
        return LocationType::PERIPHERAL;
    } else {
        return LocationType::ORDINARY;
    }
}