/* @JUDGE_ID: ******* 10034 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;


struct coord {
    struct edge {
        edge(coord* coord1, coord* coord2){connectedTo = coord2; if (coord1 != coord2) distance=calcDistance(coord1,coord2); else distance=0; distOutput=distance;};
        static float calcDistance(coord* coord1, coord* coord2){
            float diffX = coord1->x - coord2->x;    //dosen't need abs() because it'll be squared anyways
            float diffY = coord1->y - coord2->y;    //calling abs() would be a waste of cycles
            return sqrtf((diffX * diffX) + (diffY * diffY));    //a^2 + b^2 = c^2   c = sqrt(a^2 + b^2)
        };
        float distance = std::numeric_limits<float>::max(); //distance should always be positive (this is the distance directly to the other vertex)
        float distOutput = std::numeric_limits<float>::max();   //This will save the results (this is the shortest distance going through other points to the vertex)
        coord* connectedTo;
    };
    coord(){x=0.0; y=0.0;};
    coord(float x, float y){this->x=x; this->y=y;};
    float x;
    float y;
    bool visited = false;
    vector<coord::edge> edges;
};

void findMinimumEdge(vector<coord>* coordinates, int &fromNode, int &toNode){
    int numC = coordinates->size();
    float min = std::numeric_limits<float>::max();
    for (int y = 0; y < numC; y++){
        for (int x = 0; x < numC; x++){
            if (coordinates->at(y).edges[x].distOutput < min && (coordinates->at(y).visited && !coordinates->at(x).visited) && x != y){
                min = coordinates->at(y).edges[x].distOutput;
                fromNode = y;
                toNode = x;
            }
        }
    }
    coordinates->at(toNode).visited = true;
}

float solution(vector<coord>* coordinates){
    int numC = coordinates->size();
    float total = 0;
    coordinates->at(0).visited = true;
    for (int z = 0; z < numC-1; z++){
        int fromNode;
        int toNode;
        findMinimumEdge(coordinates,fromNode,toNode);
        total += coordinates->at(fromNode).edges[toNode].distOutput;
    }
    return total;
}

int main(int argc, char** argv){
    vector<float> answers;
    int numTestCases = 0;
    cin >> numTestCases;
    for (int x = 0; x < numTestCases; x++){
        vector<coord> coordinates;
        int numFreckles = 0;
        cin >> numFreckles;

        //create the coords
        for (int y = 0; y < numFreckles; y++){
            float cx; float cy;
            cin >> cx >> cy;
            coordinates.push_back(coord(cx,cy));
        }

        //create the edges
        for (int idx = 0; idx < numFreckles; idx++){
            for (int idy = 0; idy < numFreckles; idy++){
                //idx coord with edges being created
                coordinates[idx].edges.push_back(coord::edge(&coordinates[idx], &coordinates[idy]));
            }
        }
        
        //get answer using greedy algorithm
        float answer = solution(&coordinates);
        answers.push_back(answer);
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    int anSize = answers.size();
    for (int x = 0; x < anSize; x++){
        cout << answers[x] << endl;
        if (x+1 != anSize)
            cout << endl;
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */