#include "../citizen/Citizen.h"
#include <stdexcept>
#include <cstring>
#pragma warning (disable : 4996)

const double Citizen::DAILY_TAX = 50.0; 

void Citizen::print() const {
    std::cout << "\tName: "      << name          << "\n"
              << "\tHappiness: " << happiness     << "\n"
              << "\tSalary: "    << monthlySalary << "\n"
              << "\tMoney: "     << money         << "\n"
              << "\tLife: "      << life          << "\n"
              << "\n";
}

void Citizen::payDaily() {
    if (money > 0.0) {
        money -= DAILY_TAX;
    }
}

Citizen::Citizen() : name(nullptr), happiness(0), money(0.0), life(0) {}

Citizen::Citizen(
    const char* name,
    size_t happiness,
    size_t monthlySalary,
    size_t life
) : 
    happiness(happiness), 
    life(life) 
{
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
}

Citizen::Citizen(
    const char* name,
    size_t happiness,
    size_t monthlySalary,
    double money,
    size_t life
) : 
    happiness(happiness), 
    monthlySalary(monthlySalary),
    money(money),
    life(life)
{
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
}

Citizen::Citizen(const Citizen& other) {
    name = new char[std::strlen(other.name) + 1];
    std::strcpy(name, other.name);

    happiness = other.happiness;
    monthlySalary = other.monthlySalary;
    money = other.money;
    life = other.life;
}

Citizen& Citizen::operator=(const Citizen& other) {
    if (this != &other) {
        char* temp = new char[std::strlen(other.name) + 1];

        try {
            std::strcpy(temp, other.name);
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;

            delete[] temp;

            throw ex;
        }

        delete[] name;
        name = temp;

        happiness = other.happiness;
        monthlySalary = other.monthlySalary;
        life = other.life;
    }

    return *this;
}

Citizen::~Citizen() noexcept {
    delete[] name;
    name = nullptr;
}

const char* Citizen::getName() const {
    return name;
}

size_t Citizen::getHappiness() const {
    return happiness;
}

size_t Citizen::getMonthlySalary() const {
    return monthlySalary;
}

double Citizen::getMoney() const {
    return money;
}

size_t Citizen::getLife() const {
    return life;
}

void Citizen::setName(const char* newName) {
    if (!newName) {
        throw std::invalid_argument("Name of citizen cannot be set to nullptr");
    }

    size_t newNameLen = std::strlen(newName);

    if (newNameLen == 0) {
        throw std::invalid_argument("Name of citizen cannot be empty");
    }

    if (std::strcmp(name, newName)) {
        return;
    }

    delete[] name;
    name = new char[newNameLen + 1];
    std::strcpy(name, newName);
}

void Citizen::setHapinness(size_t newValue) {
    happiness = newValue;
}

void Citizen::setLife(size_t newValue) {
    life = newValue;
}