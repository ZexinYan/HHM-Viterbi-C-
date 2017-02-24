//
// Created by 颜泽鑫 on 24/02/2017.
//

#ifndef HMM_VITERBI_H
#define HMM_VITERBI_H

#include "__config.h"

namespace HMM {
class Viterbi {
    private:
        stateArray __observation;
        stateArray __states;
        probabilityArray __startProbability;
        probabilityMatrix __transitionProbability;
        probabilityMatrix __confusionProbability;

    public:
        Viterbi(stateArray _obs,
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

        stateArray compute() {
            probabilityMatrix vertex(__observation.size(),
                                     probabilityArray(__states.size(), 0));
            pathArray path(__states.size(), stateArray(__observation.size(), 0));

            for (auto each : __states) {
                vertex[0][each] = __startProbability[each] *
                                  __confusionProbability[each][__observation[0]];
                path[each][0] = each;
            }

            for (int i = 1; i < __observation.size(); ++i) {

                pathArray newPath(__states.size(),
                                  stateArray(__observation.size(), 0));

                for (auto curState : __states) {
                    double maxProbability = -1;
                    int state = 0;
                    for (auto preState : __states) {

                        double curProbability = vertex[i - 1][preState] *
                                                __transitionProbability[preState][curState] *
                                                __confusionProbability[curState][__observation[i]];

                        if (curProbability > maxProbability) {

                            maxProbability = curProbability;
                            state = curState;
                            vertex[i][state] = curProbability;

                            newPath[curState] = path[preState];
                            newPath[curState][i] = curState;
                        }
                    }
                }
                path = newPath;
            }

            double maxProbability = -1;
            int state = 0;
            for (auto finalState : __states) {
                if (vertex[__observation.size() - 1][finalState] > maxProbability) {
                    maxProbability = vertex[__observation.size() - 1][finalState];
                    state = finalState;
                }
            }
            return path[state];
        }
    };
} // HMM

#endif //HMM_VITERBI_H
