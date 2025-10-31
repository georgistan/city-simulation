#include "../building/Building.h"
#pragma once

namespace Utils {
    const char* mapBuildingTypeToString(BuildingType type) {
        switch (type) {
            case BuildingType::MODERN: return "Modern";
            case BuildingType::PANEL:  return "Panel";
            case BuildingType::DORM:   return "Dorm";
            default:                   return "Unknown";
        }
    }

    const char* mapCitizenTypeToString(CitizenType type) {
        switch (type) {
            case CitizenType::MINER:      return "Miner";
            case CitizenType::PROGRAMMER: return "Programmer";
            case CitizenType::TEACHER:    return "Teacher";
            case CitizenType::UNEMPLOYED: return "Unemployed";
            default:                      return "Unknown";
        }
    }
}