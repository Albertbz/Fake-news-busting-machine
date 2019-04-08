#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char title[150];

    printf("Type the title of the article: ");
    fgets(title, 150, stdin); // gets the title from the user


    char delim[] = " "; // deliminator for strtok
    char *token; // token for splitting
    char *titleSplit[15]; // the split title so it's possible to reference each word later
    size_t numberOfWords = 0; // counts number of words in titleSplit to use in for loops
    size_t counter = 0;
    char *pos; // is used for strchr to replace \n with \0 (a null character)

    token = strtok(title, delim); // tokenizes/splits title and puts the value into token

    while(token != NULL){ // does the same for the rest of the title

        if((pos=strchr(token, '\n')) != NULL){ // replaces the \n at the end of var title when it sees it in var token (only happens at the last word; is caused by fgets at the very start)
            *pos = '\0';
        }
        else{
            int tokenLength = strlen(token); // gets the length of the token/word for the for loop

            for(size_t i = 0; i < tokenLength; i++){
                token[i] = tolower(token[i]); // makes the tokens/words of the title lowercase to be comparable with database later
            }
        }

        titleSplit[counter] = token; // puts the value of token into titleSplit

        token = strtok(NULL, delim);

        counter++;
        numberOfWords++;
    }

    char *allWords[150000];
    char allCharacters[1000000];
    int numberOfWordsNews = 0;

    FILE *fPointer;                                            // opens and reads file
    fPointer = fopen("fakeNewsHeadlinesLowercase.txt", "r");

    while(!feof(fPointer)){
        fgets(allCharacters, 1000000, fPointer); // gets all characters from the file
    }

    fclose(fPointer); // closes file

    token = strtok(allCharacters, delim); // changes var token to split all words from the file

    counter = 0;

    while(token != NULL){
        allWords[counter] = token;

        token = strtok(NULL, delim);

        counter++;
        numberOfWordsNews++;
    }

    int occurrencesOfAllWords = 0;

    for(size_t i = 0; i < numberOfWords; i++){ // for loop to check for occurrences of words from title in the file
        int occurrencesOfWord = 0;

        for(size_t j = 0; j < numberOfWordsNews; j++){
            if(strcmp(titleSplit[i], allWords[j]) == 0){
                occurrencesOfWord++;
                occurrencesOfAllWords++;
            }
        }
        printf("\nOccurrences of \"%s\": %d \n", titleSplit[i], occurrencesOfWord); // prints occurrences of each word from the title in the file
    }
    printf("\n\nOccurrences of all words: %d \n", occurrencesOfAllWords); // prints total occurrences of all the words from the title in the file

    return 0;
}
