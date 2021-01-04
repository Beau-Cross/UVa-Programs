/* @JUDGE_ID: ******* 10003 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main(int argc, char** argv){
    vector<int> answers;
    int length;
    while(cin >> length){
        if (length == 0)
            break;
        vector<int> cuts;
        cuts.push_back(0);
        int numCuts;
        cin >> numCuts;
        for (int x = 0; x < numCuts; x++){
            int cutLoc;
            cin >> cutLoc;
            cuts.push_back(cutLoc);
        }
        cuts.push_back(length);
        numCuts += 2;

        //create temp storage to remember sub answers
        int temp[51][51];   // number of cuts will always be less than 49 + 2 (extra cuts for 0 and length)
        //compare all of the cutting possibilities of cuts[x] - cuts[y]
        //don't forget to include cuts[x] - 0 and 100 - cuts[numCuts-1]
        for (int x = 1; x < numCuts; x++){
            for (int y = x-1; y >= 0; y--){
                //If there are no cuts to be made the cost is zero (no cuts in between x and y)
                if (y + 1 == x){
                    temp[y][x] = 0;
                } else {
                    //find the minimum cost cut for C(t x, t z) + C(t z, t x)
                    temp[y][x] = std::numeric_limits<int>::max();
                    for (int z = y + 1; z < x; z++){
                        if (temp[y][z] + temp[z][x] < temp[y][x]){
                            temp[y][x] = temp[y][z] + temp[z][x];
                        }
                    }
                    //add cost function (remaining distance of board)
                    temp[y][x] += cuts[x] - cuts[y];
                }
            }
        }
        answers.push_back(temp[0][numCuts-1]);
    }

    for (int x = 0; x < answers.size(); x++){
        cout << "The minimum cutting is " << answers[x] << "." << endl;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */