/* @JUDGE_ID: ******* 10004 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>

using namespace std;

//vertices are labeled from 0 to n-1

struct node {
    node(){label=-1;visit=-1;};
    node(int val){label=val;};
    int label;
    int visit;
    vector<node*> connected;
};

//If there are any odd number cycles in the graph then it's not bicolorable
void dfs(node* vertex, int visitNum, bool* answer){
    //update current node
    vertex->visit = visitNum;
    visitNum += 1;

    //find new nodes
    int conSize = vertex->connected.size();
    for (int x = 0; x < conSize; x++){
        if (!*answer)
            return;
        if (vertex->connected[x]->visit == -1){ //Not visited yet
            dfs(vertex->connected[x], visitNum, answer);
        } else {    //Visited
            //check if it's an odd distance away
            int distance = visitNum - vertex->connected[x]->visit;
            if (distance%2 == 1){
                *answer = false;
                break;
            }
        }
    }
}

//Utilize a DFS
bool isBicolored(node* vertices, int* n, int* l){
    bool answer = true;
    if (*n > 0 && *l > 0)
        dfs(&vertices[0], 0, &answer);
    return answer;
}

int main(int argc, char** argv){
    int n;  //num vertices
    int l; //num edges (lines)
    while(cin >> n){
        if (n == 0)
            break;
        cin >> l;
        node vertices[n];
        //init vert labels
        for (int x = 0; x < n; x++){
            vertices[x].label = x;
        }
        //gather edges
        int edge1;
        int edge2;
        for (int x = 0; x < l; x++){
            cin >> edge1 >> edge2;
            vertices[edge1].connected.push_back(&vertices[edge2]);
            vertices[edge2].connected.push_back(&vertices[edge1]);
        }

        if (isBicolored(vertices, &n, &l)){
            cout << "BICOLORABLE." << endl; 
        } else {
            cout << "NOT BICOLORABLE." << endl;
        }
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */