#include "../city/City.h"
#include "../memento/SimulationMemento.h"
#include <chrono>
#include <ctime>
#pragma once

class Simulation {
public:
    bool generateCity(size_t n, size_t m);

    bool addCitizen(
        size_t n, 
        size_t m, 
        const char* name, 
        const char* job,
        size_t happiness,
        size_t monthlySalary,
        size_t life
    );
    bool removeCitizen(size_t x, size_t y, const char* name);

    unsigned step();
    unsigned step(int steps);

    void info() const;
    void info(size_t x, size_t y) const;
    void info(size_t x, size_t y, const char* name) const;

    // TODO -----------------------------------
    void save(const char* fileName);
    void load(const char* fileName) const;
    void loadSnapshot(SimulationMemento* snapshot, size_t index);
    // -----------------------------------

    size_t getStartingDay() const;
    size_t getCurrentDay() const;
    size_t getSnapshotCount() const;
    size_t getSnapshotCapacity() const;
    SimulationMemento** getSnapshots() const;

    Simulation();
    Simulation(
        size_t startingDay,
        size_t currentDay,
        size_t snapshotCount,
        size_t snapshotCapacity
    );
    Simulation(const Simulation& other);
    Simulation& operator=(const Simulation& other);
    ~Simulation() noexcept;

private:
    City* city;
    size_t currDay;
    size_t startingDay;

    SimulationMemento** snapshots;
    size_t snapshotCount;
    size_t snapshotCapacity;

    void addSnapshot();
    void restoreFromSnapshot(size_t dayIndex);
    int getSimulatedDayOfMonth() const;
};