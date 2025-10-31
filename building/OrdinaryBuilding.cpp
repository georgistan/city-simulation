#include "../building/OrdinaryBuilding.h"

Building* OrdinaryBuilding::clone() const {
    return new OrdinaryBuilding(*this);
}

BuildingType OrdinaryBuilding::getType() const {
    return type;
}

LocationType OrdinaryBuilding::getLocationType() const {
    return LocationType::ORDINARY;
}

OrdinaryBuilding::OrdinaryBuilding(
    BuildingType type,
    size_t citizenCount,
    size_t capacity
) : Building(type, citizenCount, capacity) {
    setRequiredRent();
};

void OrdinaryBuilding::setRequiredRent() {
    Building::setRequiredRent();
}