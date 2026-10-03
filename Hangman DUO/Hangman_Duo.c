#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#define MAX_LETTER 20
/* What is Hangman Duo?
    Hangman Duo is a game that lets them guess the word, and to whoever the first one to guess the word, or the last to die, that player will win.
    Otherwise, it will result in a draw. There are only 8 lives, each given to the players (16 in all).
    1st: draw an upside down L
    2nd: head
    3rd: body
    4th: left arm
    5th: right arm
    6th: left leg
    7th: right leg
    8th: rope (game over)

    The word is shared, meaning if one correctly guessed a letter, the opponent will see that as well.
    So by that, we introduce a sabotage letter, where can place a letter however we like and insert them into blank positions. It can be only used once per game.
    It will not cost any life. However, it cannot be used when the remaining position is only 1.
    In the next round after the placement of the sabotage letter will it disappear.
    If the sabotage letter is revealed as it is when the opponent correctly guessed the letter, it will be replaced and be notified that the replaced letter is a sabotage letter.
    And if the player used the sabotage letter yet it is the correct one, the sabotage letter will be used.
    */
bool alreadyGuessed(char letter, char *displayedWord, size_t letterCount) {
    for (size_t i = 0; i < letterCount; ++i) {
        if (letter == displayedWord[i])
            return true;
    }

    return false;
}

void displayHang(int lives) {
    if (lives == 8) {
        printf("    -\n");
        printf("    |\n");
        printf("    |\n");
        printf("    |\n");
        printf("    |\n");
        printf("     \n");
    }

    if (lives == 7) {
        printf(" ----\n");
        printf("    |\n");
        printf("    |\n");
        printf("    |\n");
        printf("    |\n");
        printf("     \n");
    }

    if (lives == 6) {
        printf(" ----\n");
        printf("    |\n");
        printf(" o  |\n");
        printf("    |\n");
        printf("    |\n");
        printf("     \n");
    }

    if (lives == 5) {
        printf(" ----\n");
        printf("    |\n");
        printf(" o  |\n");
        printf(" |  |\n");
        printf("    |\n");
        printf("     \n");
    }

    if (lives == 4) {
        printf(" ----\n");
        printf("    |\n");
        printf(" o  |\n");
        printf("/|  |\n");
        printf("    |\n");
        printf("     \n");
    }

    if (lives == 3) {
        printf(" ----\n");
        printf("    |\n");
        printf(" o  |\n");
        printf("/|\\ |\n");
        printf("    |\n");
        printf("     \n");
    }

    if (lives == 2) {
        printf(" ----\n");
        printf("    |\n");
        printf(" o  |\n");
        printf("/|\\ |\n");
        printf(" /  |\n");
        printf("     \n");
    }

    if (lives == 1) {
        printf(" ----\n");
        printf("    |\n");
        printf(" o  |\n");
        printf("/|\\ |\n");
        printf(" /\\ |\n");
        printf("     \n");
    }

    if (lives == 0) {
        printf(" ----\n");
        printf(" |  |\n");
        printf(" o  |\n");
        printf("/|\\ |\n");
        printf(" /\\ |\n");
        printf("     \n");
    }

}

int main() {
    srand(time(NULL));
    char *word_files[] = {"WORDS_5.txt", "WORDS_6.txt", "WORDS_7.txt", "WORDS_8.txt", "WORDS_9.txt"};
    int num_of_letters = rand() % 5;
    FILE *file = fopen(word_files[num_of_letters], "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    char temp[100];
    int wordCount = 0;

    // Count words first
    while (fscanf(file, "%s", temp) != EOF) {
        wordCount++;
    }

    rewind(file); // go back to start

    // Pick a random index
    int randIndex = rand() % wordCount;

    size_t letterCount = (size_t)num_of_letters + 5; /// should be randomly picked based on a number
    char *displayedWord = (char *)calloc(letterCount + 1, sizeof(char));
    char wordToGuess[letterCount + 1];
    int currentIndex = 0;

    while (fscanf(file, "%s", temp) != EOF) {
        if (currentIndex == randIndex) {
            strcpy(wordToGuess, temp); // store word in a string
            break;
        }
        currentIndex++;
    }

    fclose(file);

    /*================================================================================================*/
    for (size_t i = 0; i < letterCount; ++i) {
        displayedWord[i] = '_';
    }

    char guessedLetter[MAX_LETTER];
    size_t lives = 8;
    bool correctLetter = false;
    size_t correctLetterCount = 0;
    while (lives > 0 && correctLetterCount < letterCount) {
        system("clear");
        /// printf("%s\n", wordToGuess);

        displayHang(lives);
        printf("Lives: %zu\n", lives);
        printf("Correct Letter Count: %zu\n", correctLetterCount);

        printf("Word: ");
        for (size_t i = 0; i < letterCount; ++i) {
            printf("%c ", displayedWord[i]);
        }
        printf("\n");

        repeat:
        for (size_t i = 0; i < MAX_LETTER; ++i)
            guessedLetter[i] = '\0';

        printf("Enter a character: %s", guessedLetter);
        scanf(" %s", guessedLetter);

        if (strlen(guessedLetter) > 1) {
            printf("Too many characters. Try again.\n");
            goto repeat;
        }

        if (isalpha(guessedLetter[0]))
            guessedLetter[0] = toupper(guessedLetter[0]);
        else {
            printf("Input not a character. Try again.\n");
            goto repeat;
        }

        if (alreadyGuessed(guessedLetter[0], displayedWord, letterCount)) {
            lives--;
            continue;
        }

        correctLetter = false;
        for (size_t i = 0; i < letterCount; ++i) {
            if (guessedLetter[0] == wordToGuess[i]) {
                displayedWord[i] = guessedLetter[0];
                correctLetter = true;
                correctLetterCount++;
            }
        }

        if (correctLetter == false)
            lives--;
    }

    system("clear");
    displayHang(lives);
    printf("Attempt: %s\n", displayedWord);
    printf("Correct Answer: %s\n", wordToGuess);

    free(displayedWord);
}
