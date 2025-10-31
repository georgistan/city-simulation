#include "../../building/CentralBuilding.h"
#include "../../building/OrdinaryBuilding.h"
#include "../../building/PeripheralBuilding.h"
#pragma once

class BuildingFactory {
public:
    static Building* createBuilding(
        BuildingType type,
        size_t citizenCount,
        size_t capacity,
        LocationType location
    );
};