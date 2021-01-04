/* @JUDGE_ID: ******* 10161 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv){
    unsigned int step;
    while (cin >> step){
        if (step == 0){
            break;
        }
        int it = 0; //current shell number
        int diagNum = 1;
        //base case: diagNum = 1
        //following cases: diagNum = diagNum + (2 * it)
        while(diagNum + it < step){
            it += 1;
            diagNum += (2 * it);
        }
        int diff = step - diagNum;
        int x = it;
        int y = it;
        if (it % 2 == 0){   //+ is left, - is down
            if (diff > 0){
                x -= diff;
            } else if (diff < 0) {
                y += diff;
            }
        } else {    //- is left, + is down
            if (diff > 0){
                y -= diff;
            } else if (diff < 0){
                x += diff;
            }
        }

        cout << (x+1) << " " << (y+1) << endl;
    }
    
    return 0;
}

/* @END_OF_SOURCE_CODE */