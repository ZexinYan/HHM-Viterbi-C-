//
// Created by 颜泽鑫 on 24/02/2017.
//

#ifndef HMM_FORWARDANDBACKWARD_H
#define HMM_FORWARDANDBACKWARD_H

#include "__config.h"

namespace HMM {
    class ForwardAndBackward {
    private:
        stateArray __observation;
        stateArray __states;
        probabilityArray __startProbability;
        probabilityMatrix __transitionProbability;
        probabilityMatrix __confusionProbability;

        probabilityMatrix __alpha;
        probabilityMatrix __beta;
        probabilityMatrix __gamma;

    public:
        ForwardAndBackward(stateArray _obs,
                            stateArray _states,
                            probabilityArray _start_p,
                            probabilityMatrix _trans_p,
                            probabilityMatrix _emit_p) {
            __observation = _obs;
            __states = _states;
            __startProbability = _start_p;
            __transitionProbability = _trans_p;
            __confusionProbability = _emit_p;

            __alpha = probabilityMatrix(__observation.size(),
                                        probabilityArray(__states.size(), 0));
            __beta = probabilityMatrix(__observation.size(),
                                        probabilityArray(__states.size(), 0));
            __gamma = probabilityMatrix(__observation.size(),
                                        probabilityArray(__states.size(), 0));
        }

        void calculateForward() {
            for (int curObs = 0; curObs < __observation.size(); ++curObs) {
                for (int curState = 0; curState < __states.size(); ++curState) {
                    if (curObs == 0){
                        __alpha[curObs][curState] = __startProbability[curState] *
                                __confusionProbability[curState][__observation[curObs]];
                        continue;
                    }
                    for (int preState = 0; preState < __states.size(); ++preState) {
                        __alpha[curObs][curState] += __alpha[curObs - 1][preState] *
                                __transitionProbability[preState][curState];
                    }
                    __alpha[curObs][curState] *=
                            __confusionProbability[curState][__observation[curObs]];
                }
            }
        }

        void calculateBackward() {
            for (int curObs = (int)__observation.size() - 1; curObs >= 0;
                 ++curObs) {
                for (int curState = 0; curState < __states.size(); ++curState) {
                    if (curObs == __observation.size() - 1) {
                        __beta[curObs][curState] = 1;
                        continue;
                    }
                    for (int preState = 0;
                         preState < __states.size(); ++preState) {
                        __beta[curObs][curState] +=
                                __transitionProbability[preState][curState] *
                                __confusionProbability[curState][__observation[curObs + 1]]
                                * __beta[curObs + 1][preState];
                    }
                }
            }
        }

        void calculateGamma() {
            for (int curObs = 0; curObs < __observation.size(); curObs++) {
                double denominator = 0;
                for (int curState = 0; curState < __states.size(); ++curState) {
                    denominator += __alpha[curObs][curState] *
                            __beta[curObs][curState];
                }
                for (int curState = 0; curState < __states.size(); ++curState) {
                    __gamma[curObs][curState] =
                            __alpha[curObs][curState] *
                            __beta[curObs][curState] / denominator;
                }
            }
        }

    };
}

#endif //HMM_FORWARDANDBACKWARD_H
