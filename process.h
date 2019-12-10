#ifndef PROCESS_H
#define PROCESS_H
#include "mem.h"
#include <string>

// this will have all contents of the process
class Process {
public:
    Process();
    Process(int id, int nInst, std::string *_code, std::string _codeName, int _feedTime, int totalPages);

    // page table
    PageManager *pageTable;

    // Process operations
    bool HasFinished();
    void DecCycle();
    std::string GetNextInst();
    void MoveToNextLine();

    // time allocated when process occupies the cpu
    void AllocTime(int _runTimeQ);
    int GetRunTimeQuantum();

    // time quantum being fed periodically
    void FeedTime(int _feedTimeQ);
    int GetRemTimeQuantum();

    // sleep operations
    void AssignSleepTime(int a);
    bool ToggleSleep(bool s);
    bool IsSleep();

    // io operations
    bool ToggleWait(bool w);
    bool IsIOWait();

    // memory functions
    void IncAllocId();

    // methods that returns process values
    std::string GetCodeName();
    int GetAllocId();
    int GetPid();
    int GetCurrentLine();
    int GetAwakeCycle();

private:
    int pid, allocId, currentLine, totalInst, awakeCycle, runTimeQuantum, remTimeQuantum;
    bool sleep, ioWait;
    std::string codeName;
    std::string *code;
};
#endif
