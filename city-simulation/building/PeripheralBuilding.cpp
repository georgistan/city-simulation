#include "../building/PeripheralBuilding.h"

const double PeripheralBuilding::RENT_MULTIPLIER = 0.2;

Building* PeripheralBuilding::clone() const {
    return new PeripheralBuilding(*this);
}

BuildingType PeripheralBuilding::getType() const {
    return type;
}

LocationType PeripheralBuilding::getLocationType() const {
    return LocationType::PERIPHERAL;
}

PeripheralBuilding::PeripheralBuilding(
    BuildingType type,
    size_t citizenCount,
    size_t capacity
) : Building(type, citizenCount, capacity) {
    setRequiredRent();
};

void PeripheralBuilding::setRequiredRent() {
    Building::setRequiredRent();

    requiredRent -= requiredRent * RENT_MULTIPLIER;
}