/* @JUDGE_ID: ******* 10245 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct coord {
    coord(){};
    coord(double x, double y){
        this->x = x;
        this->y = y;
    };
    double x = 0;
    double y = 0;
};

double distance(coord* start, coord* end){
    double a = start->x - end->x;
    double b = start->y - end->y;
    return sqrt((a*a)+(b*b));
}

bool sortByCoord(coord first, coord second){
    return first.x < second.x;
}

int main(int argc, char** argv){
    vector<double> answers;
    int numInputs;
    while(cin >> numInputs){
        if (numInputs == 0)
            break;

        vector<coord> points;
        for (int x = 0; x < numInputs; x++){
            double px; cin >> px;
            double py; cin >> py;
            points.push_back(coord(px,py));
        }
        sort(points.begin(), points.end(), sortByCoord);

        //use this to help keep track of what the best answer is
        //since the max answer is 9,999 it is initialized to 10k.
        double tmpAnswer = 10000;
        for(int x = 0; x < numInputs-1; x++){
            for (int y = x+1; y < numInputs; y++){
                //check if y should continue
                if (points[x].x + tmpAnswer < points[y].x){ //This loop invariance works because x is sorted in ascending order. 
                    break;                                  //Therefore it's guarenteed that the other combinations of points[x] and any points with a higher y value will not be a possible better answer.
                }
                double dist = distance(&points[x], &points[y]);
                if (dist < tmpAnswer){
                    tmpAnswer = dist;
                }
            }
        }
        //answers.push_back(tmpAnswer);
        
        cout.precision(4);
        cout << std::fixed;

        if (tmpAnswer >= 10000.0)
            cout << "INFINITY" << endl;
        else
            cout << tmpAnswer << endl;
        

    }
    /*
    for (int x = 0; x < answers.size(); x++){
        if (answers[x] >= 10000.0)
            cout << "INFINITY" << endl;
        else
            cout << answers[x] << endl;
    }
    */
    return 0;
}

/* @END_OF_SOURCE_CODE */