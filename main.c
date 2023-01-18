#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//CONSTANTS
#define MAX_LENGTH 35
#define MAX_TABLE 50

//TYPES
typedef struct {
    int minutes;
    int hours;
} tTime;

typedef enum {
    G_RATED, PG_RATED, PG13_RATED, R_RATED, NC17_RATED
} tMovieRate;

typedef struct {
    int movieId;
    char title[MAX_LENGTH];
    tTime duration;
    tMovieRate rate;
    float income;//0 or positive
} tMovie;

typedef struct {
    tMovie table[MAX_TABLE];
    int nActualMovies;
} tMovieTable;

//FUNCTIONS
void copyStruct(tMovieTable *movieTable, int i, int j) {
    movieTable->table[i].movieId = movieTable->table[j].movieId;
    movieTable->table[i].duration.hours = movieTable->table[j].duration.hours;
    movieTable->table[i].duration.minutes = movieTable->table[j].duration.minutes;
    movieTable->table[i].income = movieTable->table[j].income;
    movieTable->table[i].rate = movieTable->table[j].rate;
    strcpy(movieTable->table[j].title, movieTable->table[i].title);
}

void addMovie(tMovieTable *movieTable, tMovie movie) {
    int i = 0;
    int pos = 0;
    bool found = false;
    //search for where the movie should be located
    while (i < movieTable->nActualMovies && !found) {
        if (movie.movieId == movieTable->table[i].movieId) {
            found = true;
            pos = i;
        } else {
            ++i;
        }
    }
    //move elements to the right
    if (movieTable->nActualMovies < MAX_TABLE) {
        for (int j = movieTable->nActualMovies - 1; j >= pos; --j) {
            movieTable->table[j + 1] = movieTable->table[j];
        }
        //insert values
        movieTable->table[pos].movieId = movie.movieId;
        movieTable->nActualMovies++;
    }
}

int search(tMovieTable movieTable, int ID) {
    int i = 0;
    bool found = false;
    int pos = -1;
    //search for the same ID
    while (i < movieTable.nActualMovies && !found) {
        if (movieTable.table[i].movieId == ID) {
            found = true;
            pos = i;
        } else {
            ++i;
        }
    }
    return pos;
}

void delete(tMovieTable *movieTable, int ID) {
    int pos = search(*movieTable, ID);
    if (pos != -1) {
        for (int i = pos; i < movieTable->nActualMovies; ++i) {
            //we copy using the copy function for fixing errors
            copyStruct(movieTable, i, i + 1);
        }
        movieTable->nActualMovies--;
    } else {
        printf("The movie Id is not correct or is not found\n");
    }
}

void showMovies(tMovieTable *movieTable, tMovie movie) {
    printf("Number of movies: %d\n", movieTable->nActualMovies);
    for (int i = 0; i < movieTable->nActualMovies; ++i) {
        printf("---Movie %d:\n", i + 1);
        printf("ID: %d\n", movieTable->table[i].movieId);
        printf("Title: %s\n", movieTable->table[i].title);
        printf("Duration: %d Hours, %d minutes\n", movieTable->table[i].duration.hours,
               movieTable->table[i].duration.minutes);
    }
}

void menu(tMovieTable *movieTable, tMovie movie) {
    int option = 0;
    printf("Choose an option:\n");
    printf("0 -> Exit | 1 -> Add movie | 2 -> Search for a movie | 3 -> delete a movie | 4 -> show movies\n");
    scanf("%d", &option);
    //check what user wants
    while (option >= 0 && option <= 4) {
        if (option == 1) {
            //TODO: scan all movie elements
            printf("Movie ID:\n ");
            scanf("%d", &movie.movieId);
            printf("Movie Title:\n ");
            scanf("%s", movie.title);
            printf("Movie duration (h, min):\n ");
            scanf("%d %d", &movie.duration.hours, &movie.duration.minutes);
            printf("Movie income:\n ");
            scanf("%f", &movie.income);

            addMovie(movieTable, movie);
        } else if (option == 2) {
            search(*movieTable, movie.movieId);
        } else if (option == 3) {
            delete(movieTable, movie.movieId);
        } else if (option == 4){
            showMovies(movieTable, movie);
        } else {
            printf("Choose a correct option");
        }
        scanf("%d", &option);
    }
}

int main() {
    tMovieTable movieTable;
    tMovie movie;

    menu(&movieTable, movie);

    return 0;
}