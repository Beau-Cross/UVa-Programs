/* @JUDGE_ID: ******* 10082 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <sstream>

using namespace std;

static const char keyboard[4][20] = {"ASDFGHJKL;'","QWERTYUIOP[]\\","ZXCVBNM,./","`1234567890-="};
static int keyboardSize[4] = {11, 13, 10, 13};

void correct(char* in){
    for (int x = 0; x < 4; x++){
        int size = keyboardSize[x];
        for (int y = 0; y < size; y++){
            if (keyboard[x][y] == in[0]){
                in[0] = keyboard[x][y-1];
                return;
            }
        }
    }
    return;
};

int main(int argc, char** argv){
    string tmp;
    while (getline(cin, tmp)){
        stringstream ss;
        for (int i = 0; tmp[i]; i++){
            if (tmp[i] == ' ')
                ss << ' ';
            else {
                correct(&tmp[i]);
                ss << tmp[i];
            }
        }
        cout << ss.str() << "\n";
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */