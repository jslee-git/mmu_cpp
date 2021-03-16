//
//  1-2#SentenceSwap.c
//  
//
//  Created by Jisang lee on 13.03.21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    int i;
    
    //get 5 sentences
    printf("Enter 5 sentences (MAX 49 Characters):\n\n");
    char sentence[5][51];
    for (i = 0; i < 5; i++)
        fgets(sentence[i], 50, stdin);
    
    //check and swap
    int ch;
    printf("\n");
    for (i = 0; i < 5; i++) {
        for (ch = 0; ch < strlen(sentence[i]); ch ++) {
            if (sentence[i][ch] == 'a')
                printf("%c", 'A');
            else
                printf("%c", sentence[i][ch]);
        }
    }
    return 0;
}
