//line 736 has been ignored.

#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
    double budget;
    int genre;
    char *name;
    double score;
    int year;
} Movie;


// -------- Read File and keep in struct Functions ----------
// read file and return movies struct with size and return genres with genre size
Movie* read_file(char *file_name, int *size_movie, char ***genres, int *size_genre);
// realloc Movies struct
Movie* realloc_Movie(Movie *arr, int size);
// reallocate genres
char** dynamic_genre(char **genres, int *size, char *search);
// search genres array
int search_genre(char **genres, int size, char *searched);
// search movie
int search_movie(Movie *movies, char *name, int size);

// ----------- Actual program that using struct infos --------------
// Menu function
void menu(Movie *movies, int size_movie, char **genres, int size_genre);
// Part-2 
void sorted_list(Movie *movies, int size_movie, char **genres, int size_genre);
void sort_list_helper(Movie *movies, char **genres);
void sorted_list_budget(Movie *movies, int size_movie,char **genres);
void sorted_list_genre(Movie *movies, int size_movie, char **genres);
void sorted_list_name(Movie *movies, int size_movie, char **genres);
void sorted_list_score(Movie *movies, int size_movie, char **genres);
void sorted_list_year(Movie *movies, int size_movie, char **genres);
//Part-3
void list_genres(char **genres, int size_genres);
//Part 4
void list_through_year(Movie *movies, int size_movie, char **genres);
//Part 5
void list_through_score(Movie *movies, int size_movie, char **genres);
//Part 6
void all_info_movie(Movie *movies, int size_movie, char **genre);
//Part 7
void average_score(Movie *movies, int size_movie);
//Part 8
void freq_genres(Movie *movies, int size_movie, char **genres, int size_genre);

void print_movie_info(Movie *movies, char **genres, int start_index, int end_index);


int main(void)
{
    // Mandatory informations for program
    char **genres;
    int size_genre = 0;
    int size_movie = 0;
    Movie *movies = read_file("Movies.txt", &size_movie, &genres, &size_genre);

    menu(movies, size_movie, genres, size_genre);

}

Movie* read_file(char *file_name,int *size_movie, char ***genres, int *size_genre)
{
    FILE *p = fopen(file_name,"r");
    if (p == NULL)      
    {
        printf("Error\n");
        return NULL;
    }
    //size of movie struct array
    *size_movie = 0;
    Movie *movies = calloc(1, sizeof(Movie));

    // keep genres
    *size_genre = 0;
    *genres = calloc(*size_genre, sizeof(char*));
    for (int i = 0; i < *size_genre; i++)
        *genres[i] = calloc(20, sizeof(char));

    // read line by line with this
    char *line = calloc(200,sizeof(char));
    // keep txt values in infos
    char **infos = calloc(5,sizeof(char*));
    for (int i = 0; i < 5; i++)
        infos[i] = calloc(200,sizeof(char));

    // skip first line that not contains any data, just infos
    fgets (line, 200, p);
    
    int i = 0;
    int temp = -1;
    while(fgets (line, 200, p))
    {
        sscanf(line,"%[^,],%[^,],%[^,],%[^,],%[^,]", infos[0],infos[1],infos[2],infos[3],infos[4]);

        // if this movie already in movies struct
        // take index of this movie and update
        int search_val = search_movie(movies, infos[2], *size_movie);
        if (search_val != -1)
        {
            temp = *size_movie;
            *size_movie = search_val;
        }

        // if there is a value with unkwnon, set value with -1
        if (!strcmp(infos[0],"unknown"))
            movies[*size_movie].budget = -1;
        else
            movies[*size_movie].budget = atoi(infos[0]);

        // if this genre is already in genres array
        // add to genres
        // otherwise do not add
        *genres = dynamic_genre(*genres, size_genre, infos[1]);
        // take index of genres 2d string and assign with genre value
        movies[*size_movie].genre = search_genre(*genres,*size_genre,infos[1]);

        // allocate name data
        movies[*size_movie].name = calloc(100, sizeof(char));
        strcpy(movies[*size_movie].name,infos[2]);
        
        // assign score and year values with converting string double and integer
        movies[*size_movie].score = atof(infos[3]);
        movies[*size_movie].year = atoi(infos[4]);

        // This value used for, if there is same value. Updated and reused old value
        if (temp != -1)
            *size_movie = temp - 1;
            
        // increement size each time and allocate again
        *size_movie += 1;
        movies = realloc_Movie(movies,*size_movie+1);
        // always assign temp value to -1
        temp = -1;
    }
    return movies;  
}

Movie* realloc_Movie(Movie *arr, int size)
{
    Movie *temp = calloc(size,sizeof(Movie));
    for (int i = 0; i < (size-1); i++)
        temp[i] = arr[i];

    free(arr);
    return temp;
    
}

//Implemented function to use instead of realloc for genre
char** dynamic_genre(char **genres, int *size, char *search)
{

    if (search_genre(genres,*size,search) != -1)
        return genres;

    *size += 1;
    char **temp = calloc(*size, sizeof(char*));
    for (int i = 0; i < *size; i++)
        temp[i] = calloc(20, sizeof(char));
        
    for (int i = 0; i < *size-1; i++)
    {
        strcpy(temp[i],genres[i]);
    }
    
    // first, free all dimensions free itself
    for (int i = 0; i < *size-1; i++)
        free(genres[i]);
    free(genres);

    strcpy(temp[*size-1], search);
    return temp;
    
}

int search_movie(Movie *movies, char *name, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!strcmp(movies[i].name, name))
            return i;
    }
    return -1;
}

int search_genre(char **genres, int size, char *searched)
{
    for (int i = 0; i < size; i++)
    {
        if(!strcmp(genres[i],searched))
        {
            return i;
        }
    }
    return -1;
}

void menu(Movie *movies, int size_movie, char **genres, int size_genre)
{
    int option = 0;
    printf("--------- Welcome to best Movie archive Program ---------\n");
    while (1)
    {
        printf("\n1-List of the Sorted Data\n");
        printf("2-List of the Genres\n");
        printf("3-List of the Movie Thorugh The Year\n");
        printf("4-List of the Movie Thorugh The Scores\n");
        printf("5-All information of a Single Movie\n");
        printf("6-Average of the IMDB Scores\n");
        printf("7-Frequency of the Genres\n");
        printf("8-Exit\n\n");
        printf("Please select an option:");
        scanf(" %d", &option);

        switch (option)
        {
        case 1:
            sorted_list(movies, size_movie, genres, size_genre);
            break;

        case 2:
            list_genres(genres, size_genre);
            break;

        case 3:
            list_through_year(movies, size_movie, genres);
            break;

        case 4:
            list_through_score(movies, size_movie, genres);
            break;

        case 5:
            all_info_movie(movies, size_movie, genres);
            break;

        case 6:
            average_score(movies, size_movie);
            break;

        case 7:
            freq_genres(movies, size_movie, genres, size_genre);
            break;
        
        case 8:
            printf("Have a good day. Bye!\n");
            return;
            break;

        default:
            printf("Invalid input. Try Again\n");
            break;
        }

    
    }
    
 }

void sorted_list(Movie *movies, int size_movie, char **genres, int size_genre)
{
    while(1)
    {
        int choice = 0;
        printf("1-Budget (Be aware, Starts with unknwon values)\n2-Genre\n3-Name\n4-Score\n5-Year\n");
        printf("Enter choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            sorted_list_budget(movies, size_movie, genres);
            return;
        case 2:
            sorted_list_genre(movies, size_movie, genres);
            return;
        case 3:
            sorted_list_name(movies, size_movie, genres);
            return;
        case 4:
            sorted_list_score(movies, size_movie, genres);
            return;
        case 5:
            sorted_list_year(movies, size_movie, genres);
            return;
        

        case 6:
            
        
        default:   
            printf("Invalid input. Try Again\n");
            break;
        }
    }
}

void sort_list_helper(Movie *movies, char **genres)
{
    int choice = 0;
    printf("1-Single Selection\n2-Multiple Selection\n");
    printf("Enter choice:");
    scanf(" %d",&choice);

    if (choice == 1)
    {
        int input = 0;
        printf("Enter input:");
        scanf(" %d", &input);
        print_movie_info(movies, genres, input, input+1);
    }
    else if (choice == 2)
    {
        int input1, input2;
        printf("Enter start value:");
        scanf(" %d", &input1);
        printf("Enter end value:");
        scanf(" %d", &input2);

        print_movie_info(movies, genres, input1, input2);    
    }
    else
        printf("Invalid value\n");
}

