#include "../citizen/Citizen.h"
#pragma once

class Programmer : public Citizen {
public:
    Citizen* clone() const override;
    CitizenType getType() const override;
    void firstOfTheMonthUpdate(double requiredTax) override;

    Programmer(const char* name, size_t happiness, size_t monthlySalary, size_t life);
    Programmer(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        double money,
        size_t life
    );

private:
    void setMonthlySalary(size_t monthlySalary) override;
};