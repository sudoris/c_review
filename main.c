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
    char **languages;    
    float rating;

    // next is used so that Movie structs can be stored as a linked list
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

    // The third token is the Languages (array of strs)

    // the fourth token is the Rating (float)

    newMovie->next = NULL;

    // strcpy(movie->title, title);
    // movie->title = title;
    // movie->year = year;
    // movie->langsCount = langsCount;
    // movie->languages = languages;
    // movie->rating = rating;    
    return newMovie;
}

struct Movie* processFile(char *filePath) {
    printf("Path is: %s\n", filePath);

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

    // Read the file line by line
    while ((nread = getline(&currLine, &len, moviesFile)) != -1)
    {
        // Get a new Movie node corresponding to the current line
        struct Movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(moviesFile);
    return head;
}

void printMoviesList(struct Movie *list)
{
    while (list != NULL)
    {
        printf("Title: %s\n", list->title);
        list = list->next;
    }
}

struct Node {
    struct Movie *movie;
    struct Node *next;
};

struct Node* createNode() {

};

int main(int argc, char *argv[]) {        
    char filePath[] = "./movies_sample_1.csv";
    struct Movie *list = processFile(filePath);
    printMoviesList(list);

    return EXIT_SUCCESS;     
}