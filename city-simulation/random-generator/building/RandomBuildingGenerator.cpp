#include "RandomBuildingGenerator.h"
#include "../../factory/building/BuildingFactory.h"
#include <cstdlib>
#include <ctime>

const size_t RandomBuildingGenerator::TYPE_LOWER_BOUND = 1;
const size_t RandomBuildingGenerator::TYPE_UPPER_BOUND = 3;

const size_t RandomBuildingGenerator::CAPACITY_LOWER_BOUND = 1;
const size_t RandomBuildingGenerator::CAPACITY_UPPER_BOUND = 10;

Building* RandomBuildingGenerator::generateBuilding(LocationType location) {
    size_t capacity = randInt(CAPACITY_LOWER_BOUND, CAPACITY_UPPER_BOUND);

    return BuildingFactory::createBuilding(
        generateType(), 
        randInt(CAPACITY_LOWER_BOUND, capacity),
        capacity,
        location
    );
}

BuildingType RandomBuildingGenerator::generateType() {
    switch (randInt(TYPE_LOWER_BOUND, TYPE_UPPER_BOUND)) {
        case 1: return BuildingType::MODERN;
        case 2: return BuildingType::PANEL;
        case 3: return BuildingType::DORM;
        default: return BuildingType::UNKNOWN;
    }
}

int RandomBuildingGenerator::randInt(int min, int max) {
    return min + (std::rand() % (max - min + 1));
}