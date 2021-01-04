/* @JUDGE_ID: ******* 846 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv){
    vector<int> solutions;
    int numTestCases;
    //Gather the number of test cases
    cin >> numTestCases;
    for (int x = 0; x < numTestCases; x++){
        //Gather input
        unsigned int first; unsigned int second;
        cin >> first >> second;

        //Solve problem
        unsigned int desiredDistance = second - first;
        unsigned int numSteps = 0;
        unsigned int maxDistance = 0;

        while (maxDistance < desiredDistance){
            maxDistance += ((numSteps/2) + 1);
            numSteps += 1;
        }
        solutions.push_back(numSteps);
    }

    int solSize = solutions.size();
    for (int x = 0; x < solSize; x++){
        cout << solutions[x] << endl;
    }

    return 0;
}
/* @END_OF_SOURCE_CODE */