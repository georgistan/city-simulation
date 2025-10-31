#include "../citizen/Citizen.h"
#pragma once

enum class BuildingType {
    MODERN,
    PANEL,
    DORM,
    UNKNOWN
};

enum class LocationType {
    CENTRAL,
    ORDINARY,
    PERIPHERAL,
    UNKNOWN
};

class Building {
public:
    virtual Building* clone() const = 0;
    virtual BuildingType getType() const = 0;
    virtual LocationType getLocationType() const = 0;

    bool addCitizen(Citizen* toAdd);
    bool removeCitizen(const char* toRemove);

    // TODO ------------------------------- just Simulation class logic for first of the month
    unsigned step(bool isFirstOfTheMonth);
    // -------------------------------

    void generate();

    void printCitizen(const char* name) const;
    void printCitizensNames() const;
    void printFullInfo() const;

    Building();
    Building(
        BuildingType type,
        size_t citizenCount,
        size_t capacity
    );
    Building(const Building& other);
    Building& operator=(const Building& other);
    virtual ~Building() noexcept;

    Citizen** getCitizens() const;
    size_t getCitizenCount() const;
    size_t getCapacity() const;
    double getRequiredRent() const;

protected:
    BuildingType type;
    Citizen** citizens;
    size_t citizenCount;
    size_t capacity;
    double requiredRent;

    virtual void setRequiredRent() = 0;

    void freeDynamic();

private:
    static const size_t MODERN_BUILDING_RENT; 
    static const size_t PANEL_BUILDING_RENT; 
    static const size_t DORM_BUILDING_RENT; 
};