/* @JUDGE_ID: ******* 10252 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    string first;
    string second;
    while(getline(cin, first) && getline(cin, second)){
        string answer;
        string tmpS = second;
        //find what characters they have in common
        int sizeF = first.size();
        for (int x = 0; x < sizeF; x++){
            int sizeT = tmpS.size();
            for (int y = 0; y < sizeT; y++){
                if (first[x] == tmpS[y]){
                    answer += first[x];
                    tmpS.erase(y, 1);
                    break;
                }
            }
        }
        //put them in alphabetical order
        int anS = answer.size();
        for (int x = 0; x < anS-1; x++){
            for (int y = x+1; y < anS; y++){
                if (answer[x] > answer[y]){
                    swap(answer[x], answer[y]);
                }
            }
        }
        //print answer
        if (first == " " || second == " "){
            cout << "" << "\n";
        } else {
            cout << answer << "\n";
        }
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */