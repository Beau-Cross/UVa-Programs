/* @JUDGE_ID: ******* 10042 C++ */
/* @BEGIN_OF_SOURCE_CODE */
#include <iostream>
#include <vector>

using namespace std;

int radixSum(unsigned int input){
    int total = 0;
    while(input > 0){
        int radix = input % 10;
        total += radix;
        input /= 10;
    }
    return total;

}

int pFacSum(unsigned int input, vector<unsigned int> *primes){
    int total = 0;
    int numIterations = 0;
    int primesSize = primes->size();
    //Get prime factors
    while(input != 1){
        int idx = 0;
        while(true){
            if (idx >= primesSize){
                total += radixSum(input);
                //cout << "Factor = " << input << endl;
                input = 1;
                numIterations += 1;
                break;
            } else if (input % primes->at(idx) == 0){
                total += radixSum(primes->at(idx));
                //cout << "Factor = " << primes->at(idx) << endl;
                input /= primes->at(idx);
                numIterations += 1;
                break;
            }
            idx += 1;
        }
    }
    if (numIterations > 1)
        return total;
    else
        return 0;
    //Sum them up
}

//Using the Sieve of Erathosethenes method I will generate all the prime numbers from 2 to sqrt(INT_MAX)
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
    //cout << "Generating Prime Numbers..." << endl;
    genPrimeNumbers(&primeNumbers, 31622);
    //cout << "Prime Numbers Generated" << endl;
    //init primeNumbers
    int numInputs;
    cin >> numInputs;
    for (int x = 0; x < numInputs; x++){
        unsigned int input;
        cin >> input;
        input += 1;
        while (input < INT32_MAX){
            //cout << "radSum called" << endl;
            int radSum = radixSum(input);
            //cout << "primeFactorSum" << endl;
            int primeFactorSum = pFacSum(input, &primeNumbers);
            //cout << "Input = " << input << " radSum = " << radSum << " primeFactorSum = " << primeFactorSum << endl;
            if (radSum == primeFactorSum){
                cout << input << endl;
                break;
            }
            input += 1;
        }
        //For every number larger than input
            //Find prime factors

            //Get prime factor sum

            //Get input radix sum

            //Compare
                //If both sums are equal then break for and output answer
    }
    return 0;
}
/* @END_OF_SOURCE_CODE */