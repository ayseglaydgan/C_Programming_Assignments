#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// first struct
typedef struct Movie_Budget
{
    int budget;
    int year;
    char *name;
    struct Movie_Budget *next;
}Movie_Budget;

// second struct
typedef struct Movie_Name
{
    char *genre;
    char *name;
    double score;
    struct Movie_Name *next;

}Movie_Name;

// third struct for keeoing genre informations
// in one place
typedef struct Genre
{
    char *name;
    int freq;
    struct Genre* next;
}Genre;



// read file and fill two 
void read_file(char *file_name, Movie_Name **head1, Movie_Budget **head2);

// add new node to movie_budget struct
// implement instructions that said
// add sorted due to year and budget
void create_NewNode_Budget(Movie_Budget **head, char **infos);

// add new node to Movie_name struct
void create_NewNode_Name(Movie_Name **head, char **infos);

// update lists if already in list
int update_Budget(Movie_Budget* head, char **infos);
int update_Name(Movie_Name* head, char **infos);

// detect all genres from movies
void detect_genres(Movie_Name *head_movie, Genre **head_genre);

// search all list
// if display value is 1
// print founded info
int search_movie_budget(Movie_Budget *head, char *name, int display);
int search_movie_name(Movie_Name *head, char *name, int display);

void swap_budget(Movie_Budget *first, Movie_Budget *second);
void swap_name(Movie_Name *first, Movie_Name *second);

// search through genre struct, if given genre is exist return 1;
int search_genre(Genre *head_genre, char *genre);

// print whole list
void print_List_Budget(Movie_Budget *head);
void print_List_Name(Movie_Name *head);
// print whole genre list

// *** HomeWork Parts ***
void menu(Movie_Budget *head_budget, Movie_Name *head_name, Genre *head_genre);

// PART 1
void sorted_list(Movie_Budget *head_budget, Movie_Name *head_name);
void sorted_list_budget(Movie_Budget *head_budget, Movie_Name *head_name);
void sorted_list_year(Movie_Budget *head_budget, Movie_Name *head_name);
void sorted_list_name(Movie_Budget *head_budget, Movie_Name *head_name);
void sorted_list_genre(Movie_Budget *head_budget, Movie_Name *head_name);
void sorted_list_score(Movie_Budget *head_budget, Movie_Name *head_name);
// helper function for printing values
void sort_list_helper(Movie_Budget *head_budget, Movie_Name *head_name, int type);
void print_movie_info(Movie_Budget *head_budget, Movie_Name *head_name, int type,  int start_index, int end_index);

// PART 2 - 7
void print_genres(Genre *head_genre, int freq);

// PART 3
void list_through_year(Movie_Budget *head_budget, Movie_Name *head_name);
// PART 4
void list_through_score(Movie_Budget *head_budget, Movie_Name *head_name);

// PART 5
void all_info_movie(Movie_Budget *head_budget, Movie_Name *head_name);

// PART 6
void average_score(Movie_Name *head_name);

int main()
{
    // create heads for structs
    Movie_Budget *head_budget = NULL;
    Movie_Name *head_name = NULL;
    Genre *head_genre = NULL;

    // read file and fill lists
    read_file("Movies.txt", &head_name, &head_budget);
    // find genres and frequencies
    detect_genres(head_name, &head_genre);

    // call menu and send important infoos
    menu(head_budget, head_name, head_genre);

}

void read_file(char *file_name, Movie_Name **head1, Movie_Budget **head2)
{
    FILE *p = fopen(file_name,"r");
    if(p == NULL)
    {
        printf("Error\n");
        return;
    }
    
    // allocate a string to keep lines
    char *line = (char*)calloc(200,sizeof(char));

    // keep all infos in a string array
    char **infos = (char**) calloc(5,sizeof(char*));    
    for (int i = 0; i < 5; i++)
        infos[i] = (char *) calloc(100, sizeof(char));

    // skip first line that contains header infos
    fgets(line,200,p);

    int i = 0;
    // iterate all file 
    while (fgets(line,200,p))
    {
        // use sscanf (string scanf) to split data into infos array
        sscanf(line,"%[^,],%[^,],%[^,],%[^,],%[^,]", infos[0],infos[1],infos[2],infos[3],infos[4]);

        if (update_Budget(*head2, infos));
        else create_NewNode_Budget(head2, infos);

        if (update_Name(*head1, infos));
        else create_NewNode_Name(head1, infos);
        
    }   
}

