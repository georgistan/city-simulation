#include "../building/Building.h"
#pragma once

class OrdinaryBuilding : public Building {
public:
    Building* clone() const override;
    BuildingType getType() const override;
    LocationType getLocationType() const override;

    OrdinaryBuilding(
        BuildingType type,
        size_t citizenCount,
        size_t capacity
    );
private:
    void setRequiredRent() override;
};