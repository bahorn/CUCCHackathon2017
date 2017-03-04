#ifndef EEGStorage_hpp
#define EEGStorage_hpp

#include <stdio.h>
#include <vector>
#include <array>
#include <queue>
#include <ctime>

class EEGItem {
    public:
        std::time_t timestamp;
        std::array<float, 4> content;
};

class EEGStorage {
    public:
        EEGStorage(int timePeriod, int mode);
        void addItem(EEGItem item);
        std::vector<EEGItem> * getValues(std::time_t start, std::time_t end);
    
        /* meta */
        int type;
        std::time_t startTime;
        std::time_t endTime;
        int timeLength;
    private:
        std::vector<EEGItem> queue;
};

#endif /* EEGStorage_hpp */
