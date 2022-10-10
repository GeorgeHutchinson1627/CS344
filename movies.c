#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//Defines Movie structure
struct Movie {
    char* languages;
    float rating;
    int year;
    char* title;
    struct Movie* next_movie;
}movie;

//Checks if a particular integer is in an integer array
int valueinarray(int val, int arr[])
{
    int i;
    for(i = 0; i < 103; i++)
    {
        if(arr[i] == val)
            return 1;
    }
    return 0;
}


void main(int argc, char *argv[]){
    
    //creates basis for linked list, aswell as initilzed file variables
    struct Movie* head= NULL;
    struct Movie* tail = NULL;
    head= (struct Movie*)malloc(sizeof(struct Movie));
    tail=head;
    FILE *fp;
    char *filename;
    filename= argv[1];
    
    //Opens file and parses file data. Also creates linked list
    printf("Recognized filename %s\n", filename);
    fp=fopen(filename, "r");

    if (!fp)
        printf("Can't open file\n");
 
    else {
        char buffer[1024];
        int row = 0;
        int column = 0;
        while (fgets(buffer,1024, fp)) {
            column = 0;
            row++;
            if (row == 1){
                continue;
            }
            //creates new movie for each new line and adds it to linked list
            tail->next_movie=(struct Movie*)malloc(sizeof(struct Movie));
            tail=tail->next_movie;
            
            //grabs token of first column and sets title
            char* value = strtok(buffer, ",");
            while (value) {
                if (column == 0) {
                    char * real_title=strdup(value);
                    tail->title=real_title;


                }
                //grabs token of second column and converts 
                if (column == 1) {
                    char * real_year=strdup(value);
                    int real_int_year;
                    real_int_year= atoi(real_year);
                    tail->year=real_int_year;
                }
                //grabs third column
                if (column == 2) {
                    char * real_lang=strdup(value);
                    //printf("Languages: %s",value);
                    tail->languages= real_lang;
                }
                //grabs fourth column 
                if (column == 3){
                    char * real_rating=strdup(value);
                    float real_float_rating;
                    real_float_rating= atof(real_rating);
                    tail->rating=real_float_rating;
                }

                value = strtok(NULL, ",");
                column++;
            }
           
        }
        //prints that data is parsed properly
        printf("Successful processed data for file %s for %i movies\n",filename,row-1);
        fclose(fp);
    
    }
    bool still_reviewing= true;
    //main loop
        while (still_reviewing){
            int initial_choice;
            //grabs user choice during each loop of the text portion of the program. Error checks so program wont crash
            while(1){
                printf("\n1. Show movies released in the specified year\n2. Show highest rated movie for each year\n3. Show the title and year of release of all movies in a specific language\n4. Exit from the program\n");
                printf("\nEnter a choice from 1 to 4: ");
                scanf("%d", &initial_choice);
                if (initial_choice==1||initial_choice==2||initial_choice==3||initial_choice==4){
                    
                    break;
               }
            printf("Invalid choice. Please enter 1-4. \n");
            fflush(stdin);
           }
            //Handles user choice #1
            if (initial_choice==1){
                int year_choice;
                while(1){
                printf("For which years do you want to see movies released?: ");
                scanf("%d", &year_choice);
                //error checks for valid years
                if (year_choice>=1900 && year_choice<=2021){
                    break;
                }
                    printf("Invalid choice. Please enter a valid year. \n");
                    fflush(stdin);
                }
                struct Movie* testp=head;
                bool found_movie=false;
                //iterates through linked list, checks for entered year and then displays movies
                while (testp!=tail){
                        if (testp->next_movie->year==year_choice){
                            printf("%s\n",(testp->next_movie->title));
                            found_movie=true;
                        }
                    testp=testp->next_movie;
                    }
                    if (found_movie==false){
                        printf("No data about movies released in the year %d.\n", year_choice);
                    }
                }
            //Handles user choice #2
            if (initial_choice==2){
                int year_choice2;
                struct Movie* testp=head;
                struct Movie* testp3;
                bool found_movie=false;
                float high_score=0;
                int possible_years[103]={0};
                int count=0;
                while (testp!=tail){
                    //iterates through linked list and adds each year to array uniquely
                    if (valueinarray(testp->next_movie->year, possible_years)==0){
                        possible_years[count]=testp->next_movie->year;
                        count++;
                    }
                    testp=testp->next_movie;
                }
                testp=head;
                //iterates through year array 103 picked as there are only so many years allowed
                for (int i=0; i<103;i++){
                    testp=head;
                    high_score=0;
                    //breaks if year is 0 as that signifies the end of uniquely added years
                    if (possible_years[i]==0){
                        break;
                    }
                    year_choice2=possible_years[i];
                    while (testp!=tail){
                        if (testp->next_movie->year==year_choice2){
                            if (testp->next_movie->rating>high_score){
                                high_score=testp->next_movie->rating;
                                testp3=testp->next_movie;
                            }
                        
                        }
                        testp=testp->next_movie;
                    }
                    printf("Year: %d Rating: %.1f Title: %s\n",testp3->year,testp3->rating,testp3->title);
                    testp=head;
                }

                }
            //Handles choice number #3
            if (initial_choice==3){
                char user_lang[20];
                bool lang_found=false;
                struct Movie* testp=head;
                printf("For which language do you want to see movies released?: ");
                scanf("%s", &user_lang);
                while (testp!=tail){
                    //Checks if substring of entered language is the the language string
                    if (strstr(testp->next_movie->languages,user_lang)!=NULL){
                        printf("Title: %s\n", testp->next_movie->title);
                        lang_found=true;
                    }
                    testp=testp->next_movie;
                }
                if (lang_found==false){
                    printf("No movies found in that language\n");
                }  
            }
            //Quits program
            if (initial_choice==4){
                still_reviewing=false;
            }
        }  
}