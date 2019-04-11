#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char title[300];

    printf("Type the title of the article: ");
    fgets(title, 300, stdin); // gets the title from the user


    double percentFake;
    double percentReal;
    char delim[] = " "; // deliminator for strtok
    char *token; // token for splitting
    char *titleSplit[20]; // the split title so it's possible to reference each word later
    size_t numberOfWords = 0; // counts number of words in titleSplit to use in for loops
    size_t counter = 0;
    char *pos; // is used for strchr to replace \n with \0 (a null character)
    size_t j = 0;

    for(size_t i = 0; title[i] != '\0'; i++){ // for loop to remove everything that isn't a letter or number
        while(!((title[i] >= 'a' && title[i] <= 'z') || (title[i] >= 'A' && title[i] <= 'Z') || (title[i] >= '0' && title[i] <= '9') || title[i] == '\0' || title[i] == ' ')){
            for(j = i; title[j] != '\0'; j++){
                title[j] = title[j+1];
            }
            title[j] = '\0';
        }
    }
    printf("Words getting tested: ");
    puts(title);

    token = strtok(title, delim); // tokenizes/splits title and puts the value into token

    while(token != NULL){ // does the same for the rest of the title

        if((pos=strchr(token, '\n')) != NULL){ // replaces the \n at the end of var title when it sees it in var token (only happens at the last word; is caused by fgets at the very start)
            *pos = '\0';
        }

        int tokenLength = strlen(token); // gets the length of the token/word for the for loop

        for(size_t i = 0; i < tokenLength; i++){
            token[i] = tolower(token[i]); // makes the tokens/words of the title lowercase to be comparable with database later
        }

        titleSplit[counter] = token; // puts the value of token into titleSplit

        token = strtok(NULL, delim);

        counter++;
        numberOfWords++;
    }

    char *allWordsFake[90000];
    char *allWordsReal[90000];
    char allCharactersFake[600000];
    char allCharactersReal[600000];
    double numberOfWordsFake = 0;
    double numberOfWordsReal = 0;

    FILE *fPointer;                         // opens and reads file with fake news
    fPointer = fopen("fakeNewsWords.txt", "r");

    while(!feof(fPointer)){
        fgets(allCharactersFake, 600000, fPointer); // gets all characters from the file with fake news
    }

    fclose(fPointer); // closes file with fake news

    //////////////////////////////

    fPointer = fopen("realNewsWords.txt", "r"); // opens and reads file with real news

    while(!feof(fPointer)){
        fgets(allCharactersReal, 600000, fPointer); // gets all characters from the file with real news
    }

    fclose(fPointer); // closes file with real news

    token = strtok(allCharactersFake, delim); // changes var token to split all words from the file with fake news

    counter = 0;

    while(token != NULL){
        allWordsFake[counter] = token;

        token = strtok(NULL, delim);

        counter++;
        numberOfWordsFake++;
    }

    int occurrencesOfAllWordsFake = 0;

    for(size_t i = 0; i < numberOfWords; i++){ // for loop to check for occurrences of words from title in the file
        int occurrencesOfWord = 0;

        for(size_t j = 0; j < numberOfWordsFake; j++){
            if(strcmp(titleSplit[i], allWordsFake[j]) == 0){
                occurrencesOfWord++;
                occurrencesOfAllWordsFake++;
            }
        }
        printf("\nOccurrences of \"%s\" in fake news file: %d \n", titleSplit[i], occurrencesOfWord); // prints occurrences of each word from the title in the file
    }

    printf("\n");

    ////////////////////////////////////

    token = strtok(allCharactersReal, delim); // changes var token to split all words from the file with real news

    counter = 0;

    while(token != NULL){
        allWordsReal[counter] = token;

        token = strtok(NULL, delim);

        counter++;
        numberOfWordsReal++;
    }

    int occurrencesOfAllWordsReal = 0;

    for(size_t i = 0; i < numberOfWords; i++){ // for loop to check for occurrences of words from title in the file
        int occurrencesOfWord = 0;

        for(size_t j = 0; j < numberOfWordsReal; j++){
            if(strcmp(titleSplit[i], allWordsReal[j]) == 0){
                occurrencesOfWord++;
                occurrencesOfAllWordsReal++;
            }
        }
        printf("\nOccurrences of \"%s\" in real news file: %d \n", titleSplit[i], occurrencesOfWord); // prints occurrences of each word from the title in the file
    }

    printf("\n\nOccurrences of all words in fake news file: %d \n", occurrencesOfAllWordsFake); // prints total occurrences of all the words from the title in the file
    percentFake = ((occurrencesOfAllWordsFake/numberOfWordsFake)*100);
    printf("Occurrences in percent: %.2lf%% \n", percentFake);
    printf("\nOccurrences of all words in real news file: %d \n", occurrencesOfAllWordsReal); // prints total occurrences of all the words from the title in the file
    percentReal = ((occurrencesOfAllWordsReal/numberOfWordsReal)*100);
    printf("Occurrences in percent: %.2lf%% \n", percentReal);


    if(percentFake > percentReal){
        printf("\nThis article might be Fake - read with caution! \n");
    }
    else if(percentReal > percentFake){
        printf("\nThis article is possibly Real. \n");
    }
    else{
        printf("\nThe answer is unclear. \n");
    }

    return 0;
}
