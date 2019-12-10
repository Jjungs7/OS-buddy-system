#ifndef SYSTEM_H
#define SYSTEM_H
#include "queue.h"
#include "stack.h"
#include "process.h"
#include "mem.h"
#include "simulator.h"
#include <string>

/*******************************************************/
/*********** struct to handle multiple events **********/
/*******************************************************/
struct MultEvents {
    int *arr;
    int size;
};

/*******************************************************/
/******** This will be the kernel of the program *******/
/*******************************************************/
class System {
public:
    System(int nP, int tE, int tQ, int vmS, int pmS, int pS, int fF, int fS, Event *_e);

    // cycle related
    void runCycle(); // runs current cycle
    int getCycle(); // returns current cycle
    void incCycle(); // increases cycle by 1

    // system methods
    int CheckAndAllocateTimeQuantum(); // gives time quantum for all processes periodically
    int AwakeSleepingProcesses(); // checks for sleeping processes
    MultEvents OrderEvents(); // gets event(s)
    int runEvent(); // runs events of current cycle
    Process* Scheduler();  // RR Scheduler
    int Fetch(); // fetchs operations of current process
    int Execute(); // executes operations
    void UpdateBlock(); // updates block for buddy system
    void PrintStatusTxt(); // prints system.txt

    // checks if there are no more works to do
    bool HasEnded();

    // Process operations
    int MemoryAllocation(int arg);
    int MemoryAccess(int arg);
    int MemoryRelease(int arg);
    void NonMemInst(); // does nothing
    void Sleep(int arg);
    void IOWait();

    // Memory related methods
    int HandlePageFault(int pid, int a); // handles page faults
    int FreeMemory(); // frees memory by LRU
    int CollectMemory(int pid, int a); // collects victimized memory
    bool PageInFrame(Process *c, int a); // checks if the page is allocated

private:
    int op, arg, lastQuantumAllocationCycle, currentProcesses, cycle, numOfProcesses, currentEvent, finishedProcesses;
    int totalEventNum, timeQuantum, vmemSize, pmemSize, pageSize, feedFreq, feedSize;
    bool end;
    Event *events;
    Queue *runQueue, *ioWaitQueue, *sleepQueue;
    Process **processList;
    Process *currentProcess;
    LRUStack *lru;
    BuddySystemManager *buddySystem;
};
#endif
