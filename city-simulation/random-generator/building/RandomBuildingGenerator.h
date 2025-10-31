#include "../../building/Building.h"
#pragma once

class RandomBuildingGenerator {
public:
    static Building* generateBuilding(LocationType location);

private:
    static const size_t TYPE_LOWER_BOUND;
    static const size_t TYPE_UPPER_BOUND;

    static const size_t CAPACITY_LOWER_BOUND;
    static const size_t CAPACITY_UPPER_BOUND;

    static BuildingType generateType();
    static int randInt(int min, int max);
};