//
//  EEGStorage.cpp
//  hackathon
//
//  Created by bearh on 2017-03-04.
//
//

#include "EEGStorage.hpp"

EEGStorage::EEGStorage(int timePeriod, int mode)
{
    timeLength = timePeriod;
    startTime = std::time(nullptr);
    endTime = startTime+timePeriod;
    type = mode;
}

void
EEGStorage::addItem(EEGItem item)
{
    queue.push_back(item);
}

std::vector<EEGItem> *
EEGStorage::getValues(std::time_t start, std::time_t end)
{
    int i;
    int size = queue.size();
    auto returnVal = new std::vector<EEGItem>;
    if (queue.size() != 0) {
        return returnVal;
    }
    for (i = 0; i <= size; i++){
        if (start <= queue[i].timestamp <= end) {
            returnVal->push_back(queue[i]);
        }
    }
    return returnVal;
}


