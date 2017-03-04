/* this implements the training model.
 *
 */

#include <cmath>
#include "training.hpp"
#include <iostream>

TrainingModel::TrainingModel()
{
    stageOfTraining = 0;
    currentPrediction = 0;
}

void
TrainingModel::loadPrev(std::map<int, std::array<MetaModel,4>> prev)
{
    values.insert(prev.begin(), prev.end());
}

void
TrainingModel::addTrainingData(int name, EEGStorage * data)
{
    int j;
    auto v = data->getValues(0, 4294967296);
    for (const auto& i: *v) {
        for (j = 0; j < 4; j++) {
            values[name][j].count += 1;
            values[name][j].mean += i.content[j];
            values[name][j].sd   += pow(i.content[j], 2);
        }
    }
}

int
TrainingModel::evaluateData(EEGStorage * data)
{
    int i, j;
    int a = 0;
    std::array<MetaModel, 4> temp;
    std::array<std::array<float, 4>, 2> compare;
    auto v = data->getValues(0, 4294967296);
    std::map<int, std::array<MetaModel, 4>> local;
    /* calculate for all the states */
    for (i = 0; i < values.size(); i++) {
        for (j = 0; j < values[i].size(); j++) {
            local[i][j].mean = (values[i][j].mean/values[i][j].count);
            local[i][j].sd = (sqrt(values[i][j].sd)/values[i][j].count);
        }
    }
    /* normalize the current one */
    for (const auto& i: *v) {
        for (j = 0; j < 4; j++) {
            temp[j].count = 1;
            temp[j].mean += i.content[j];
            temp[j].sd += pow(i.content[j], 2);
        }
    }
    for(i = 0; i < 4; i++) {
        temp[i].mean = (temp[i].mean)/temp[i].count;
        temp[i].sd = (sqrt(temp[i].sd)/temp[i].count);
    }
    /* compare */
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (temp[j].mean <= local[0][j].mean+local[0][j].sd*local[0][j].blur) {
                a += 1;
            }
        }
    }
    if (a >= 3) {
        return 0;
    } else {
        return 1;
    }
 

}
