#include <stdio.h>
#include <string.h>

int isValidWord(char word[], int minLen, int maxLen) {
    int len = strlen(word);

    // Check length
    if (len < minLen || len > maxLen) {
        return 0;
    }

    // First letter must be uppercase
    if (!(word[0] >= 'A' && word[0] <= 'Z')) {
        return 0;
    }

    // Check remaining characters
    for (int i = 1; i < len; i++) {
        // Must be lowercase only
        if (!(word[i] >= 'a' && word[i] <= 'z')) {
            return 0;
        }
    }

    return 1;
}

void toUpperCase(char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = word[i] - ('a' - 'A'); // convert to uppercase
        }
    }
}

int main() {
    FILE *input = fopen("words.txt", "r");
    FILE *output = fopen("WORDS_9.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char word[100];

    while (fscanf(input, "%s", word) != EOF) {
        if (strlen(word) == 9 && isValidWord(word, 9, 9)) {
            toUpperCase(word);           // convert the word to all uppercase
            fprintf(output, "%s\n", word);
        }
    }

    fclose(input);
    fclose(output);

    printf("Filtering and capitalizing complete!\n");
    return 0;
}
