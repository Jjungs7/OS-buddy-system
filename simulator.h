#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <string>
// struct to handle multiple events
struct Event {
    int runCycle, pid;
    std::string codeName;
    bool io = false;
};
#endif
