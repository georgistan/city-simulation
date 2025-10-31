#include "../../factory/citizen/CitizenFactory.h"
#pragma once

class RandomCitizenGenerator {
public:
    static Citizen* generateCitizen();

private:
    static const size_t HAPPINESS_LOWER_BOUND;
    static const size_t HAPPINESS_UPPER_BOUND;

    static const size_t LIFE_LOWER_BOUND;
    static const size_t LIFE_UPPER_BOUND;

    static constexpr size_t NAMES_COUNT = 15;
    static constexpr size_t JOBS_COUNT = 4;
    static constexpr size_t STRING_LEN = 50;
    static const char namePool[NAMES_COUNT][STRING_LEN];
    static const char jobPool[JOBS_COUNT][STRING_LEN];

    static const size_t MINER_SALARY_LOWER_BOUND;
    static const size_t MINER_SALARY_UPPER_BOUND;

    static const size_t PROGRAMMER_SALARY_LOWER_BOUND;
    static const size_t PROGRAMMER_SALARY_UPPER_BOUND;

    static const size_t TEACHER_SALARY_LOWER_BOUND;
    static const size_t TEACHER_SALARY_UPPER_BOUND;

    static const size_t UNEMPLOYED_SALARY;    
    
    static int randInt(int min, int max);
    static size_t getRandomSalary(const char* job);
};