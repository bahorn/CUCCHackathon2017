//
//  training.hpp
//  hackathon
//
//  Created by bearh on 2017-03-04.
//
//

#ifndef training_hpp
#define training_hpp

#include "EEGStorage.hpp"

#include <stdio.h>
#include <string>
#include <map>
#include <utility>

class MetaModel {
    public:
        int count = 0;
        float mean = 0;
        float sd = 0;
        float blur = 0.75;
};

class TrainingModel {
    public:
        TrainingModel();
        void addTrainingData(int time, EEGStorage * data);
        int evaluateData(EEGStorage * data);
        void loadPrev(std::map<int, std::array<MetaModel,4>> prev);
    private:
        
        int stageOfTraining;
        int currentPrediction;
        std::map<int, std::array<MetaModel, 4>> values;
    
};

#endif /* training_hpp */
