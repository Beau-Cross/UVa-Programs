/* @JUDGE_ID: ******* 120 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//flip everything from pos to 0
void flip(vector<int> *stack, int num){
    int pR = stack->size()-num;
    int pL = 0;
    while(pL < pR){
        swap(stack->at(pL), stack->at(pR));
        pL +=1;
        pR -= 1;
    }
}

int rightUnsorted(vector<int> *stack, int max){
    int pos = stack->size()-1;
    if (stack->at(pos) != max){
        return (pos);
    }
    while (pos > 0 && stack->at(pos) > stack->at(pos-1)){
        pos -= 1;
    }
    return pos;
}

int maxUnsortedLoc(vector<int> *stack, int rUns){
    int max = 0;
    int maxLoc = 0;
    while(rUns >= 0){
        if (stack->at(rUns) > max){
            max = stack->at(rUns);
            maxLoc = rUns;
            //cout << "maxLoc = " << maxLoc << " rUns = " << rUns << endl;
        }
        rUns -= 1;
    }
    return maxLoc;
}

int insertPosition(vector<int> *stack, int min, int max){
    int higherNum = stack->at(0);
    while (min < max){
        if (higherNum < stack->at(min)){
            return min-1;
        }
        min += 1;
    }
    return min-1;
}

int main(int argc, char** argv){
    vector<vector<int>> stacks;
    string inputStackS;
    while(getline(cin, inputStackS)){
        if (!std::cin)
            break;
        vector<int> stack;
        //parse string into digits
        int base = 0;
        int lineSize = inputStackS.size();
        for (int x = 0; x < lineSize; x++){
            if (inputStackS[x] == ' '){
                stack.push_back(std::stoi(inputStackS.substr(base, x-base+1)));
                base = x + 1;
            }
        }
        if (base <= lineSize-1){
            stack.push_back(std::stoi(inputStackS.substr(base, lineSize-base+1)));
        }
        stacks.push_back(stack);
    }
        //Begin
        //flip(&stack, stack.size()-2);
        //for (int x = 0; x < stack.size(); x++){
        //    cout << stack[x] << " ";
        //}
        //cout << endl;

        //High Level of the sorting algorithm

        //Find the max unsorted number
        //Flip so it's on the left end of the unsorted area (if it's not already in the leftmost area)
            //Aka flip(&stack, currentPosition)
        //Flip so it's now inserted into the rightmost unsorted area
            //Aka flip(&stack, rmUnsorted)
    for (int z = 0; z < stacks.size(); z++){
        vector<int> stack = stacks[z];
        int stackSize = stack.size();
        int rmUnsorted = stackSize-1;
        int max = 0;

        for (int x = 0; x < stack.size(); x++){
            cout << stack[x] << " ";
        }
        cout << endl;

        //Get max
        for (int x = 0; x < stackSize; x++){
            if (stack[x] > max){
                max = stack[x];
            }
        }

        rmUnsorted = rightUnsorted(&stack, max);
        //cout << "rUns = " << rmUnsorted << endl;
        while (rmUnsorted > 0){
            //cout << "\nrmUnsorted = " << rmUnsorted << endl;
            int MUL = maxUnsortedLoc(&stack, rmUnsorted);
            int MULV = stack[MUL];
            //cout << "MUL = " << MUL << endl;
            //cout << "2" << endl;
            if (MUL > 0){
                flip(&stack, stackSize - MUL);
                cout << stackSize-MUL << " ";
            }

            //where should this higher number go? (higher number will always be at stack[0])
            int inPos = insertPosition(&stack, rmUnsorted, stackSize);
            //cout << "\ninPos = " << inPos << endl;
            flip(&stack, stackSize-inPos);
            //cout << "4" << endl;
            cout << stackSize-inPos << " ";

            //for (int x = 0; x < stack.size(); x++){
            //    cout << stack[x] << " ";
            //}
            //cout << endl;

            rmUnsorted = rightUnsorted(&stack, max);
            //cout << "5" << endl;
        }
        cout << "0\n";

        //for (int x = 0; x < stack.size(); x++){
        //    cout << stack[x] << " ";
        //}
        //cout << endl;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */