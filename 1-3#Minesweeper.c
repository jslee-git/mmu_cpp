//
//  1-3#Minesweeper.c
//  
//
//  Created by Jisang lee on 14.03.21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//defining minefield dimension limit.
#define MIN 3
#define MAX 10

char *minefield;                        //declaring global pointer as minefield

void generate_minefield(int width, int height, int number_of_mines);

int main()
{
    int height,
    width,
    number_of_mines = 0,                 //0 For random
    max_mines;

    printf("This is a minefield generator\n\n");


    int i, j,
    count = 1;

    while (count < 150) {
        printf("Minefield #%d\n", count);
        printf("0 0 for quit\n");
        printf("Enter height and width (Min %d, Max %d) (w h): ", MIN, MAX);    //Input of height and width
        int is_num = scanf("%d %d", &width, &height);

        if (is_num != 2) {                                                      //Check for input error
            printf("## Error: Wrong input!\n");
            exit(1);
        }
        else if (width == 0 && height == 0) {
            printf("Ending Program...\n");
            exit(0);
        }
        else if (!(MIN <= width && width <= MAX) || !(MIN <= height && height <= MAX)) { //check if input is in range
            printf("## Error: Wrong input! Check Min Max\n");
            continue;
        }

        max_mines = (int)(width*height*50/100);                                 //sets maximum mines to 50% of total and asks input
        printf("How many mines do you want to have?(Max %d, 0 for random): ", max_mines);
        scanf("%d", &number_of_mines);

        if (number_of_mines > max_mines) {                                      //check range
            printf("## Error: Number of Mines exceeding maximum!\n");
            continue;
        }


        minefield = (char *) calloc(height*width, sizeof(char));                //allocate memory of minefield array (2D) with 0

        generate_minefield(width, height, number_of_mines);                                   //minefield generation function


        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                if (minefield[i*width + j] == 48)
                    printf("x ");
                else
                    printf("☐ ");
            }
            printf("\t\t");
            for (j = 0; j < width; j++) {
                if (minefield[i*width + j] == 48)
                    printf("x ");
                else
                    printf("%d ", minefield[i*width + j]);
            }
            printf("\n");
        }
        count++;
        free(minefield);
    }
    printf("Program has reached maximum number of games. Please restart this program..\n");
    return 0;
}


/* This generates the minefield.
Given the height and width and the number of mines
this will create the minefield*/
void generate_minefield(int width, int height, int number_of_mines)
{
    int i, j,
    tmp;
    
    time_t t;
    srand((unsigned) time(&t));                                         //init time for random

    if (number_of_mines == 0) {                                         //randomizes number_of_mines if value is given 0 (12% to 22% of total)
        number_of_mines = (rand() % (int)(floor(height*width*10/100) + 1)) + (int)(floor(height*width*12/100));
    }
    printf("number of mines = %d\n", number_of_mines);


    for (i = 0; i < number_of_mines; i++) {                             //populate minefield
        tmp = rand() % (width*height - 1);

        if (minefield[tmp] == 0)                                        //check if already placed, if not place mine (48 for '0' in ascii)
            minefield[tmp] = 48;
        else                                                            //if mine already exist do again
            i--;
    }



    for (i = 0; i <= height; i++) {                                     //assign proximity numbers to the array
        for (j = 0; j <= width; j++) {


            if (minefield[j + width*i] == 48) {
                int m, n;

                for (m = -1; m < 2; m++) {                              //this will add 1 to each nearby squares
                    for (n = -1; n < 2; n++) {
                        if (m + i < 0 || m + i > (height - 1) || n + j < 0 || n + j > (width - 1)) {    //checks if its out of border
                            continue;
                        }
                        else if (minefield[(i + m)*width + (j + n)] != 48){
                            minefield[(i + m)*width + (j + n)] += 1;
                        }
                        else {
                            continue;
                        }

                    }
                }

            }



        }
    }

} 
