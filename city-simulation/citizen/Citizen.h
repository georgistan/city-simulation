#include <iostream>
#pragma once

enum class CitizenType {
    MINER,
    PROGRAMMER,
    TEACHER,
    UNEMPLOYED, 
    UNKNOWN
};

class Citizen {
public:
    virtual Citizen* clone() const = 0;
    virtual CitizenType getType() const = 0;
    virtual void firstOfTheMonthUpdate(double requiredTax) = 0;

    void print() const;
    void payDaily();

    Citizen();
    Citizen(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        size_t life
    );
    Citizen(
        const char* name,
        size_t happiness,
        size_t monthlySalary,
        double money,
        size_t life
    );
    Citizen(const Citizen& other);
    Citizen& operator=(const Citizen& other);
    virtual ~Citizen() noexcept;

    const char* getName() const;
    size_t getHappiness() const;
    size_t getMonthlySalary() const;
    double getMoney() const;
    size_t getLife() const;

    void setName(const char* newName);
    void setHapinness(size_t newValue);
    void setLife(size_t newValue);

protected:
    char* name;
    size_t happiness;
    size_t monthlySalary;
    double money;
    size_t life;

    static const double DAILY_TAX;

    virtual void setMonthlySalary(size_t newValue) = 0;
};