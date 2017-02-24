//
// Created by 颜泽鑫 on 24/02/2017.
//

#ifndef HMM_FORWARD_H
#define HMM_FORWARD_H


#include "__config.h"

namespace HMM {
    class ForwardAlg {
    private:
        stateArray __observation;
        stateArray __states;
        probabilityArray __startProbability;
        probabilityMatrix __transitionProbability;
        probabilityMatrix __confusionProbability;

    public:
        ForwardAlg(stateArray _obs,
                   stateArray _states,
                   probabilityArray _start_p,
                   probabilityMatrix _trans_p,
                   probabilityMatrix _emit_p) {
            __observation = _obs;
            __states = _states;
            __startProbability = _start_p;
            __transitionProbability = _trans_p;
            __confusionProbability = _emit_p;
        }

        void compute() {
            probabilityMatrix result(__states.size(), probabilityArray
                    (__observation.size(), 0));

            for (int i = 0; i < __states.size(); ++i) {
                result[i][0] = __startProbability[__states[i]] *
                               __confusionProbability[__states[i]][__observation[0]];
            }

            for (int j = 1; j < __observation.size(); ++j) {
                for (int i = 0; i < __states.size(); ++i) {
                    for (int k = 0; k < __states.size(); ++k) {
                        result[i][j] += result[k][j - 1] *
                                        __transitionProbability[__states[k]][__states[i]];
                    }
                    result[i][j] *=
                            __confusionProbability[__states[i]][__observation[j]];
                }
            }

            for (int m = 0; m < __states.size(); ++m) {
                for (int i = 0; i < __observation.size(); ++i) {
                    cout << result[m][i] << " ";
                }
                cout << endl;
            }

            double prob = 0;
            for (int l = 0; l < __states.size(); ++l) {
                prob += result[l][__observation.size() - 1];
            }
            cout << "Probability is " << prob << endl;
        }
    };
}

#endif //HMM_FORWARD_H
