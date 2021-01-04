/* @JUDGE_ID: ******* 10310 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct coord {
    coord(){};
    coord(float x, float y, int type){
        this->x = x;
        this->y = y;
        this->type = type;
    };
    float x = 0;
    float y = 0;
    int type = -1;  //0 = gopher, 1 = dog
};

float distance(coord* start, coord* end){
    float a = start->x - end->x;
    float b = start->y - end->y;
    return sqrtf((a*a)+(b*b));
}

int main(int argc, char** argv){
    int numHoles = 0;
    while (cin >> numHoles){
        float coords[4];
        vector<coord> holes;
        for (int x = 0; x < 4; x++){
            cin >> coords[x];
        }
        coord gS(coords[0], coords[1], 0);
        coord dS(coords[2], coords[3], 1);
        for (int z = 0; z < numHoles; z++){
            float x; float y;
            cin >> x >> y;
            holes.push_back(coord(x,y,2));
        }

        //calculate which hole is closest to the gopher relative to the distance that hole is to the dog
            //gopher will live if it's distance to the hole is less than half the amount of the dogs distance to that same hole.

        int sol = -1;
        for (int x = 0; x < numHoles; x++){
            float gDist = distance(&gS, &holes[x]);
            float dDist = distance(&dS, &holes[x]);
            if (gDist > 0){
                if ((dDist/gDist) >= 2){
                    sol = x;
                    break;
                }
            } else if (gDist == 0){
                sol = x;
                break;
            }
        }
        
        cout.precision(3);
        cout << std::fixed;
        if (sol == -1){
            cout << "The gopher cannot escape." << endl;
        } else {
            cout << "The gopher can escape through the hole at (" << holes[sol].x << "," << holes[sol].y << ")." << endl;
        }
        
    }
    
    return 0;
}

/* @END_OF_SOURCE_CODE */