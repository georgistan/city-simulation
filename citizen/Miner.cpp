#include "../citizen/Miner.h"

CitizenType Miner::getType() const {
    return CitizenType::MINER;
}

Citizen* Miner::clone() const {
    return new Miner(*this);
}

void Miner::firstOfTheMonthUpdate(double requiredTax) {
    money += monthlySalary;

    money = money < requiredTax ? 0 : money - requiredTax;

    life = life < 0 ? 0 : life - 1;
}

void Miner::setMonthlySalary(size_t monthlySalary) {
    if (monthlySalary < 1000 || monthlySalary > 3000) {
        throw std::invalid_argument("Miner must have salary in [1000, 3000]");
    }

    this->monthlySalary = monthlySalary;
}

Miner::Miner(const char* name, size_t happiness, size_t monthlySalary, size_t life)
    : Citizen(name, happiness, monthlySalary, life) {
    setMonthlySalary(monthlySalary);
    money = monthlySalary;
}

Miner::Miner(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        double money,
        size_t life
    ) : Citizen(name, happiness, monthlySalary, money, life) {}