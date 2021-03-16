//
//  1-1#PrimeNumbers.c
//
//
//  Created by Jisang lee on 13.03.21.
//

#include <stdio.h>
#include <stdlib.h>

//Total number of primes
int number_of_primes;

//function explanation below
void populate_array(int input, int *primes);

int main ()
{
    int input,
    *primes,
    i;

    
    //Main loop
    while(1) {
        
        //asking for integer
        printf("Print prime numbers below (q for quit): ");
        int is_number = scanf("%d", &input);
        
        //check if number
        if (is_number != 1) {
            char ch;
            scanf("%c", &ch);
            
            //check if quit
            if (ch == 'q') {
                printf("Exiting..\n");
                exit(0);
            }
            else {
                printf("### Wrong Input ###\n\n");
                continue;
            }
        }
        
        //check if wrong number input
        if (input == 1) {
            printf("### 1 is not a prime number ###\n");
            printf("### Wrong Input ###\n\n");
            continue;
        }
        else if (input < 1) {
            printf("### Wrong Input ###\n\n");
            continue;
        }

        //sets temporary size for primes array
        primes = (int *) malloc(input * sizeof(int));
        
        //populates array
        populate_array(input, primes);
        
        //prints out prime numbers
        for (i = 0; i < number_of_primes; i++) {
            if (i == number_of_primes - 1)
                printf("%d\n", *(primes+i));
            else
                printf("%d, ", *(primes+i));
        }
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
    tmp = (int *) malloc(input * sizeof(int));
    
    for (i = 2; i <= input; i++) {
        
        //resetting fac numbers to 1
        fac = 1;
        
        //checking factors
        for (j = 2; j <= i/2; j++) {
            if (i % j == 0)
                fac++;
            if (fac == 2)
                break;
        }
        
        //if prime number, add to array tmp
        if (fac < 2) {
            tmp[number_of_primes] = i;
            number_of_primes++;
            continue;
        }
    }
    
    //populate to main array
    primes = realloc(primes, number_of_primes * sizeof(int));
    for (i = 0; i < number_of_primes; i++) {
        primes[i] = tmp[i];
    }
}
