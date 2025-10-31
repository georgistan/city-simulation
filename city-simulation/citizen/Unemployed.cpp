#include "../citizen/Unemployed.h"

CitizenType Unemployed::getType() const {
    return CitizenType::UNEMPLOYED;
}

Citizen* Unemployed::clone() const {
    return new Unemployed(*this);
}

void Unemployed::firstOfTheMonthUpdate(double requiredTax) {
    money = money < requiredTax ? 0 : money - requiredTax;

    life = life == 0 ? 0 : life - 1;
}

void Unemployed::setMonthlySalary(size_t monthlySalary) {
    if (monthlySalary != 0) {
        throw std::invalid_argument("Unemployed citizen must have salary of 0");
    }

    this->monthlySalary = monthlySalary;
}

Unemployed::Unemployed(const char* name, size_t happiness, size_t monthlySalary, size_t life)
    : Citizen(name, happiness, monthlySalary, life) {
    setMonthlySalary(monthlySalary);
    money = monthlySalary;
}   

Unemployed::Unemployed(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        double money,
        size_t life
    ) : Citizen(name, happiness, monthlySalary, money, life) {}