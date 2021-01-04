/* @JUDGE_ID: ******* 861 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;

struct coord {
    coord(){c=-1;r=-1;};
    coord(int c, int r){this->c = c; this->r = r;};
    coord(int c, int r, bool* dR, bool* dL, int n){
        this->c = c; this->r = r;
        dR[c-r+(n-1)] = 1;
        dL[c+r] = 1;
    };
    void add(bool* dR, bool* dL, int n){
        dR[c-r+(n-1)] = 1;
        dL[c+r] = 1;
    };
    void remove(bool* dR, bool* dL, int n){
        dR[c-r+(n-1)] = 0;
        dL[c+r] = 0;
    };
    int c;  //Column number
    int r;  //Row number
};

//Use backtracking to solve this problem

//Objective:
    //Find the number of ways one can put k bishops on an n x n chessboard such that none of them attack eachother.

//What can be pruned?
    //only one bishop can have it's two diagonals
        //if two bishops share any diagonals then there is no solution
    //light squares cannot interact with dark squares
        //another large help to the runtime complexity

void constructCandidates(coord *candidates, int* numC, int *n, bool *dR, bool *dL, int sx, int sy){
    bool first = true;
    bool isEven;
    *numC = 0;

    //get top of stack's coord position and start there
    //look at every other square starting from sx, sy
    for (int x = sx; x < *n; x++){ //column
        int y;
        if (first){
            y = sy;
            first = false;
            if (sy%2 == 0)
                isEven = true;
            else
                isEven = false;    
        } else {
            isEven = !isEven;
            if (isEven)
                y = 0;
            else
                y = 1;
        }
        for (y; y < *n; y += 2){ //row
            if (!(dR[x-y+(*n)-1] || dL[x+y])){
                candidates[*numC].c = x;
                candidates[*numC].r = y;
                *numC += 1;
            }
        }
    }
}

//This function will return the number of combinations k bishops can have for either even or odd squares on an NxN board in solution
void backtrack(coord* order, int* numOrder, int *numBish, int *edge, bool *dR, bool* dL, long long* solution){
    coord candidates[(*edge)*(*edge)];
    int numC = 0;
    if (*numOrder == *numBish){     //If the number of desired bishops is achieved then iterate the solution counter and exit the function
        *solution += 1;     
    } else {
        if (*numOrder == -1){       //Starts on an odd block
            *numOrder = 0;
            constructCandidates(candidates, &numC, edge, dR, dL, 0, 1);
        } else if (*numOrder == 0){ //Starts on an even block
            constructCandidates(candidates, &numC, edge,dR,dL,0,0);
        } else                      //Continuation from chosen candidate
            constructCandidates(candidates, &numC, edge,dR,dL,(order[*numOrder].c),(order[*numOrder].r));   
        
        //break early if there aren't enough candidates given the number of bishops left
        if (numC < (*numBish - *numOrder))
            return;

        //Move on to new candidate
        for (int x = 0; x < numC; x++){
            *numOrder += 1;
            //push candidate to stack
            order[*numOrder].c = candidates[x].c;
            order[*numOrder].r = candidates[x].r;
            candidates[x].add(dR, dL, *edge);
            //go to next iteration
            backtrack(order, numOrder, numBish, edge, dR, dL, solution);
            //remove candidate to stack
            order[*numOrder].c = -1;
            order[*numOrder].r = -1;
            *numOrder -= 1;
            candidates[x].remove(dR, dL, *edge);
        }
    }
}

//This will take advantage of the fact that there are two different diagonals
//There are even diagonals, and there are odd diagonals
//Even diagonals can never interact with odd diagonals so they can be logically separated
    //Much like in chess how a dark square bishop can never attack a light square piece
void solve(int *maxDiags, int *numBish, int *edge, bool *dR, bool* dL, long long* solution){
    //the coord arrays will keep track of what coords are currently occupied and act as a stack with a static capacity
    //this will be helpful for seeing the most recent candidate
        //it is a hardblock array so the array isn't constantly reallocated whenever something is pushed to the stack
        //this can be done because no chess board will ever have more than 2((2*n)-1) diagonals total
            //splitting the diagonals into dark and light means each array is only ((2*n)-1)
    coord orderB1[(2*(*edge))-1];
    coord orderB2[(2*(*edge))-1];

    int bishFirst = *numBish;
    int bishSecond = 0;
    //0,3; 1,2; 2,1; 3,0
    //0,n ; 1,n-1 ; 2,n-2 ... n,0
    while(bishFirst >= 0){
        long long solOne = 0;
        long long solTwo = 0;
        for (int x = 0; x < *maxDiags; x++){
            dR[x] = 0;
            dL[x] = 0;
        }
        int numOrder1 = 0;
        int numOrder2 = -1;
        if (bishFirst > 0)
            backtrack(orderB1, &numOrder1, &bishFirst, edge, dR, dL, &solOne);
        else
            solOne = 1;
        
        if (bishSecond > 0)
            backtrack(orderB2, &numOrder2, &bishSecond, edge, dR, dL, &solTwo);
        else 
            solTwo = 1;
        
        //cout << "bishFirst = " << bishFirst << "\tbishSecond = " << bishSecond << "\t*numBish = " << *numBish << endl;
        //cout << "SolOne = " << solOne << "\tSolTwo = " << solTwo << "\t*solution = " << *solution << endl;
        *solution = *solution + (solOne*solTwo);

        bishFirst -= 1;
        bishSecond += 1;
    }
}

int main(int argc, char** argv){
    int n;  //Board dimensions (n by n)
    int k;  //Number of bishops
    while(cin >> n >> k){
        if (n == 0 && k == 0)
            break;
        if (n == 0){
            cout << "0" << endl;
        } else if (k > 1 && k >= (2*n)-1){
            cout << "0" << endl;
        } else {
            int boardSize = n*n;
            int maxDiags = (2*n)-1;

            //These diag arrays will keep track of what diagonals are currently occupied
            //Doing dR aka diagRight[Column # - Row # + (n-1)] will see if a diag going to the bottom right exists
                //0 doesn't exist, 1 exists
            //Doing dL aka diagLeft[Column # + Row #] will see if a diag going to the bottom left exists
                //0 doesn't exist, 1 exists
            bool dR[maxDiags]; //Column # - Row # + (n-1) //For a 4x4 grid: 0 in array = -3; 1 in array = -2, ... 6 in array = 3.
            bool dL[maxDiags];  //Column # + Row # //For a 4x4 grid: 0 in array = 0; 1 in array = 1, ... 6 in array = 6
            //The one to one correspondence will let me check if a diag is taken in a single call
            

            long long *solution = new long long(0);
            //clock_t time_req = clock();
            solve(&maxDiags, &k, &n, dR, dL, solution);
            //time_req = clock() - time_req;
            //cout << *solution << " time: " << (float)time_req/CLOCKS_PER_SEC << endl;
            cout << *solution << endl;
            delete solution;
        }
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */