/* @JUDGE_ID: ******* 10029 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>

using namespace std;

struct node {
    node(){label=-1;visit=-1;maxLen=-1;};
    node(string val){label=val;visit=-1;maxLen=-1;};
    string label;
    int visit;
    int maxLen;
    vector<node*> next;
    vector<node*> prev;
};

void dfs(node* dict, int* length, int iteration){
    //update current node
    dict->visit = iteration;
    //cout << "iteration = " << iteration << " dict->maxlen = " << dict->maxLen << endl;
    
    if (dict->maxLen == -1 || dict->maxLen < iteration){
        //cout << "1" << endl;
        dict->maxLen = iteration;
    } else if(dict->maxLen > iteration) {
        //cout << "2" << endl;
        return;
    }
    
    //cout << "iteration = " << iteration << " at " << dict->label << " nextSize = " << dict->next.size() << endl;
    //find next node
    int nextSize = dict->next.size();
    if (nextSize > 0){
        iteration += 1;
        for (int x = 0; x < nextSize; x++){
            dfs(dict->next[x], length, iteration);
        }
    } else {
        //if there's no next node see if it's the longest
        if (iteration > *length){
            //cout << iteration << " > " << *length << endl;
            *length = iteration;
        }
    }
}

bool isEditStep(string* first, string* second){
    //cout << "first = " << *first << " second = " << *second << endl;
    int numDif = 0;
    int fL = first->length();
    int sL = second->length();
    if (fL == sL){
        for (int x = 0; x < fL; x++){
            if (first->at(x) != second->at(x)){
                numDif += 1;
                if (numDif > 1){
                    return false;
                }
            }
        }
    } else if (abs(fL - sL) == 1){
        //cout << "this should call" << endl;
        int x1 = 0;
        int x2 = 0;
        while (x1 < fL && x2 < sL){
            //cout << x1 << " " << x2 << endl;
            if (first->at(x1) != second->at(x2) && x1 == x2){
                if (fL > sL)
                    x1 += 1;
                else 
                    x2 += 1;
            } else if (first->at(x1) != second->at(x2)){
                return false;
            } else {
                x1 += 1;
                x2 += 1;
            }
        }
    } else if (abs(fL - sL) > 1){
        return false;
    }
    return true;
}

int main(int argc, char** argv){
    int n = 0;
    string word;
    vector<node> dictionary;
    while(cin >> word){
        dictionary.push_back(node(word));
        n += 1;
    }
    //cout << "Building paths... n = " << n << endl;
    if (n > 1){
        //build paths
        for (int x = 1; x < n; x++){
            //cout << "x = " << x << endl;
            for (int y = x - 1; y >= 0; y--){
                //cout << "x = " << x << " y = " << y << endl;
                //see if word connects
                if (isEditStep(&dictionary[x].label, &dictionary[y].label)){
                    //cout << "this is an edit step" << endl;
                    //x is child, y is parent
                    dictionary[x].prev.push_back(&dictionary[y]);
                    dictionary[y].next.push_back(&dictionary[x]);
                }

            }
        }
        //cout << "paths were built" << endl;
        //find which path is longest
        //call only root nodes
            //they have no parents
        int longest = 0;
        
        for (int x = 0; x < n; x++){
            //cout << "x = " << x << endl;
            if (dictionary[x].prev.size() == 0){
                int length = 0;
                dfs(&dictionary[x], &length, 1);
                if (length > longest)
                    longest = length;
            }
        }
        /*
        cout << "show the paths" << endl;
        for (int x = 0; x < n; x++){
            cout << "label = " << dictionary[x].label << " x = " << x << " numNext = " << dictionary[x].next.size() << " numPrev = " << dictionary[x].next.size() << endl;
        }*/
        cout << longest << endl;
    } else {
        cout << "0" << endl;
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */