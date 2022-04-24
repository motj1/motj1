// #include <stdio.h>
#include <vector>
#include <fstream>
#include <cmath>

std::vector<unsigned long> array;

void findPrimes(unsigned long& number){
    array.reserve(number/(std::log(number)-1));

    array.__emplace_back(3);

    bool prime;
    unsigned long i, j;

    for (j = 5; j != number; j += 2){
        prime = true;

        for (i = 0; array[i] * array[i] <= j; i++){
            if (j%array[i] == 0){
                prime = false;
                break;
            }
        }
        if (prime){
            array.__emplace_back(j);
        }
    }
}


int main(){
    unsigned long number = 10000000101;

    findPrimes(number);
    std::ofstream myfile;
    myfile.open ("Primes_10billion.txt");

    myfile << 2 << "\n";
    for (unsigned int i = 0; i < array.size(); i ++){
        myfile << array[i] << "\n";
    }
    myfile << array.size();

    array.clear();

    myfile.close();

    return 0;
}
