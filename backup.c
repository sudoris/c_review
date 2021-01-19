#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Title,Year, Languages, Rating Value
// The Incredible Hulk, 2008, [English;Portuguese;Spanish], 6.8
struct Movie {
    char *title;
    int year;
    int langsCount;
    char **languages;    
    float rating;
};

// struct Movie* createMovie(char *title, int year, int langsCount, char **languages, float rating) {
//     struct Movie *movie = (struct Movie*)malloc(sizeof(struct Movie)); 
//     // strcpy(movie->title, title);
//     movie->title = title;
//     movie->year = year;
//     movie->langsCount = langsCount;
//     movie->languages = languages;
//     movie->rating = rating;    
//     return movie;
// };

struct Movie* createMovie(char *currLine) {
    struct Movie *newMovie = (struct Movie*)malloc(sizeof(struct Movie)); 

    char 

    // strcpy(movie->title, title);
    // movie->title = title;
    // movie->year = year;
    // movie->langsCount = langsCount;
    // movie->languages = languages;
    // movie->rating = rating;    
    return newMovie;
};

struct Node {
    struct Movie *movie;
    struct Node *next;
};

struct Node* createNode() {

};

int main() {
    // struct Movie movie;
    // strcpy(movie.title, "The Incredible Hullk");
    // movie.year = 2008;    
    char *langs[] = {"English", "Portuguese", "Spanish"};
    int langsCount = sizeof(langs)/sizeof(char *);
    // movie.languages = langs;
    // movie.langsCount = langsCount;
    // movie.ptrLanguages = langs;
    // printf("location of langs: %p\n", &langs);
    // printf("location of ptr %p\n", movie.ptrLanguages);
    // movie.languages = langs;
    
    // int i;
    // for (i = 0; i < langsCount; i++) {        
    //     // strcpy(movie.languages[i], langs[i]);
    //     movie.languages[i] = langs[i];
    // }



    // movie.rating = 8.7;

    

    // printf("Name of movie is: %s\n", movie.title);
    // printf("First language is %s\n", movie.languages[0]);

    FILE *filePtr;     
    filePtr = fopen("./movies_sample_1.csv", "r");    

    if (filePtr == NULL) {
        printf("Error opening file!");
        exit(1);
    } else {    // create linked list of movies by parsing data from file
        char *currLine = NULL;
        size_t len = 0;
        ssize_t nread;
        int row = 0;    

        // The head of the linked list
        struct Movie *head = NULL;
        // The tail of the linked list
        struct Movie *tail = NULL;    

        while ((nread = getline(&currLine, &len, filePtr)) != -1)
        {
            // Get a new student node corresponding to the current line
            struct Movie *movie = createMovie(currLine);

            // Is this the first node in the linked list?
            if (head == NULL)
            {
                // This is the first node in the linked link
                // Set the head and the tail to this node
                head = movie;
                tail = movie;
            }
            else
            {
                // This is not the first node.
                // Add this node to the list and advance the tail
                tail->next = movie;
                tail = movie;
            }
        }



        // while(fgets(readBuffer, sizeof(readBuffer), filePtr) != NULL) {
        //     row++;            
        //     if (row == 1) {
        //         continue;
        //     }            
        //     // create movie struct using data from current line
        //     // Title,Year,Languages,Rating Value
        //     char *savePtr;

        //     char *token = strtok_r(readBuffer, ",", &savePtr);            
        //     printf("Token is: %s\n", token);
        //     char *title = calloc(strlen(token) + 1, sizeof(char));
        //     strcpy(title, token);
        // }
    }

    // char testes[] = "The Incredible Hulk";
    // struct Movie* myMovie = createMovie(testes, 2008, 3, langs, 8.7);
    // printf("Name of movie is: %s\n", myMovie->title);
    // printf("First language is %s\n", myMovie->languages[0]);

    

    // struct Node *head = NULL;
    // head = (struct Node*)malloc(sizeof(struct Node)); 
    // head->movie = &movie;
    // head->next = head;
    
    // printf("test node %s\n", head->movie->languages[0]);

    return 0;
}