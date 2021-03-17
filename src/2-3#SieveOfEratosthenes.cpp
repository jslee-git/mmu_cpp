//
//  2-3#SieveOfErasthenes.cpp
//
//
//  Created by Jisang lee on 17.03.21.
//
//

#include <iostream>
#include <cstdlib>
#include <limits>
#include <cctype>

using namespace std;

//Total number of primes
int number_of_primes;

//function explanation below
void populate_array(int input, int *primes);

int main ()
{
    int input,
    *primes,
    i;

    string option;

    //Main loop
    while(1) {
        
        //asking for integer
        cout << "Print prime numbers below (q for quit): ";
        cin >> option;
        //check if number
        if (isdigit(option[0])) {
            goto is_number;
        }
        if (option == "q") {
                cout << "Exiting..\n";
                exit(0);
        }
        else {
                cout << "### Wrong Input ###\n\n";
                continue;
        }

        is_number:
        input = stoi(option);
        //check if wrong number input
        if (input == 1) {
            cout << "### 1 is not a prime number ###\n";
            cout << "### Wrong Input ###\n\n";
            continue;
        }
        else if (input < 1) {
            cout << "### Wrong Input ###\n\n";
            continue;
        }

        //sets temporary size for primes array
        primes = new int [input];
        
        //populates array
        populate_array(input, primes);
        
        //prints out prime numbers
        for (i = 0; i < number_of_primes; i++) {
            if (i == number_of_primes - 1)
                cout << *(primes+i) << endl;
            else
                cout << *(primes+i) << ", ";
        }
        //deallocates memory primes and sets to NULL
        delete[] primes;
        primes = 0;
    }
    return 0;
}

/* This function will populate the prime numbers array with the correct size*/
void populate_array(int input, int *primes)
{
    int i,
    j,
    fac,
    *tmp;
    
    //resets number of prime for use
    number_of_primes = 0;
    
    //since there cant be more primes then the maximum number size is set correctly
    tmp = new int [input];

    //allocate array from 2 to the maximum input number
    for (i = 2; i <= input; i++) {
        tmp[i - 2] = i;
    }
    //This loop turns the multiple of a prime to 0
    for (i = 0; i < input; i++) {

        if (tmp[i] != 0) {
            for (j = 2 * (i + 1); j <= input; j += i + 2) {
                if (j == 0)
                    continue;
                else if (j < input)
                    tmp[j] = 0;
            } 
        }
    }
    //assign to array prime
    for (i = 0; i < input - 1; i++) {
        if (tmp[i] != 0) {
            primes[number_of_primes] = tmp[i];
            number_of_primes++;
        }
    }
    primes = new int [number_of_primes];
    
    //dealocates memory and NULL's tmp array
    delete[] tmp;
    tmp = 0;
}
