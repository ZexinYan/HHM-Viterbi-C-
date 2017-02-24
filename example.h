//
// Created by 颜泽鑫 on 24/02/2017.
//

#ifndef HMM_EXAMPLE_H
#define HMM_EXAMPLE_H

#include "viterbi.h"
#include "forward.h"

namespace HMM {
    class WeatherExample{
    private:
        enum Weather{Sunny, Cloudy, Rainy};
        enum Activity{Damp, Soggy, Dry, Dryish};
        stateArray states{Weather::Sunny, Weather::Cloudy, Weather::Rainy};
        stateArray observation{Activity::Damp, Activity::Soggy, Activity::Dry};
        probabilityArray start_probability{0.63, 0.17, 0.20};
        probabilityMatrix transition_probability{{0.5, 0.25, 0.25},
                                                 {0.375, 0.125, 0.375},
                                                 {0.125, 0.675, 0.375}};
        probabilityMatrix confusion_probability{{0.15, 0.05, 0.6, 0.20},
                                                {0.25, 0.25, 0.25, 0.25},
                                                {0.35, 0.5, 0.05, 0.10}};
        stateArray result;
    public:
        WeatherExample() {
            Viterbi viterbi(observation,
                            states,
                            start_probability,
                            transition_probability,
                            confusion_probability);
            ForwardAlg forwardAlg(observation,
                                  states,
                                  start_probability,
                                  transition_probability,
                                  confusion_probability);
            result = viterbi.compute();
            forwardAlg.compute();
        }

        void print() {

            for (auto curState : result) {
                switch (states[curState]) {
                    case Rainy: cout << "Rainy ";
                        break;
                    case Sunny: cout << "Sunny ";
                        break;
                    case Cloudy: cout << "Cloudy ";
                    default:
                        break;
                }
            }

            cout << endl;
        }
    };
}

#endif //HMM_EXAMPLE_H
