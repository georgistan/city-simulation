#include "../building/CentralBuilding.h"

const double CentralBuilding::RENT_MULTIPLIER = 2.5;

Building* CentralBuilding::clone() const {
    return new CentralBuilding(*this);
}

BuildingType CentralBuilding::getType() const {
    return type;
}

LocationType CentralBuilding::getLocationType() const {
    return LocationType::CENTRAL;
}

CentralBuilding::CentralBuilding(
    BuildingType type,
    size_t citizenCount,
    size_t capacity
) : Building(type, citizenCount, capacity) {
    setRequiredRent();
};

void CentralBuilding::setRequiredRent() {
    Building::setRequiredRent();

    requiredRent *= RENT_MULTIPLIER;
}