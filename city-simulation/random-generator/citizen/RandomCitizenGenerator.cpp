#include "RandomCitizenGenerator.h"
#include <cstring>

const size_t RandomCitizenGenerator::HAPPINESS_LOWER_BOUND = 1;
const size_t RandomCitizenGenerator::HAPPINESS_UPPER_BOUND = 20;

const size_t RandomCitizenGenerator::LIFE_LOWER_BOUND = 1;
const size_t RandomCitizenGenerator::LIFE_UPPER_BOUND = 20;

const size_t RandomCitizenGenerator::MINER_SALARY_LOWER_BOUND = 1000;
const size_t RandomCitizenGenerator::MINER_SALARY_UPPER_BOUND = 3000;

const size_t RandomCitizenGenerator::PROGRAMMER_SALARY_LOWER_BOUND = 2000;
const size_t RandomCitizenGenerator::PROGRAMMER_SALARY_UPPER_BOUND = 5000;

const size_t RandomCitizenGenerator::TEACHER_SALARY_LOWER_BOUND = 1200;
const size_t RandomCitizenGenerator::TEACHER_SALARY_UPPER_BOUND = 1300;

const size_t RandomCitizenGenerator::UNEMPLOYED_SALARY = 0;

const char RandomCitizenGenerator::namePool[NAMES_COUNT][STRING_LEN] = {
    "Joro",
    "Vlado",
    "Selina",
    "Hristian",
    "Elena",
    "Andrey",
    "Mihaela",
    "Kayra",
    "Bozhidar",
    "Aleksandur",
    "Nikol",
    "Stefani",
    "Krisi",
    "Tommy",
    "Stefan"
};

const char RandomCitizenGenerator::jobPool[JOBS_COUNT][STRING_LEN] {
    "Miner",
    "Programmer",
    "Teacher",
    "Unemployed"
};

size_t RandomCitizenGenerator::getRandomSalary(const char* job) {
    if (std::strcmp(job, "Miner") == 0) {
        return randInt(MINER_SALARY_LOWER_BOUND, MINER_SALARY_UPPER_BOUND);
    } else if (std::strcmp(job, "Programmer") == 0) {
        return randInt(PROGRAMMER_SALARY_LOWER_BOUND, PROGRAMMER_SALARY_UPPER_BOUND);
    } else if (std::strcmp(job, "Teacher") == 0) {
        return randInt(TEACHER_SALARY_LOWER_BOUND, TEACHER_SALARY_UPPER_BOUND);
    } else if (std::strcmp(job, "Unemployed") == 0) {
        return UNEMPLOYED_SALARY;
    } else {
        return 0;
    }
}

Citizen* RandomCitizenGenerator::generateCitizen() {
    const char* job = jobPool[randInt(0, JOBS_COUNT - 1)];

    return CitizenFactory::createCitizen(
        namePool[randInt(0, NAMES_COUNT - 1)],
        job,
        randInt(HAPPINESS_LOWER_BOUND, HAPPINESS_UPPER_BOUND),
        getRandomSalary(job),
        randInt(LIFE_LOWER_BOUND, LIFE_UPPER_BOUND)
    );
}

int RandomCitizenGenerator::randInt(int min, int max) {
    return min + (std::rand() % (max - min + 1));
}