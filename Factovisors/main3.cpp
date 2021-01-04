/* @JUDGE_ID: ******* 10139 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>

using namespace std;

struct node {
    node(int num, int count){ this->num = num; this->count = count;};
    int num;
    int count = 0;
};

void addFactor(int num, vector<node> *factors){
    //see if num is in factors
    int idx = -1;
    int factSize = factors->size();
    if (factSize > 0){
        for (int x = 0; x < factSize; x++){
            if (factors->at(x).num == num){
                idx = x;
                break;
            }
        }
    }
    if (idx == -1){ //if it is add
        factors->push_back(node(num, 1));
    } else {        //if it isn't make new node
        factors->at(idx).count = factors->at(idx).count + 1;
    }
}

void factorize(int input, vector<unsigned int> *primes, vector<node> *factors){
    int primesSize = primes->size();
    //cout << "primesSize = " << primesSize << endl;
    //Get prime factors
    while(input != 1){
        int idx = 0;
        while(true){
            if (idx >= primesSize){
                addFactor(input, factors);
                input = 1;
                break;
            } else if (input % primes->at(idx) == 0){
                //cout << "idx = " << idx << endl;
                addFactor(primes->at(idx), factors);
                input /= primes->at(idx);
                break;
            }
            idx += 1;
        }
    }
    //Sum them up
}

//For this function, I used information from math.stackexchange.com
//https://math.stackexchange.com/questions/526095/exponent-of-prime-in-a-factorial
bool hasFactorsInFactorial(int fact, int factor, int goal){
    int numFacts = 0;
    unsigned int x = factor;
    while (x <= fact){
        numFacts += fact/x;
        if (numFacts >= goal)
            return true;
        x *= factor;
    }
    return false;
}

//I used the Sieve of Erathosethenes method to generate all the prime numbers from 2 to sqrt(2^31)
//I learned and acquired this algorithm from:
    //https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
void genPrimeNumbers(vector<unsigned int>* primeNumbers, int max){
    char numArray[max];
    for (int x = 0; x < max; x++){
        numArray[x] = 1;
    }
    numArray[0] = 0;
    numArray[1] = 0;
    numArray[2] = 1;
    int num = 2;
    while(num < max){
        if (numArray[num] == 1){
            for (int z = num * num; z < max; z += num){
                numArray[z] = 0;
            }
        }
        num += 1;
    }
    for (int x = 0; x < max; x++){
        if (numArray[x] == 1)
            primeNumbers->push_back(x);
    }
}

int main(int argc, char** argv){
    vector<unsigned int> primeNumbers;
    genPrimeNumbers(&primeNumbers, 46340);
    int numPrimes = primeNumbers.size();
    int div = 0; int fact = 0;
    while(cin >> fact >> div){
        vector<node> primeFactors;
        bool enough = false;
        if (fact > 1 && div > 1){
            enough = true;
            //factorize the denominator
            factorize(div, &primeNumbers, &primeFactors);
            //see if numerator has sufficient factors to cancel out denominator
                //If it does, then it's divisible
                //If it doesn't, then it's not divisible
            int primeFactorSize = primeFactors.size();
            //cout << "There are this many prime factors: " << primeFactorSize << endl;
            for (int x = 0; x < primeFactorSize; x++){
                if (!hasFactorsInFactorial(fact, primeFactors[x].num, primeFactors[x].count)){
                    enough = false;
                    break;
                }
            }
        }
        if ((enough || div == 0 || div == 1) || ((fact == 0 || fact == 1) && (div == 0 || div == 1))){
            cout << div << " divides " << fact << "!" << endl;
        } else {
            cout << div << " does not divide " << fact << "!" << endl;
        }
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */