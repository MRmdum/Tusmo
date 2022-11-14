#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>



/// <summary>
/// chose a random word/line to search on a dictionnary as each word are on one line
/// </summary>
/// <returns>the word chosen randomly</returns>
char* ChoiceOfARandString() {

    //random number
    int txtSize = 370105;
    srand((unsigned int)time(NULL));
    int r = rand()%txtSize;

    //file initialisation
    FILE* MyFile;
    fopen_s(&MyFile, "./words_alpha.txt", "r");

    //the word to return
    char* word = 0;
    int wordSize = 0;

    //checking if my file opened properly
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

        fclose(MyFile);
    }

    return word;

}

/// <summary>r
/// Set up managing of the game
/// </summary>
/// <returns>returns 0 for a lose and 1 for a win</returns>
int Tusmo() {

    int numberOfTries = 0;
    
    //iniate the word to find
    char * word2find = ChoiceOfARandString();

    printf("%s", word2find); //printing the word for debugg purpose

    
    //giving clue on the very first letter AND counting the size of word2find
    int wordSize = 0;
    for (int i = 0; word2find[i]; i++) {
        if (i == 0)
            printf("%c ", word2find[i]);
        else
            printf("_ ");
        wordSize++;
    }

    

    char* userword = (char*)calloc(wordSize,sizeof(char));

    printf("\nEnter your guess\n");
    int testEqual = 0;

    do {
        //printf("\e[1;1H\e[2J");

        do {
            scanf_s("%s", userword, wordSize);
        } while (!userword); //test of strchr might be removed

        if (!strchr(userword, ' ')) {

            for (int i = 0; word2find[i + 1]; i++)
                if (word2find[i] == userword[i]) {

                    testEqual++; //adding the number of similar letters in the word
                    printf("%c ", word2find[i]); //writing letters in common
                }
                else
                    printf("_ "); //writting missing letters

            //printf("\33[2K\r");

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

    } while (numberOfTries<5); //can be modifie depending on the rules

    free(userword);
    return 0; //returning a lose
}

int main() {

    if (Tusmo())
        printf("\nCongrats ! You won\n");
    else
        printf("\nToo bad you lost\n");

    return 0;
}