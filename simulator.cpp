#include <cstdio>
#include <cstring> // strcmp
#include "queue.h"
#include "mem.h"
#include "simulator.h"
#include "system.h"

using namespace std;

int main (int argc, char** argv) {

    /*******************************************/
    /*** gets input for the current test set ***/
    /*******************************************/

    const char *txtFile = argv[1];
    FILE *in;
    in = fopen(txtFile, "r");

    // if Error opening file exit
    if(in == NULL) { 
        printf("File not found\n"); 
        return 0; 
    }

    // get first line
    int totalEventNum, timeQuantum, vmemSize, pmemSize, pageSize, feedFreq, feedSize;
    fscanf(in, "%d\t%d\t%d\t%d\t%d\t%d\t%d\n", &totalEventNum, &timeQuantum, &vmemSize, &pmemSize, &pageSize, &feedFreq, &feedSize);

    // get all instructions
    Event *event;
    event = new Event[totalEventNum];
    int numOfProcesses = 0;
    char op[256];
    for(int i = 0 ; i < totalEventNum ; i++) {
        fscanf(in, "%d\t%s", &event[i].runCycle, op);
        if(strcmp(op, "INPUT") == 0) {
            event[i].io = true;
            fscanf(in, "%d", &event[i].pid);
        } else {
            string cn = op;
            event[i].codeName = cn;
            numOfProcesses++;
        }
    }

    // close file after processing inputs
    fclose(in);

    /*******************************************/
    /************ all inputs processed *********/
    /*******************************************/


    // Instantiates system
    System *system = new System(numOfProcesses, totalEventNum, timeQuantum, vmemSize, pmemSize, pageSize, feedFreq, feedSize, event);
    while(true) {
        // runs one cycle
        system->runCycle();

        // checks if the current test set has ended
        if(system->HasEnded()) break;
    }


    return 0;
}
