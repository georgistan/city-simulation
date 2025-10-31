#include "../simulation/Simulation.h"
#include "../factory/citizen/CitizenFactory.h"
#include "../file/save/FileSaver.h"
// #include "../file/load/FileLoader.h"
#include <stdexcept>
#include <cstdlib>

int Simulation::getSimulatedDayOfMonth() const {
    std::time_t now = std::time(nullptr);
    std::tm localTime = *std::localtime(&now);

    localTime.tm_mday = static_cast<int>(startingDay);

    localTime.tm_mday += static_cast<int>(currDay);

    std::mktime(&localTime);

    return localTime.tm_mday;
}

bool Simulation::generateCity(size_t n, size_t m) {
    std::time_t timeLocal = std::time(nullptr);

    int randomDays = std::rand() % 365;
    timeLocal += randomDays * 24 * 60 * 60;

    std::tm* localTime = std::localtime(&timeLocal);

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", localTime);
    std::cout << "Starting date of simulation: " << buffer << "\n";

    startingDay = static_cast<size_t>(localTime->tm_mday);
    city = new City(n, m);

    return true;
}

bool Simulation::addCitizen(
    size_t n, 
    size_t m, 
    const char* name, 
    const char* job,
    size_t happiness,
    size_t monthlySalary,
    size_t life
) {
    return city->addCitizen(n, m, CitizenFactory::createCitizen(name, job, happiness, monthlySalary, life));
}

bool Simulation::removeCitizen(size_t x, size_t y, const char* name) {
    return city->removeCitizen(x, y, name);
}

void Simulation::addSnapshot() {
    if (snapshotCount == snapshotCapacity) {
        size_t newCapacity = (snapshotCapacity == 0) ? 10 : snapshotCapacity * 2;
        SimulationMemento** newArray = new SimulationMemento*[newCapacity];

        for (size_t i = 0; i < snapshotCount; i++) {
            newArray[i] = snapshots[i];
        }

        delete[] snapshots;
        snapshots = newArray;
        snapshotCapacity = newCapacity;
    }

    snapshots[snapshotCount] = new SimulationMemento(city, currDay);
    snapshotCount++;
    currDay++;
}

void Simulation::restoreFromSnapshot(size_t dayIndex) {
    delete city;
    city = new City(*snapshots[dayIndex]->citySnapshot);

    currDay = snapshots[dayIndex]->currDay;
}

unsigned Simulation::step() {
    return city->step(getSimulatedDayOfMonth() == 1);
}

unsigned Simulation::step(int steps) {
    unsigned result = 0;

    if (steps > 0) {
        for (int i = 0; i < steps; i++) {
            addSnapshot();
            result += step();
        }
    } else if (steps < 0) {
        size_t targetDay = (currDay < size_t(-steps)) ? 0 : currDay + steps;
        restoreFromSnapshot(targetDay);
    }

    return result;
}

void Simulation::info() const {
    city->printFullInfo();
}

void Simulation::info(size_t x, size_t y) const {
    city->printSpecificBuilding(x, y);
}

void Simulation::info(size_t x, size_t y, const char* name) const {
    city->printSpecificCitizen(x, y, name);
}

void Simulation::save(const char* fileName) {
    addSnapshot();
    FileSaver::saveSimulation(this, fileName);
}

void Simulation::load(const char* fileName) const {
    // FileLoader::loadSimulation(fileName);
}

void Simulation::loadSnapshot(SimulationMemento* snapshot, size_t index) {
    this->snapshots[index] = snapshot;
}

size_t Simulation::getStartingDay() const {
    return startingDay;
}

size_t Simulation::getCurrentDay() const {
    return currDay;
}

size_t Simulation::getSnapshotCount() const {
    return snapshotCount;
}

size_t Simulation::getSnapshotCapacity() const {
    return snapshotCapacity;
}

SimulationMemento** Simulation::getSnapshots() const {
    return snapshots;
}

Simulation::Simulation() 
    : city(nullptr), 
      currDay(0), 
      snapshots(nullptr), 
      snapshotCount(0),
      snapshotCapacity(0) {}

Simulation::Simulation(const Simulation& other) 
    : currDay(other.currDay), 
      startingDay(other.startingDay), 
      snapshotCount(other.snapshotCount),
      snapshotCapacity(other.snapshotCapacity) 
{
    city = new City(*other.city);

    this->snapshots = new SimulationMemento*[snapshotCapacity] {nullptr};
    for (size_t i = 0; i < snapshotCount; i++) {
        this->snapshots[i] = new SimulationMemento(*(other.snapshots[i]));
    }
}

Simulation& Simulation::operator=(const Simulation& other) {
    if (this != &other) {
        delete city;
        city = new City(*other.city);

        SimulationMemento** temp = new SimulationMemento*[other.snapshotCapacity] {nullptr};
        try {
            for (size_t i = 0; i < other.snapshotCount; i++) {
                temp[i] = new SimulationMemento(*other.snapshots[i]);
            }
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;

            for (size_t i = 0; i < other.snapshotCount; i++) {
                delete temp[i];
            }

            delete[] temp;

            throw ex;
        }

        for (size_t i = 0; i < snapshotCount; i++) {
            delete snapshots[i];
        }

        delete[] snapshots;
        snapshots = nullptr;

        snapshots = temp;
        currDay = other.currDay;
        startingDay = other.startingDay;
        snapshotCount = other.snapshotCount;
        snapshotCapacity = other.snapshotCapacity;
    }

    return *this;
}

Simulation::~Simulation() noexcept {
    delete city;
    city = nullptr;

    for (size_t i = 0; i < snapshotCount; i++) {
        delete snapshots[i];
    }

    delete[] snapshots;
    snapshots = nullptr;
}