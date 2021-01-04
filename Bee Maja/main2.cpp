/* @JUDGE_ID: ******* 10182 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Things to note about Willi's system
    For a given shell (a shell is just a ring of hexagons that are at the same radius, the center has a shell number of 0)
        The max number is equal to prev + (6r)
        The min number is equal to prev + (6r-6)
            where r is the radius starting at 0

*/
int main(int argc, char** argv){
    int destN;
    while (cin >> destN){
        int it = 0; //this will tell what shell the target lies in
        int shellMax = 1;   //this will keep track of the max value of the current shell
        int shellQ0 = 1;
        //while goal greater than current shell max
        while (destN > shellMax){
            it += 1;
            shellMax += (6*it);
            shellQ0 += (6*it - 5);
        }

        //cout << "destN = " << destN << " shellMax = " << shellMax << " it = " << it << " shellQ0 = " << shellQ0 << endl;
        //see which of the 6 sextants the destN is in [0,5]
        int qLoc = 0;
        while (shellQ0 <= shellMax){
            if (destN <= shellQ0){
                break;
            }
            shellQ0 += it;
            qLoc += 1;
        }

        //cout << "qLoc = " << qLoc << endl;

        int shift = shellQ0 - destN;
        int x = 0;
        int y = 0;

        switch (qLoc)
        {
        case 0:
            x = 0;
            y = it;
            if (shift > 0){
                x += shift;
                y -= shift;
            }
            break;
        case 1:
            x = -1*it;
            y = it;
            if (shift > 0){
                x += shift;
            }
            break;
        case 2:
            x = -1*it;
            y = 0;
            if (shift > 0){
                y += shift;
            }
            break;
        case 3:
            x = 0;
            y = -1*it;
            if (shift > 0){
                x -= shift;
                y += shift;
            }
            break;
        case 4:
            x = it;
            y = -1*it;
            if (shift > 0){
                x -= shift;
            }
            break;
        case 5:
            x = it;
            y = 0;
            if (shift > 0){
                y -= shift;
            }
            break;
        
        default:
            break;
        }
        
        cout << x << " " << y << endl;
    }

    return 0;
}
/* @END_OF_SOURCE_CODE */