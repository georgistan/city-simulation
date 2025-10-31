#include "../../citizen/Miner.h"
#include "../../citizen/Programmer.h"
#include "../../citizen/Teacher.h"
#include "../../citizen/Unemployed.h"
#pragma once

class CitizenFactory {
public:
    static Citizen* createCitizen(
        const char* name,
        const char* job,
        size_t happiness,
        size_t monthlySalary,
        size_t life
    );
};