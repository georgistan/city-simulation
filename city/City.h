#include "../building/Building.h"
#pragma once

class City {
public:
    bool addCitizen(size_t x, size_t y, Citizen* toAdd);
    bool removeCitizen(size_t x, size_t y, const char* name);

    unsigned step(bool isFirstOfTheMonth);

    void printSpecificCitizen(size_t x, size_t y, const char* name) const;
    void printSpecificBuilding(size_t x, size_t y) const;
    void printFullInfo() const;

    void loadBuilding(size_t i, size_t j, Building& building);

    size_t getN() const;
    size_t getM() const;
    const Building* getBuilding(size_t i, size_t j) const;

    City(size_t n, size_t m);
    City(const City& other);
    City& operator=(const City& other);
    ~City() noexcept;

private: 
    Building*** buildings;
    size_t n;
    size_t m;

    static const double CENTRAL_BUILDING_DISTANCE_DIVIDER;
    static const double PERIPHERAL_BUILDING_DISTANCE_MULTIPLIER;

    void deleteBuildings(Building*** buildings, size_t n, size_t m);

    LocationType calcLocationType(size_t x, size_t y);
};