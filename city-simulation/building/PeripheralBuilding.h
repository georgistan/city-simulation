#include "../building/Building.h"
#pragma once

class PeripheralBuilding : public Building {
public:
    Building* clone() const override;
    BuildingType getType() const override;
    LocationType getLocationType() const override;

    PeripheralBuilding(
        BuildingType type,
        size_t citizenCount,
        size_t capacity
    );
private:
    static const double RENT_MULTIPLIER;

    void setRequiredRent() override;
};