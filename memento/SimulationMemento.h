#include "../city/City.h"
#pragma once

class SimulationMemento {
    friend class Simulation;
public:
    const City* getCitySnapshot() const;

    SimulationMemento(const City* city, size_t day);
private:
    City* citySnapshot;
    size_t currDay;

    SimulationMemento();
    // SimulationMemento(const City* city, size_t day);
    SimulationMemento(const SimulationMemento& other);
    SimulationMemento& operator=(const SimulationMemento& other);
    ~SimulationMemento() noexcept;
};