/* @JUDGE_ID: ******* 10041 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(int argc, char** argv){
    int numTestCases = 0;
    vector<int> answers;
    while(cin >> numTestCases){
        int idx = 0;
        while (idx < numTestCases){
            vector<int> streets;
            int numRel = 0;
            int idy = 0;
            cin >> numRel;
            while (idy < numRel){
                int st;
                cin >> st;
                streets.push_back(st);
                idy += 1;
            }
            std::sort(streets.begin(), streets.end());
            int mid = 0;

            if (streets.size() % 2 == 0){
                mid = (streets[streets.size()/2]);
            } else {
                mid = (streets[(streets.size()-1)/2]);
            }

            int total = 0;
            for (int x = 0; x < streets.size(); x++){
                total += abs(mid - streets[x]);
            }
            answers.push_back(total);
            idx += 1;
        }
        //print all out
        int size = answers.size();
        for (int x = 0; x < size; x++){
            cout << answers[x] << "\n";
        }
        answers.clear();
    }

    return 0;
}
/* @END_OF_SOURCE_CODE */