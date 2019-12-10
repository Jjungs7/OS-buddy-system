#ifndef MEM_H
#define MEM_H
// data each page in the page table will have
struct PageTable {
    int allocId, frameIdx, usingPages;
    bool valid;
};

// data each frame in the buddy system will have
struct BuddySystem {
    int pid, allocId;
};

// this data structure will have the total pages
// and the page table for the process
struct PageManager {
    PageManager(int _totalPages);
    int totalPages;
    PageTable *table;
};

// this data structure will have the total frames
// along with num of allocated frames and
// blocks when alloc/dealloc frames
struct BuddySystemManager {
    BuddySystemManager(int _totalFrames);
    int allocFrames, totalFrames;
    bool *block;
    BuddySystem *table;
};
#endif