void create_NewNode_Budget(Movie_Budget **head, char **infos)
{
    Movie_Budget *newNode = (Movie_Budget *)malloc(sizeof(Movie_Budget));

    // allocate space for name
    newNode->name = (char *)malloc(sizeof(char)*100);
    strcpy(newNode->name,infos[2]);

    // assign budget
    newNode->budget = atoi(infos[0]);
    // assign year
    newNode->year = atoi(infos[4]);
    // assign next node to NULL
    newNode->next = NULL;
    
    // to adding infos with sorted orted, keep previous
    Movie_Budget *temp_prev = NULL;
    Movie_Budget *temp = *head;

    int flag = 0;

    // if head is null
    // assign head
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    // Iterate till last node to NULL
    while(temp != NULL)
    {
        // if find a place to replacement
        // set flag value to 1
        if(temp->year < newNode->year)
        {
            flag = 1;

            // if temp_prev is not null
            // asign to this
            if(temp_prev != NULL)
                temp_prev->next = newNode;
            // temp_prev is null
            // this means it belong to head
            else
                *head = newNode;
            // always assign to temp
            newNode->next = temp;
            // break when finish
            break;
        }
        // if years are equal, sort due to budget
        // repeat same thing above
        else if (temp->year == newNode->year)
        {
            if(temp->budget < newNode->budget)
            {
                flag = 1;

                if(temp_prev != NULL)
                    temp_prev->next = newNode;
                else
                    *head = newNode;

                newNode->next = temp;
                break;
            }
        }
        
        // iterate prev to temp
        temp_prev = temp;
        // assign temp to next
        // always on temp_prev
        temp = temp->next;
    }
    // if flag assigned to zero
    // asign temp_prev to newNode
    if (flag == 0)
        temp_prev->next = newNode;

}

void create_NewNode_Name(Movie_Name **head, char **infos)
{
    Movie_Name *newNode = (Movie_Name *)malloc(sizeof(Movie_Name));

    // allocate space for name
    newNode->name = (char *)malloc(sizeof(char)*100);
    strcpy(newNode->name,infos[2]);

    // assign budget
    newNode->genre = (char *)malloc(sizeof(char)*100);
    strcpy(newNode->genre, infos[1]);
    // assign year
    newNode->score = atof(infos[3]);
    // assign next node to NULL
    newNode->next = NULL;
    
    
    if(*head == NULL)
         *head = newNode;
    else
    {
        Movie_Name *temp = *head;

        //last node's next address will be NULL.
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        //add the newNode at the end of the linked list
        temp->next = newNode;
    }
}

void print_List_Budget(Movie_Budget *head)
{
    if(head != NULL)
    {
        if (head->budget == 0)
            printf("Unknow\t%d\t%s\n",head->year,head->name);
        else
            printf("%d\t%d\t%s\n",head->budget,head->year,head->name);
        print_List_Budget(head->next);
    }
}

void print_List_Name(Movie_Name *head)
{
    if(head != NULL)
    {
        printf("%s\t%lf\t%s\n",head->genre,head->score,head->name);
        print_List_Name(head->next);
    }
}

void print_genres(Genre *head_genre, int freq)
{
    if(head_genre != NULL)
    {
        printf("%s",head_genre->name);
        if (freq == 1)
            printf(" %d", head_genre->freq);
        printf("\n");
        print_genres(head_genre->next, freq);
    }
}

int update_Budget(Movie_Budget* head, char **infos)
{
   int result = 0;
   while (head != NULL)
   {
       if(strcmp(head->name,infos[2]) == 0)
       {
           head->budget = atoi(infos[0]);
           head->year = atoi(infos[4]);
           result = 1;
           // printf("Updated Budget Struct %s\n", infos[2]);
           break;
       }
       head = head->next;
   }
   return result;
}

int update_Name(Movie_Name* head, char **infos)
{
   int result = 0;
   while (head != NULL)
   {
       if(strcmp(head->name,infos[2]) == 0)
       {
           strcpy(head->genre, infos[1]);
           head->score = atof(infos[3]);
           result = 1;
           // printf("Updated Name Struct\n");
           break;
       }
       head = head->next;
   }
   return result;
}

void detect_genres(Movie_Name *head_movie, Genre **head_genre)
{
    while (head_movie != NULL)
    {
        // if this genre is already in list
        // continue
        if (search_genre(*head_genre, head_movie->genre) == 1) 
        {
            head_movie = head_movie->next;
            continue;
        }

        Genre *newGenre = (Genre *) malloc(sizeof(Genre));
        newGenre->name = (char *) malloc(sizeof(char) * 100);
        newGenre->freq = 1;
        strcpy(newGenre->name, head_movie->genre);
        newGenre->next = NULL;

        if (*head_genre == NULL)
        {
            *head_genre = newGenre;
        }
        else
        {
            Genre *temp = *head_genre;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newGenre;       
        }
            
        head_movie = head_movie->next;
    }
    
}

int search_movie_budget(Movie_Budget *head, char *name, int display)
{
    int flag = 0;
    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            flag = 1;
            if (display == 1)
               printf("%d\t%d\t",head->budget, head->year);
            break;
        }
        
        head = head->next;
    }
    return flag;
}

int search_movie_name(Movie_Name *head, char *name, int display)
{
    int flag = 0;

    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            flag = 1;
            if (display == 1)   
                printf("%s\t%s\t%lf\n", head->name, head->genre, head->score);
            break;
        }
        head = head->next;
    }
    return flag;
}

int search_genre(Genre *head_genre, char *genre)
{
    int flag = 0;
    while (head_genre != NULL)
    {
        if (strcmp(head_genre->name, genre) == 0)
        {
            flag = 1;
            head_genre->freq++;
            break;
        }
        head_genre = head_genre->next;
    }
    return flag;
}

void swap_budget(Movie_Budget *first, Movie_Budget *second)
{
    Movie_Budget *temp = (Movie_Budget*) malloc(sizeof(Movie_Budget));
    temp->budget = first -> budget;
    temp->year = first -> year;
    temp->name = (char*) malloc(sizeof(char) * 100);
    strcpy(temp->name, first->name);

    first->budget = second->budget;
    first->year = second->year;
    strcpy(first->name, second->name);

    second->budget = temp->budget;
    second->year = temp->year;
    strcpy(second->name, temp->name);

    free(temp);
}

void swap_name(Movie_Name *first, Movie_Name *second)
{
    Movie_Name *temp = (Movie_Name*) malloc(sizeof(Movie_Name));
    temp->score = first -> score;
    temp->genre = (char*) malloc(sizeof(char) * 100);
    strcpy(temp->genre, first->genre);
    temp->name = (char*) malloc(sizeof(char) * 100);
    strcpy(temp->name, first->name);

    first->score = second->score;
    strcpy(first->genre, second->genre);
    strcpy(first->name, second->name);

    second->score = temp->score;
    strcpy(second->genre, temp->genre);
    strcpy(second->name, temp->name);

    free(temp);
}


// *******************************************
// actual homework part
void menu(Movie_Budget *head_budget, Movie_Name *head_name, Genre *head_genre)
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
            sorted_list(head_budget, head_name);
            break;

        case 2:
            print_genres(head_genre, 0);
            break;

        case 3:
            list_through_year(head_budget, head_name);
            break;

        case 4:
            list_through_score(head_budget, head_name);
            break;

        case 5:
            all_info_movie(head_budget, head_name);
            break;

        case 6:
            average_score(head_name);
            break;

        case 7:
            print_genres(head_genre, 1);
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

void sorted_list(Movie_Budget *head_budget, Movie_Name *head_name)
{
    while(1)
    {
        int choice = 0;
        printf("1-Budget\n2-Genre\n3-Name\n4-Score\n5-Year\n");
        printf("Enter choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            sorted_list_budget(head_budget, head_name);
            return;
        case 2:
            sorted_list_genre(head_budget, head_name);
            return;
        case 3:
            sorted_list_name(head_budget, head_name);
            return;
        case 4:
            sorted_list_score(head_budget, head_name);
            return;
        case 5:
            sorted_list_year(head_budget, head_name);
            return;
        
        default:   
            printf("Invalid input. Try Again\n");
            break;
        }
    }
}

void sorted_list_budget(Movie_Budget *head_budget, Movie_Name *head_name)
{
    for (Movie_Budget* i = head_budget; i != NULL; i = i->next)
    {
        for (Movie_Budget* j = i->next; j != NULL; j = j->next)
        {
            if (i->budget < j->budget)
            {
                swap_budget(i, j);
            }
        }
    }

    sort_list_helper(head_budget, head_name, 1);
}

void sorted_list_year(Movie_Budget *head_budget, Movie_Name *head_name)
{
    for (Movie_Budget* i = head_budget; i != NULL; i = i->next)
    {
        for (Movie_Budget* j = i->next; j != NULL; j = j->next)
        {
            if (i->year < j->year)
            {
                swap_budget(i, j);
            }
        }
    }

    sort_list_helper(head_budget, head_name, 1);
}

void sorted_list_name(Movie_Budget *head_budget, Movie_Name *head_name)
{
    for (Movie_Budget* i = head_budget; i != NULL; i = i->next)
    {
        for (Movie_Budget* j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->name, j->name) > 0)
            {
                swap_budget(i, j);
            }
        }
    }

    sort_list_helper(head_budget, head_name, 1);
}

