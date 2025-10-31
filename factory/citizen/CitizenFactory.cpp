#include "CitizenFactory.h"
#include <stdexcept>
#include <cstring>

Citizen* CitizenFactory::createCitizen(
    const char* name,
    const char* job,
    size_t happiness,
    size_t monthlySalary,
    size_t life
) {
    if (!name) {
        throw std::invalid_argument("Cannot create citizen with nullptr name");
    }

    if (!job) {
        throw std::invalid_argument("Cannot create citizen with nullptr job");
    }

    if (std::strcmp(job, "miner") == 0 || std::strcmp(job, "Miner") == 0) {
        return new Miner(name, happiness, monthlySalary, life);
    } else if (std::strcmp(job, "programmer") == 0 || std::strcmp(job, "Programmer") == 0) {
        return new Programmer(name, happiness, monthlySalary, life);
    } else if (std::strcmp(job, "teacher") == 0 || std::strcmp(job, "Teacher") == 0) {
        return new Teacher(name, happiness, monthlySalary, life);
    } else if (std::strcmp(job, "unemployed") == 0 || std::strcmp(job, "Unemployed") == 0) {
        return new Unemployed(name, happiness, monthlySalary, life);
    } else {
        throw std::invalid_argument("Trying to create a citizen with invalid job");
    }
}