// it orders start with "unknown" budgets 
void sorted_list_budget(Movie *movies, int size_movie, char **genres)
{
    for (int i = 0; i < size_movie; i++)
    {
        for (int j = i + 1; j < size_movie; j++)
        {
            if (movies[i].budget != -1 && !movies[j].budget != -1 && (movies[i].budget > movies[j].budget))
            {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }

    sort_list_helper(movies, genres);
}

void sorted_list_genre(Movie *movies, int size_movie, char **genres)
{
    for (int i = 0; i < size_movie; i++)
    {
        for (int j = i + 1; j < size_movie; j++)
        {
            if (movies[i].genre > movies[j].genre)
            {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }

    sort_list_helper(movies, genres);
}

void sorted_list_name(Movie *movies, int size_movie, char **genres)
{
    for (int i = 0; i < size_movie; i++)
    {
        for (int j = i + 1; j < size_movie; j++)
        {
            if (strcmp(movies[i].name,movies[j].name) > 0)
            {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }

    sort_list_helper(movies, genres);
}

void sorted_list_score(Movie *movies, int size_movie, char **genres)
{
    for (int i = 0; i < size_movie; i++)
    {
        for (int j = i + 1; j < size_movie; j++)
        {
            if (movies[i].score > movies[j].score)
            {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }

    sort_list_helper(movies, genres);
}

void sorted_list_year(Movie *movies, int size_movie, char **genres)
{
    for (int i = 0; i < size_movie; i++)
    {
        for (int j = i + 1; j < size_movie; j++)
        {
            if (movies[i].year > movies[j].year)
            {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }

    sort_list_helper(movies, genres);
}

void list_genres(char **genres, int size_genres)
{
    for (int i = 0;  i < size_genres; i++)
        printf("%s\n",genres[i]);
}

void list_through_year(Movie *movies, int size_movie, char **genres)
{
    for (int i = 0; i < size_movie; i++)
    {
        for (int j = i + 1; j < size_movie; j++)
        {
            if (movies[i].year > movies[j].year)
            {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }

    printf("Enter a year:");
    int year = 0;
    scanf(" %d", &year);
    int choice = -1;
    printf("Until :0 or Since :1 %d ->",year);
    scanf(" %d",&choice);

    if (choice == 0)
    {
        for (int i = 0; i < size_movie; i++)
        {
            if (movies[i].year < year)
                print_movie_info(movies, genres, i, i+1);
        }
    }
    if (choice == 1)
    {
        for (int i = 0; i < size_movie; i++)
        {
            if (movies[i].year > year)
                print_movie_info(movies, genres, i, i+1);
        }
    }

}

void list_through_score(Movie *movies, int size_movie, char **genres)
{
    for (int i = 0; i < size_movie; i++)
    {
        for (int j = i + 1; j < size_movie; j++)
        {
            if (movies[i].score > movies[j].score)
            {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }

    printf("Enter score:");
    int score = 0;
    scanf(" %d", &score);
    int choice = -1;
    printf("Less :0 or Greater :1 %d ->",score);
    scanf(" %d",&choice);

    if (choice == 0)
    {
        for (int i = 0; i < size_movie; i++)
        {
            if (movies[i].score < score)
                print_movie_info(movies, genres, i, i+1);
        }
    }
    if (choice == 1)
    {
        for (int i = 0; i < size_movie; i++)
        {
            if (movies[i].score > score)
                print_movie_info(movies, genres, i, i+1);
        }
    }

}

void all_info_movie(Movie *movies, int size_movie, char **genre)
{
    char *movieName = calloc(100, sizeof(char));
    printf("Enter a movie name:");
    scanf(" %[^\n]", movieName);
    int val = search_movie(movies,movieName, size_movie);

    if (val == -1)
        printf("There is no Movie name %s\n",movieName );
    else
        print_movie_info(movies, genre, val, val+1);
    
}

void average_score(Movie *movies, int size_movie)
{
    double sum = 0;
    for (int i = 0; i < size_movie; i++)
        sum += movies[i].score;
    
    double average = sum / (double)size_movie;
    printf("Average imdb score is %lf\n", average);
}

void freq_genres(Movie *movies, int size_movie, char **genres, int size_genre)
{
    for (int i = 0; i < size_genre; i++)
    {
        int sum = 0;
        printf("%s -> ",genres[i]);
        for (int j = 0; j < size_movie; j++)
        {
            if (movies[j].genre == i)
                sum++;
        }
            
        printf("%d\n",sum);
    }
}

void print_movie_info(Movie *movies, char **genres, int start_index, int end_index)
{
    int flag = 1;
    for (int i = start_index; i < end_index; i++)
    {
        flag = 0;
        if (movies[i].budget == -1)
        {
            printf("unknown\t%20s\t%-60s\t%12lf\t%12d\n",genres[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
        }
        else
        {
            printf("%-15lf\t%15s\t%-60s\t%12lf\t%12d\n",movies[i].budget, genres[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
        }
    }

    // if there is no movie with this index range
    if (flag)
    {
        printf("Invalid\n");
    }
}

