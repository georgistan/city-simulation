#include "../citizen/Programmer.h"

CitizenType Programmer::getType() const {
    return CitizenType::PROGRAMMER;
}

Citizen* Programmer::clone() const {
    return new Programmer(*this);
}

void Programmer::firstOfTheMonthUpdate(double requiredTax) {
    money += monthlySalary;

    money = money < requiredTax ? 0 : money - requiredTax;

    happiness = happiness < 0 ? 0 : happiness - 1;
}

void Programmer::setMonthlySalary(size_t monthlySalary) {
    if (monthlySalary < 2000 || monthlySalary > 5000) {
        throw std::invalid_argument("Programmer must have salary in [2000, 5000]");
    }

    this->monthlySalary = monthlySalary;
}

Programmer::Programmer(const char* name, size_t happiness, size_t monthlySalary, size_t life)
    : Citizen(name, happiness, monthlySalary, life) {
    setMonthlySalary(monthlySalary);
    money = monthlySalary;
}

Programmer::Programmer(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        double money,
        size_t life
    ) : Citizen(name, happiness, monthlySalary, money, life) {}