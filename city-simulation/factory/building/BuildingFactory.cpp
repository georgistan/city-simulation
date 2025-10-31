#include "BuildingFactory.h"
#include <stdexcept>

Building* BuildingFactory::createBuilding(
    BuildingType type,
    size_t citizenCount,
    size_t capacity,
    LocationType location
) {
    switch (location) {
        case LocationType::CENTRAL:    return new CentralBuilding(type, citizenCount, capacity);
        case LocationType::ORDINARY:   return new OrdinaryBuilding(type, citizenCount, capacity);
        case LocationType::PERIPHERAL: return new PeripheralBuilding(type, citizenCount, capacity);
        default:                       throw std::logic_error("Could not create a building");
    }
}