/* @JUDGE_ID: ******* 10110 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv){
    unsigned int input;
    while(cin >> input){
        if (input == 0)
            break;
        unsigned int answer = sqrt(input);
        if (answer * answer == input)
            cout << "yes" << endl;
        else 
            cout << "no" << endl;
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */