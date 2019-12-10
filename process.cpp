#include "process.h"
#include <sstream>
#include <string>
Process::Process() { }
Process::Process(int id, int nInst, std::string *_code, std::string _codeName, int _feedTime, int totalPages) : pid(id), allocId(0), currentLine(0), totalInst(nInst), awakeCycle(0), runTimeQuantum(0), remTimeQuantum(_feedTime), sleep(false), ioWait(false), code(_code) { 
    pageTable = new PageManager(totalPages);
    codeName = _codeName;
    for(int i = 0 ; i < totalPages ; i++) {
        pageTable->table[i].usingPages = 0;
        pageTable->table[i].allocId = -1;
        pageTable->table[i].valid = false;
        pageTable->table[i].frameIdx = -1;
    }
}


// process operations
bool Process::HasFinished() { return currentLine >= totalInst; }

// decreases cpu and process's allocated time quantum
void Process::DecCycle() {
    runTimeQuantum--;
    remTimeQuantum--;
}

// gets operation
std::string Process::GetNextInst() { 
    if(currentLine < totalInst) {
        std::string line = code[currentLine];
        return line;
    }
    return "";
}

// move cursor to next line
void Process::MoveToNextLine() { currentLine++; } 


// cpu allocated time
void Process::AllocTime(int _runTimeQ) { runTimeQuantum = _runTimeQ; }

int Process::GetRunTimeQuantum() { return runTimeQuantum; }


// time quantum being fed
void Process::FeedTime(int _feedTimeQ) { remTimeQuantum += _feedTimeQ; }

int Process::GetRemTimeQuantum() { return remTimeQuantum; }


// sleep operations
void Process::AssignSleepTime(int a) { awakeCycle = a; }

bool Process::ToggleSleep(bool s) {
    if(sleep == s) {
        return false; // no changes made
    } else {
        sleep = s;
        return true; // changes made
    }
}

bool Process::IsSleep() { return sleep; }

//io operations
bool Process::ToggleWait(bool w) {
    if(ioWait == w) {
        return false; // no changes made
    } else {
        ioWait = w;
        return true; // changes made
    }
}

bool Process::IsIOWait() { return ioWait; }


// memory functions
void Process::IncAllocId() { allocId++; }

// return process values
std::string Process::GetCodeName() { return codeName; }

int Process::GetAllocId() { return allocId; }

int Process::GetPid() { return pid; }

int Process::GetCurrentLine() { return currentLine; }

int Process::GetAwakeCycle() { return awakeCycle; }