void sorted_list_genre(Movie_Budget *head_budget, Movie_Name *head_name)
{
    for (Movie_Name* i = head_name; i != NULL; i = i->next)
    {
        for (Movie_Name* j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->genre, j->genre) > 0)
            {
                swap_name(i, j);
            }
        }
    }

    sort_list_helper(head_budget, head_name, 2);
}

void sorted_list_score(Movie_Budget *head_budget, Movie_Name *head_name)
{
    for (Movie_Name* i = head_name; i != NULL; i = i->next)
    {
        for (Movie_Name* j = i->next; j != NULL; j = j->next)
        {
            if (i->score < j->score)
            {
                swap_name(i, j);
            }
        }
    }

    sort_list_helper(head_budget, head_name, 2);
}

void sort_list_helper(Movie_Budget *head_budget, Movie_Name *head_name, int type)
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
        print_movie_info(head_budget, head_name, type, input, input+1);
    }
    else if (choice == 2)
    {
        int input1, input2;
        printf("Enter start value:");
        scanf(" %d", &input1);
        printf("Enter end value:");
        scanf(" %d", &input2);

        print_movie_info(head_budget, head_name, type, input1, input2);    
    }
    else
        printf("Invalid value\n");
}

void print_movie_info(Movie_Budget *head_budget, Movie_Name *head_name, int type,  int start_index, int end_index)
{

    if (type == 1)
        for (int i = 0; i < start_index; i++)
            head_budget =  head_budget->next;

    if (type == 2)
        for (int i = 0; i < start_index; i++)
            head_name = head_name->next;

    int if_invalid = 1;

    for (int i = start_index; i < end_index; i++)
    {
        if_invalid = 0;

        if (type == 1)
        {
            search_movie_budget(head_budget, head_budget->name, 1);
            search_movie_name(head_name, head_budget->name, 1);
            if (head_budget->next != NULL) head_budget = head_budget->next;
            else return;
        }
        if (type == 2)
        {
            search_movie_budget(head_budget, head_name->name, 1);
            search_movie_name(head_name, head_name->name, 1);
            if (head_name->next != NULL) head_name = head_name->next;
            else return;
        }         
    }

    // if there is no movie with this index range
    if (if_invalid)
    {
        printf("Invalid\n");
    }
}

void list_through_year(Movie_Budget *head_budget, Movie_Name *head_name)
{
    for (Movie_Budget* i = head_budget; i != NULL; i = i->next)
    {
        for (Movie_Budget* j = i->next; j != NULL; j = j->next)
        {
            if (i->year < j->year)
            {
                swap_budget(i, j);
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
        while(head_budget != NULL)
        {
            if (head_budget->year < year)
            {
                search_movie_budget(head_budget, head_budget->name, 1);
                search_movie_name(head_name, head_budget->name, 1);
            }
            head_budget = head_budget->next;
        }
    }
    if (choice == 1)
    {
        while(head_budget != NULL)
        {
            if (head_budget->year > year)
            {
                search_movie_budget(head_budget, head_budget->name, 1);
                search_movie_name(head_name, head_budget->name, 1);
            }
            head_budget = head_budget->next;
        }
    }

}

void list_through_score(Movie_Budget *head_budget, Movie_Name *head_name)
{
    for (Movie_Name* i = head_name; i != NULL; i = i->next)
    {
        for (Movie_Name* j = i->next; j != NULL; j = j->next)
        {
            if (i->score < j->score)
            {
                swap_name(i, j);
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
        while (head_name != NULL)
        {
            if (head_name->score < score)
            {
                search_movie_budget(head_budget, head_name->name, 1);
                search_movie_name(head_name, head_name->name, 1);
            }
            head_name = head_name->next;      
        }    
    }
    if (choice == 1)
    {
        while (head_name != NULL)
        {
            if (head_name->score > score)
            {
                search_movie_budget(head_budget, head_name->name, 1);
                search_movie_name(head_name, head_name->name, 1);
            }
            head_name = head_name->next;      
        }    
    }

}

void all_info_movie(Movie_Budget *head_budget, Movie_Name *head_name)
{
    char *movieName = calloc(100, sizeof(char));
    printf("Enter a movie name:");
    scanf(" %[^\n]", movieName);
    int val = search_movie_budget(head_budget, movieName, 0);

    if (val != 1)
        printf("Invalid movie name");
    else
    {
        search_movie_budget(head_budget, movieName, 1);
        search_movie_name(head_name, movieName, 1);
    }
}

void average_score(Movie_Name *head_name)
{
    double sum = 0;
    int movie_count = 0;
    for (Movie_Name *i = head_name; i != NULL; i = i->next)
    {
        movie_count++;
        sum += i->score;
    }
    
    double average = sum / (double)movie_count;
    printf("Average imdb score of %d movie is %lf\n",movie_count, average);
}
