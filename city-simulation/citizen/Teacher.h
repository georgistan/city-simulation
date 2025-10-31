#include "../citizen/Citizen.h"
#pragma once

class Teacher : public Citizen {
public:
    Citizen* clone() const override;
    CitizenType getType() const override;
    void firstOfTheMonthUpdate(double requiredTax) override;

    Teacher(const char* name, size_t happiness, size_t monthlySalary, size_t life);
    Teacher(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        double money,
        size_t life
    );

private:
    void setMonthlySalary(size_t newValue) override;
};