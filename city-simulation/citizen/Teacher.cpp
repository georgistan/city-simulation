#include "../citizen/Teacher.h"

CitizenType Teacher::getType() const {
    return CitizenType::TEACHER;
}

Citizen* Teacher::clone() const {
    return new Teacher(*this);
}

void Teacher::firstOfTheMonthUpdate(double requiredTax) {
    money += monthlySalary;

    money = money < requiredTax ? 0 : money - requiredTax;

    happiness = happiness + 1 < 100 ? happiness + 1 : 100;
}

void Teacher::setMonthlySalary(size_t monthlySalary) {
    if (monthlySalary < 1200 || monthlySalary > 1300) {
        throw std::invalid_argument("Teacher must have salary in [1200, 1300]");
    }

    this->monthlySalary = monthlySalary;
}

Teacher::Teacher(const char* name, size_t happiness, size_t monthlySalary, size_t life)
    : Citizen(name, happiness, monthlySalary, life) {
    setMonthlySalary(monthlySalary);
    money = monthlySalary;
}

Teacher::Teacher(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        double money,
        size_t life
    ) : Citizen(name, happiness, monthlySalary, money, life) {}