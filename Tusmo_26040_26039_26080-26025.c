#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>

/*

This is the C project of
Pierre-Olivier Coudert (26040)
Noemie Munoz (26039)
Claire Brilleaud (26025)
Mathis Juret-rafin (26080)

*/

/// <summary>
/// chose a random word/line to search on a dictionnary as each word are on one line
/// </summary>
/// <returns> the word chosen randomly</returns>
char* ChoiceOfARandString() {

    //random number = the word who will be chosen randomly
    int txtSize = 370105;
    srand((unsigned int)time(NULL)); //initialisation of the random function
    int r = rand()%txtSize;


    //file initialisation
    FILE * MyFile = fopen("./words_alpha.txt", "r");
    //go to the file "words_alpha.txt"

    //the word to return
    char* word = 0;
    int wordSize = 0;

    //checking if the file opened properly
    if (MyFile) {

        int count = 0;

        //buffer for the line read by fgets(...)
        char line[256];

        //loop to go over the all file
        while (fgets(line, sizeof line, MyFile) != NULL)
        {
            //stopping on the random line defined before
            if (count == r)
            {
                word = line;
                break;
            }
            else
            {
                count++;
            }
        }

        fclose(MyFile);  //close the file
    }

    return word;

}

/// <summary>r
/// Set up managing of the game
/// </summary>
/// <returns>returns 0 for a lose and 1 for a win</returns>
int Tusmo() {

    printf("   | Hello dear player,\n   | Welcome on our game : TUSMO !\n\n");

    ///rules///
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    //15 = white letters
    printf("Rules:\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    //2 = dark green letters
    printf("Correct letter & right place\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
    //3 = turquoise letters
    printf("Correct letter & wrong place\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    printf("Wrong letter\n\n");
    printf("Be careful, you only have 6 chances.\n\n");
    ///////////

    bool stop = true;
    int cnt = 0;

    int numberOfTries = 0;

    //iniate the word to find with the function above
    char * word2find = ChoiceOfARandString();

    printf("word: %s\n", word2find); //printing the word for debugg purpose


    //giving clue on the very first letter AND counting the size of word2find
    int wordSize = 0;

    for (int i = 0; word2find[i]; i++) {
        if (i == 0)
            printf("%c ", word2find[i]);
        else
            printf("_ ");  //print a line for each letter of the word
        wordSize++;
    }
    printf("%d\n",wordSize-1);

    char userword[wordSize];  //initialisation of the word to enter

    printf("\nEnter your guess:\n");
    int testEqual = 0;

    do {

        do {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            do{
              stop = true;
              scanf("\n%s", userword, wordSize);
              cnt = strlen(userword);

              printf("\n");

              if(cnt != wordSize-1){
                stop = false;
                printf("\nWrong size! Please, try again.\n");
              }

          } while(stop==false);
              printf("\n");

        } while (!userword); //test of strchr might be removed

        if (!strchr(userword, ' ')) {  //delete space

            for (int i = 0; word2find[i + 1]; i++)
                if (word2find[i] == userword[i]) {

                    testEqual++; //adding the number of similar letters in the word
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
                    printf( "%c ", userword[i]); //writing letters in common
                }
                else
                    if(strchr(word2find,userword[i])){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
                        printf( "%c ", userword[i]); //writting letter present in the word but at the wrong place
                    }
                    else{
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                        printf( "%c ", userword[i]); //writting missing letters
                    }


            printf("\n");

            if (testEqual == wordSize - 1) //comparing the number of similar characters except the last one cause it's ended by '\n' due to dictionnary's parsing
            {
                free(userword);
                return 1; //returning a win
            }

            //set up for next lap
            testEqual = 0;
            numberOfTries++;
        }

    } while (numberOfTries<7); //can be modifie depending on the rules

    return 0; //returning a lose
}

void delay(int delay){ // Let the console open

int now=time(NULL);
int later=now+delay;
while(now<=later)now=time(NULL);
}

int main() {

    if (Tusmo())
        printf("\nCongrats ! You won\n");
    else
        printf("\nToo bad you lost\n");

    delay(3000);
    return 0;
}
