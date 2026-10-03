#include <stdio.h>

int main() {
    FILE *file = fopen("Common_5_Letter_Words.txt", "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    char temp[100];
    int wordCount = 0;

    while (fscanf(file, "%s", temp) != EOF) {
        wordCount++;   // each fscanf reads a word
    }

    fclose(file);

    printf("Number of words in file: %d\n", wordCount);
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    FILE *file = fopen("output.txt", "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    char temp[100];
    int wordCount = 3103;

    // Count words first
    while (fscanf(file, "%s", temp) != EOF) {
        wordCount++;
    }

    rewind(file); // go back to start

    // Pick a random index
    srand(time(NULL));
    int randIndex = rand() % wordCount;

    char selectedWord[100];
    int currentIndex = 0;

    while (fscanf(file, "%s", temp) != EOF) {
        if (currentIndex == randIndex) {
            strcpy(selectedWord, temp); // store word in a string
            break;
        }
        currentIndex++;
    }

    fclose(file);

    printf("Random word: %s\n", selectedWord);

    return 0;
}

*/
