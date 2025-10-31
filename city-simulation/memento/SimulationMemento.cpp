#include "SimulationMemento.h"

const City* SimulationMemento::getCitySnapshot() const {
    return citySnapshot;
}

SimulationMemento::SimulationMemento() : citySnapshot(nullptr), currDay(0) {}

SimulationMemento::SimulationMemento(const City* city, size_t day)
    : currDay(day)
{
    citySnapshot = new City(*city);
}


SimulationMemento::SimulationMemento(const SimulationMemento& other)
    : currDay(other.currDay)
{
    citySnapshot = new City(*other.citySnapshot);
}

SimulationMemento& 
SimulationMemento::operator=(const SimulationMemento& other) {
    if (this != &other) {
        delete citySnapshot;
        citySnapshot = new City(*other.citySnapshot);

        currDay = other.currDay;
    }
    
    return *this;
}


SimulationMemento::~SimulationMemento() noexcept {
    delete citySnapshot;
    citySnapshot = nullptr;
}