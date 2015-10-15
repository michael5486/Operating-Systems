#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80 //The maximum length command
char *args[MAX_LINE/2 + 1]; //command line arguments
char *history[10]; //array to store the history
int max = 0;


void printHistory() { //prints the history array
    int i = 9;
    printf("History: \n");
    for (i; i >= 0; i--) {
        if (history[i] != NULL) {
            printf("   %d %s\n", i, history[i]); //This should print out the string
        }
    }
}

void addToHistory(char *string) {
    
    int i = 9;
    char *str1 = string;
    char str2[MAX_LINE];
    strcpy(str2, "test");
    
    if (max < 10) {
     //   printf("adding %s to history[%d]\n", str2, max);
        history[max] = str2;
        max++;
    }
    else { //the array is full, shift every string up once, and add new string to history[0]
      //  printf("full array\n");
        for (i; i >= 0; i--) {
            history[i + 1] = history[i];
        }
        history[0] = string;
    }
}

void childProcess(int i) {
    
        int pid = fork();
        int status;
        if (pid == 0) {
            //printf("Child process.\n");
            if (execvp(args[0], args) < 0) {
                printf("Command not found\n"); 
            }
        }
        else if (pid > 0) {
            //printf("Parent process.\n");
            while (wait(&status) != pid);       //parent process waits for child

        }
        else {
            printf("Fork failed.\n"); //forked failed
            exit(1);
        }
}

int main(void) {
    
    int should_run = 1; //flag to determine when to exit program
    int i;


    while (should_run) {

        i=0;
        char str[MAX_LINE];
        char *point;
        int hasAmpersand = 0;
        
        fflush(stdin);
        printf("osh>");
        fgets(str, MAX_LINE, stdin);
        if(str[strlen(str)-1] == '\n') { //removes newline character from the end of the string
            str[strlen(str)-1] = '\0';
            //printf("removed newline character\n");
        }
        addToHistory(str); //adds each command to the history
        fflush(stdout);
            
        point = strtok(str," ");
        
        if (str[0] == '!') { //if statements to call the correct statement in the history array
          //  printf("go to history");
            if (str[1] == '!'){
                printf("call most recent in history\n");
                point = strtok(history[max], " ");
            }
            else if (str[1] == '1') {
                if (str[2] == '0') {
                    printf("call history[9]\n");
                    point = strtok(history[9], " ");

                }
                else {
                    printf("call history[0]\n");     
                    point = strtok(history[0], " ");

                }
            }
            else {
                printf("call history[str[0] - 1]\n");
                point = strtok(history[str[0] - 1], " ");

            }
        }
        
        while (point != NULL) { //separates the line into separate arguments
            args[i] = point;
            if (strcmp(args[i], "&") == 0) {
                hasAmpersand = 1;
              //  printf("hasAnd now true\n");
                i--; //removes ampersand from command
                point = strtok(NULL, " "); //skips space in front of &

            }
            i++;
            point = strtok(NULL, " ");
        }

        if (strcmp(args[0], "exit") == 0) { //stops the program from looping
            printf("Attempting to exit\n");
            should_run = 0;
            break;
        }
        if (strcmp(args[0], "history") == 0) { //prints the histort
            printHistory();
        }
            
        childProcess(i);
        
        if (hasAmpersand) { //tells parent process to wait for child to finish executing
           printf("Waiting for child\n");
           wait(NULL); 
        }

    }
    
    return 0;
}