#include "mem.h"
PageManager::PageManager(int _totalPages) : totalPages(_totalPages) {
    table = new PageTable[totalPages];
}

BuddySystemManager::BuddySystemManager(int _totalFrames) : allocFrames(0), totalFrames(_totalFrames) { 
    table = new BuddySystem[totalFrames];
    block = new bool[totalFrames + 1];
}
