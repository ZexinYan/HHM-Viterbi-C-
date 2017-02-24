#include <iostream>
#include <vector>
using namespace std;

namespace HMM {

    typedef vector<int> stateArray;
    typedef vector<vector<int>> pathArray;
    typedef vector<double> probabilityArray;
    typedef vector<vector<double>> probabilityMatrix;

    class Viterbi {
    private:
        stateArray __observation;
        stateArray __states;
        probabilityArray __startProbability;
        probabilityMatrix __transitionProbability;
        probabilityMatrix __emissionProbability;

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
            __emissionProbability = _emit_p;
        }

        stateArray compute() {
            probabilityMatrix vertex(__observation.size(),
                                     probabilityArray(__states.size(), 0));
            pathArray path(__states.size(), stateArray(__observation.size(), 0));

            for (auto each : __states) {
                vertex[0][each] = __startProbability[each] *
                                  __emissionProbability[each][__observation[0]];
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
                                                __emissionProbability[curState][__observation[i]];

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

    class WeatherExample{
    private:
        enum Weather{Rainy, Sunny};
        enum Activity{walk, shop, clean};
        stateArray states{Weather::Rainy, Weather::Sunny};
        stateArray observation{Activity::walk, Activity::shop, Activity::clean};
        probabilityArray start_probability{0.6, 0.4};
        probabilityMatrix transition_probability{{0.7, 0.3},
                                                 {0.4, 0.6}};
        probabilityMatrix emission_probability{{0.1, 0.4, 0.5},
                                               {0.6, 0.3, 0.1}};
        stateArray result;
    public:
        WeatherExample() {
            Viterbi viterbi(observation,
                            states,
                            start_probability,
                            transition_probability,
                            emission_probability);
            result = viterbi.compute();
        }

        void print() {

            for (auto curState : result) {
                switch (states[curState]) {
                    case Rainy: cout << "Rainy ";
                        break;
                    case Sunny: cout << "Sunny ";
                        break;
                    default:
                        break;
                }
            }

            cout << endl;
        }
    };
}

int main() {
    HMM::WeatherExample example;
    example.print();
    return 0;
}