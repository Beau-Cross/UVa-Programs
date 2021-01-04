/* @JUDGE_ID: ******* 10038 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class test {
    int x = 0;
};

//This vector will keep the loop invariance that x < x+1
//  if x = x+1
//      then not a jollyjumper
bool addToVector(int val, vector<int> *diffs){
    int cur = 0;
    //cout << "addToVector called" << endl;
    if (diffs->size() > 0){
        while (cur < diffs->size() && diffs->at(cur) <= val){
            //cout << cur << endl;
            if (diffs->at(cur) == val){
                return false;
            }
            cur += 1;
        }
        //cout << "cur = " << cur << " diffs->size = " << diffs->size() << endl;
        diffs->insert(diffs->begin()+cur, val);
    } else {
        diffs->push_back(val);
    }
    //cout << "completed" << endl;
    return true;
}

//Jolly Jumper must contain all abs diff values between 1 to n-1
bool isJollyJumper(int max, vector<int>* diffs){
    //values should start on 1, increment up by 1, and stop (but include) n-1 where n is the max.
    //cout << "1" << endl;
    if (diffs->at(0) != 1)
        return false;
    //cout << "2" << endl;
    int prev = 0;
    for (int x = 0; x < max-1; x++){
        if (prev + 1 == diffs->at(x)){
            prev += 1;
        } else {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv){
    int inLength = 0;
    while (cin >> inLength){
        int cur = 0;
        vector<int>* numbers = new vector<int>();
        vector<int>* diffs = new vector<int>();

        //Take in input, create numbers vector
        while (cur < inLength){
            int tmp = 0;
            cin >> tmp;
            //cout << tmp << endl;
            numbers->push_back(tmp);
            cur += 1;
        }

        //loop through all the numbers
        //calculate the diffs
        bool completed = false;
        int size = numbers->size();
        //cout << "numbersSize = " << size << " inLength = " << inLength << endl;
        for (int x = 0; x < size-1; x++){
            //cout << x << endl;
            if (!addToVector(abs(numbers->at(x)-numbers->at(x+1)), diffs)){
                cout << "Not jolly" << endl;
                completed = true;
                break;
            } 
        }
        //cout << "for completed" << endl;
        if (!completed && size > 1){
            if (isJollyJumper(inLength, diffs)){
                cout << "Jolly" << endl;
            } else {
                cout << "Not jolly" << endl;
            }
        } else if (size == 1){
            cout << "Jolly" << endl;
        }
        delete numbers;
        delete diffs;
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */