#include "./simulation/Simulation.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

const int MAX_COMMAND_LEN = 256;
const int NAME_LEN = 100;
const int FILE_NAME_LEN = 150;

// LINES OF CODE TOTAL: 965

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Simulation sim;

    char command[MAX_COMMAND_LEN];

    bool isSimulationGenerated = false;

    while (true) {
        std::cout << ">> ";
        std::cin.getline(command, MAX_COMMAND_LEN);

        try {
            if (!isSimulationGenerated && !(std::strncmp(command, "generate", 8) == 0)) {
                std::cout << "Please first generate the simulation in order to interact with the application!" << std::endl;
                std::cout << "Usage: generate <n> <m> -- creates a new city with size (n x m).\n";

                continue;
            }

            if (std::strncmp(command, "exit", 4) == 0) {

                break;
                
            } else if (std::strncmp(command, "help", 4) == 0) {
                char subcommand[50];

                if (std::sscanf(command, "help %s", subcommand) == 1) {
                    if (std::strcmp(subcommand, "generate") == 0) {
                        std::cout << "Usage: generate <n> <m> -- creates a new city with size (n x m).\n";
                    } else if (std::strcmp(subcommand, "add") == 0) {
                        std::cout << "Usage: add <x> <y> <name> <job> <happiness> <money> <life>\n";
                    } else if (std::strcmp(subcommand, "remove") == 0) {
                        std::cout << "Usage: remove <x> <y> <name>\n";
                    } else if (std::strcmp(subcommand, "step") == 0) {
                        std::cout << "Usage: step <n> -- advances the simulation by n days. Use 'step' for one day.\n";
                    } else if (std::strcmp(subcommand, "info") == 0) {
                        std::cout << "Usage: info [x] [y] [name]\n";
                        std::cout << "info -- gives information about the whole simulation\n";
                        std::cout << "info <x> <y> -- gives information about a specific building\n";
                        std::cout << "info <x> <y> <name> -- gives information about a specific citizen in a building\n";
                    } else if (std::strcmp(subcommand, "save") == 0) {
                        std::cout << "Usage: save <filename> -- saves the current city state to a file.\n";
                    } else if (std::strcmp(subcommand, "load") == 0) {
                        std::cout << "Usage: load <filename> -- loads a city from a file.\n";
                    } else {
                        std::cout << "Unknown help topic. Try: help generate, help add, etc.\n";
                    }
                } else {
                    std::cout << "Available commands:\n";
                    std::cout << "  generate <n> <m>\n";
                    std::cout << "  add <x> <y> <name> <job> <happiness> <money> <life>\n";
                    std::cout << "  remove <x> <y> <name>\n";
                    std::cout << "  step\n";
                    std::cout << "  step [n]\n";
                    std::cout << "  info\n";
                    std::cout << "  info <x> <y>\n";
                    std::cout << "  info <x> <y> [name]\n";
                    std::cout << "  save <filename>\n";
                    std::cout << "  load <filename>\n";
                    std::cout << "  exit\n";
                    std::cout << "Type 'help <command>' for details.\n";
                }

            } else if (std::strncmp(command, "generate", 8) == 0) {
                size_t n;
                size_t m;

                if (std::sscanf(command, "generate %zu %zu", &n, &m) == 2) {
                    if (isSimulationGenerated) {
                        std::cout << "Simulation has already been generated" << std::endl;
                    } else {
                        sim.generateCity(n, m);
                    }
                } else {
                    std::cout << "Invalid usage. Try: generate <n> <m>\n";
                }

                isSimulationGenerated = true;

            } else if (std::strncmp(command, "add", 3) == 0) {            
                size_t x;
                size_t y;
                size_t happiness;
                size_t salary;
                size_t life;

                char name[NAME_LEN];
                char job[30];

                if (std::sscanf(command, "add %zu %zu %s %s %zu %zu %zu", &x, &y, name, job, &happiness, &salary, &life) == 7) {            
                    if (sim.addCitizen(x, y, name, job, happiness, salary, life)) {
                        std::cout << "Citizen added successfully!" << std::endl;
                    } else {
                        std::cout << "Could not add citizen" << std::endl;
                    }
                } else {
                    std::cout << "Invalid usage. Try: add <x> <y> <name> <job> <happiness> <money> <life>\n";
                }

            } else if (std::strncmp(command, "remove", 6) == 0) {
                size_t x;
                size_t y;
                char name[NAME_LEN];

                if (std::sscanf(command, "remove %zu %zu %s", &x, &y, name) == 3) {
                    if (sim.removeCitizen(x, y, name)) {
                        std::cout << "Citizen removed successfully!" << std::endl;
                    } else {
                        std::cout << "Could not remove citizen" << std::endl;
                    }
                } else {
                    std::cout << "Invalid usage. Try: remove <x> <y> <name>\n";
                }

            } else if (std::strcmp(command, "step") == 0) {

                std::cout << "Total dead citizens after step: " << sim.step(1) << std::endl;

            } else if (std::strncmp(command, "step ", 5) == 0) {
                int stepCount;

                if (std::sscanf(command, "step %d", &stepCount) == 1) {
                    if (stepCount == 0) {
                        std::cout << "Can't move 0 steps" << std::endl;
                    } else if (stepCount > 0) {
                        std::cout << "Total dead citizens after " << stepCount << " steps: " << sim.step(stepCount) << std::endl;
                    } else {
                        sim.step(stepCount);
                    }
                } else {
                    std::cout << "Invalid usage. Try: step <n> (n must be positive)\n";
                }

            } else if (std::strcmp(command, "info") == 0) {

                sim.info();

            } else if (std::strncmp(command, "info ", 5) == 0) {
                size_t x;
                size_t y;
                char name[NAME_LEN];

                int count = std::sscanf(command, "info %zu %zu %s", &x, &y, name);

                if (count == 3) {
                    sim.info(x, y, name);
                } else if (count == 2) {
                    sim.info(x, y);
                } else {
                    std::cout << "Invalid usage. Try: info <x> <y> [name]\n";
                }

            } else if (std::strncmp(command, "save ", 5) == 0) {
                char filename[FILE_NAME_LEN];

                if (std::sscanf(command, "save %s", filename) == 1) {
                    sim.save(filename);
                } else {
                    std::cout << "Invalid usage. Try: save <filename>\n";
                }

            } else if (std::strncmp(command, "load ", 5) == 0) {
                char filename[FILE_NAME_LEN];

                if (std::sscanf(command, "load %s", filename) == 1) {
                    sim.load(filename);
                } else {
                    std::cout << "Invalid usage. Try: load <filename>\n";
                }

            } else {
                std::cout << "Unknown command. Try: generate, add, remove, step, info, save, load, exit.\n";
            }
        } catch (const std::logic_error& ex) {
            std::cout << "Logic error: " << ex.what() << std::endl;
        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        } catch (...) {
            std::cout << "An unknown error occurred.\n";
        }
    }

    return 0;
}