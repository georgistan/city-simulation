#include "../building/Building.h"
#pragma once

class CentralBuilding : public Building {
public:
    Building* clone() const override;
    BuildingType getType() const override;
    LocationType getLocationType() const override;

    CentralBuilding(
        BuildingType type,
        size_t citizenCount,
        size_t capacity
    );
private:
    static const double RENT_MULTIPLIER;

    void setRequiredRent() override;
};