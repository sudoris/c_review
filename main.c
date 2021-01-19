#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Movie structs will be used to hold the data for Title, Year, Languages, Rating Value 
// for each movie.  
//
// Sample data from csv:
// Title,Year,Languages,Rating Value
// The Incredible Hulk, 2008, [English;Portuguese;Spanish], 6.8
// Sherlock Holmes,2009,[English;French],7.6
struct Movie {
    char *title;
    int year;
    int langsCount;
    char *languages[5];    
    double rating;
    int moviesTotal;

    // next is used to link Movie structs together into a linked list
    struct Movie *next;
};

struct Movie* createMovie(char *currLine) {
    struct Movie *newMovie = (struct Movie*)malloc(sizeof(struct Movie)); 

    char *savePtr;

    // The first token is the Title (str)
    char *token = strtok_r(currLine, ",", &savePtr);
    newMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(newMovie->title, token);

    // The second token is the Year (int)
    token = strtok_r(NULL, ",", &savePtr);
    newMovie->year = atoi(token);     
    
    // The third token is the Languages (array of strs)
    token = strtok_r(NULL, ",", &savePtr);
    // Create substring of token without the brackets [] to make it easier to parse 
    // Must use malloc here to init substring so that it will persist outside of this function
    char *tokenCopy = (char *)malloc((strlen(token)-1)*sizeof(char));   
    memcpy(tokenCopy, &token[1], strlen(token)-2);
    // Add a null terminator at the end of substring just in case
    tokenCopy[strlen(token)-2] = '\0';
    char *langPtr;
    char *langToken;    
    int langCount = 0;
    for (langToken = strtok_r(tokenCopy, ";", &langPtr);
         langToken != NULL;
         langToken = strtok_r(NULL, ";", &langPtr)) {   
        newMovie->languages[langCount] = langToken;
        langCount++;        
    }
    newMovie->langsCount = langCount;   

    // The fourth token is the Rating (float)
    token = strtok_r(NULL, ",", &savePtr);
    // Required by strtod but not used elsewhere
    char *tempPtr;
    newMovie->rating = strtod(token, &tempPtr);

    newMovie->next = NULL;
    
    return newMovie;
}

void printMoviesList(struct Movie *list) {
    while (list != NULL) {   
        printf("Title: %s ", list->title);
        printf("Year: %d ", list->year);
        printf("Languages: %s %s %s %s %s ", list->languages[0], list->languages[1], list->languages[2], list->languages[3], list->languages[4]);
        printf("Rating: %.1f", list->rating);
        printf("\n");
        list = list->next;
    }
    printf("\n");
}

struct Movie* processFile(char *filePath) {
     // Open the specified file for reading only
    FILE *moviesFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;

    // The head of the linked list
    struct Movie *head = NULL;
    // The tail of the linked list
    struct Movie *tail = NULL;

    int currRow = 0;
    // Read the file line by line
    while ((nread = getline(&currLine, &len, moviesFile)) != -1) {   
        currRow++;
        // Ignore first line
        if (currRow == 1) {
            continue;
        }

        // Get a new Movie node corresponding to the current line
        struct Movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL) {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        } else {            
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(moviesFile);

    // Save count of Movie structs created in head
    head->moviesTotal = currRow-1;

    return head;
}

void showOptions() {    
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n\n");
}

int getChoice() {
    int choice;
    printf("Enter a choice from 1 to 4: ");
    scanf("%d", &choice);

    return choice;
}

void handleYearSel(struct Movie *list) {
    printf("Enter the year for which you want to see movies: ");
    int year;
    scanf("%d", &year);

    int matchCount = 0;
    while (list != NULL) {       
        if (list->year == year) {
            matchCount++;
            printf("%s\n", list->title);
        }    
        list = list->next;
    }
    // If no movies were found for year given, display a message
    if (matchCount == 0) {
        printf("No data for movies released in the year %d found\n", year);
    } 
    printf("\n");
}

void handleRatingSel(struct Movie *list) {
    
}

void handleLangSel(struct Movie *list) {

}

int main(int argc, char *argv[]) {        
    char filePath[] = "./movies_sample_1.csv";
    struct Movie *list = processFile(filePath);
    printf("Processed file %s and parsed data for %d movies.\n", filePath, list->moviesTotal);
    // printMoviesList(list);

    // Run program until user enters 4
    while(1) {
        showOptions();
        int selected = getChoice();
        if (selected < 1 || selected > 4) {
            printf("The option you have selected is not available. Please try again.\n\n");
        } else if (selected == 1) {
            handleYearSel(list);
        } else if (selected == 2) {
            handleRatingSel(list);
        } else if (selected == 3) {
            handleLangSel(list);
        } else if (selected == 4) {
            printf("Goodbye.\n");
            break;
        }
    }    

    return EXIT_SUCCESS;     
}