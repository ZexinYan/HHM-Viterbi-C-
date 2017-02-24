//
// Created by 颜泽鑫 on 24/02/2017.
//

#ifndef HMM_CONFIG_H
#define HMM_CONFIG_H

#include <iostream>
#include <vector>
using namespace std;

namespace HMM {

    typedef vector<int> stateArray;
    typedef vector<vector<int>> pathArray;
    typedef vector<double> probabilityArray;
    typedef vector<vector<double>> probabilityMatrix;

}

#endif //HMM_CONFIG_H
