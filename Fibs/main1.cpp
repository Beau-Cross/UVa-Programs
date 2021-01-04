/* @JUDGE_ID: ******* 101833 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//This struct will define the nodes that I will use to store the numerical values
//I realize the current implementation isn't perfect in terms of space complexity
//Were I to redo this I would change the logic in the bigNum class to utilize base 256 rather than base 10
//As a result some memory is wasted since a char can represent 256 numbers but only 10 are used.
struct numValue {
    numValue(char input){ num = input; };
    char num;
    numValue* next = NULL;
    numValue* prev = NULL;
};

//This struct will hold multiple nodes which will allow me to extend the number size
//This struct also takes care of memory management and comes with functions to interact with this large number
struct bigNum {
    bigNum(){};
    bigNum(int input){
        bool first = true;
        while(input > 0){
            //cout << "Input = " << input << endl;
            int remainder = input % 10;
            //cout << "Remainder = " << remainder << endl;
            if (first){
                //set as head
                head = new numValue(remainder);
                first = false;
            } else {
                //insert into front
                //head -> tmp
                numValue* tmp = head;
                head = new numValue(remainder);
                tmp->prev = head;
                head->next = tmp;
            }
            if (input >= 10)
                input = (input-remainder)/10;
            else
                input = input-remainder;
            
        }
    };
    bigNum(string input){
        int inputSize = input.length();
        //cout << inputSize << endl;
        for (int x = inputSize-1; x >= 0; x--){
            //cout << "I called at x = " << x  << " " << input[x] << endl;
            if (inputSize-1 == x){
                //cout << atoi(&(input.substr(x,1)[0])) << endl;
                head = new numValue((char)atoi(&(input.substr(x,1)[0])));
            } else {
                numValue* tmp = head;
                //cout << atoi(&(input.substr(x,1)[0])) << endl;
                head = new numValue((char)atoi(&(input.substr(x,1)[0])));
                tmp->prev = head;
                head->next = tmp;
            }
        }
    };
    bigNum(const bigNum &copy){
        //cout << "Copy constructor called" << endl;
        numValue* oldCur = copy.head;
        numValue* newCur;
        bool first = true;
        while (oldCur != NULL){
            if (first){
                newCur = new numValue(oldCur->num);
                head = newCur;
                first = false;
            } else {
                numValue* tmp = newCur;
                newCur = new numValue(oldCur->num);
                tmp->next = newCur;
                newCur->prev = tmp;
            }
            oldCur = oldCur->next;
        }
        //cout << "I copied everything!" << endl;
    }
    ~bigNum(){
        while (head != NULL){
            numValue* next = head->next;
            delete head;
            head = next;
        }
        //cout << "I deleted everything!" << endl;
    };
    void doubleNumber(){
        //cout << "Double Number Called" << endl;
        //do math
        //get end
        numValue* cur = head;
        while (cur->next != NULL){
            cur = cur->next;
        }
        int carry = 0;
        while (carry != 0 || cur != NULL){
            //cout << "cur num = " << cur->num << endl;
            if (cur != NULL){
                cur->num = cur->num*2;
                if (carry != 0){
                    cur->num = cur->num + carry;
                }
                if (cur->num >= 10){
                    carry = 1;
                    cur->num = cur->num - 10;
                } else {
                    carry = 0;
                }
                cur = cur->prev;
            } else if (carry != 0) {
                //insert one more
                numValue* tmp = head;
                head = new numValue(carry);
                tmp->prev = head;
                head->next = tmp;
                carry = 0;
                tmp->prev = head;
                cur = NULL;
            }
        }
    }

    //the first is what is added
    static bigNum* add(bigNum* first, bigNum* second){
        //first must be larger
        //cout << "Add called!" << endl;
        //cout << "First = ";
        //first->print();
        //cout << "Second = ";
        //second->print();
        if (second->length() > first->length()){
            //cout << "second was larger" << endl;
            bigNum* tmp = first;
            first = second;
            second = tmp;
        }
        //cout << "Add #0" << endl;
        bigNum* total = new bigNum(*first);

        int carry = 0;
        numValue* firstHead = total->head;
        numValue* secondHead = second->head;
        numValue* firstEnd = firstHead;
        while (firstEnd->next != NULL){
            firstEnd = firstEnd->next;
        }
        numValue* secondEnd = secondHead;
        while (secondEnd->next != NULL){
            secondEnd = secondEnd->next;
        }
        //cout << "Add #1" << endl;
        while (secondEnd != NULL){
            //add firstEnd and secondEnd
            int sum = firstEnd->num + secondEnd->num + carry;
            int remainder = sum % 10;
            if (sum >= 10)
                carry = 1;
            else
                carry = 0;
            
            firstEnd->num = remainder;
            firstEnd = firstEnd->prev;
            secondEnd = secondEnd->prev;
        }
        //cout << "Add #2" << endl;
        while (carry != 0){
            if (firstEnd != NULL){
                //cout << "FE != NULL" << endl;
                //add to firstEnd
                int sum = firstEnd->num + carry;
                if (sum >= 10)
                    carry = 1;
                else
                    carry = 0;
                firstEnd->num = sum%10;
                firstEnd = firstEnd->prev;
            } else {
                //cout << "FE == NULL" << endl;
                //insert new
                int sum = carry;
                numValue* tmp = firstHead;
                firstEnd = new numValue(sum);
                firstEnd->next = tmp;
                tmp->prev = firstEnd;
                carry = 0;
                total->head = firstEnd;
            }
        }
        return total;
    };

    //Check if first is greater than second
        //If first is greater than second then it will return 1
        //If first is less than second then it will return 0
        //If first is equal to second then it will return 2
    static int greaterThanOrEqual(bigNum* first, bigNum* second){
        //cout << "greaterThanOrEqual Called!" << endl;
        //cout << "First = ";
        //first->print();
        //cout << "Second = ";
        //second->print();
        if (first->length() > second->length()){
            return 1;
        } else if (first->length() < second->length()){
            return 0;
        } else {
            numValue* firstHead = first->head;
            numValue* secondHead = second->head;
            while(firstHead != NULL){
                if (firstHead->num > secondHead->num){
                    return 1;
                } else if (firstHead->num < secondHead->num){
                    return 0;
                }
                firstHead = firstHead->next;
                secondHead = secondHead->next;
            }
            return 2;
        }
    }

    void print(){
        numValue* cur = head;
        int idx = 0;
        while (cur != NULL){
            //cout << "\nidx = " << idx << endl;
            cout << to_string((int)cur->num);
            cur = cur->next;
            idx += 1;
        }
        cout << endl;
    };

    int length(){
        int length = 1;
        numValue* cur = head;
        while (cur->next != NULL){
            cur = cur->next;
            length += 1;
        }
        return length;
    }

    string toString(){
        string output = "";
        numValue* cur = head;
        while (cur != NULL){
            output += to_string((int)cur->num);
            cur = cur->next;
        }
        return output;
    }

    numValue* head;
};

int main(int argc, char** argv){
    string first;
    string second;
    while (cin >> first >> second){
        if (first == "0" && second == "0")
            break;

        int numFibs = 0;
        bigNum firstN(first);
        bigNum secondN(second);

        bigNum* start = new bigNum(1);
        bigNum* next = new bigNum(1);
        //bigNum sum(bigNum::add(&start, &next));
        bigNum* sum = new bigNum(1);

        //find where the sum is first in bounds
        while(bigNum::greaterThanOrEqual(sum, &firstN) < 1){
            sum = bigNum::add(start, next);
            delete start; //get rid of the memory that was associated with sum/start
            start = next;
            next = sum;
        }

        //iterate till the sum is out of bounds
        while(bigNum::greaterThanOrEqual(sum, &secondN) < 1){
            sum = bigNum::add(start, next);
            delete start;   //get rid of the memory that was associated with sum/start
            start = next;
            next = sum;
            numFibs += 1;
        }

        //if the last sum is equal to the bound
        if (bigNum::greaterThanOrEqual(sum, &secondN) == 2){
            numFibs += 1;
        }
        cout << numFibs << endl;
    }
    return 0;
}

/* @END_OF_SOURCE_CODE */