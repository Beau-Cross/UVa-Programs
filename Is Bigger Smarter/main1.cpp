/* @JUDGE_ID: ******* 10131 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct elephant {
    elephant(int i, int f, int s){ id = i; weight = f; iq = s; }
    int id;
    int weight;
    int iq;
};

bool sortFunc(elephant e1, elephant e2){
    return e1.weight < e2.weight || e1.weight == e2.weight && e1.iq < e2.iq;
}

int main(int argc, char** argv){
    vector<elephant> data;
    vector<int> solution;

    int iq; int weight; int x = 0;
    while(cin >> weight >> iq){
        data.push_back(elephant(x, weight, iq));
        x++;
    }

    sort(data.begin(), data.end(), sortFunc);

    //caches the distance achieved to a certain point
    int D[1001];   

    //stores the indexes relating with the above cache
    int R[1001];

    //represents the start of the path
    int start = 0;  

    for (int x = 0; x < data.size(); x++){
        //initialize array values at x
        D[x] = 0; R[x] = 0;

        //Find next largest connecting path and update current distance to prev connecting path
        for (int y = 0; y < x; y++){
            if (D[y] > D[x] && data[y].iq > data[x].iq && data[y].weight < data[x].weight){
                D[x] = D[y];
                R[x] = y;
            }
        }

        //iterate current location distance
        D[x] += 1;

        //if current iteration's location sum is larger than the current longest path, set the prev index to show the top of the current path
        if (D[x] > D[start])
            start = x;
    }
    while(start > 0){
        solution.push_back(data[start].id + 1); //id's are zero based,  but answer is looking for 1 based
        start = R[start];
    }

    cout << solution.size() << endl;
    for (int x = solution.size()- 1; x >= 0; x--){
        cout << solution[x] << endl;
    }

    return 0;
}
/* @END_OF_SOURCE_CODE */