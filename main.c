#include <stdio.h>
#include <stdlib.h>

//If running on Windows, keep the following lines after preprocessing
#ifdef _WIN32
#include <string.h>

static char buffer[2048];
//Displays a prompt, reads string input and stores into the variable buffer
//Similar to Python's input(prompt) function
char* readline(char* prompt){
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    return buffer;
}
#endif

//Version number, nothing silly
char* LISPY_VERSION = "0.0.0.1";

//Keeping track of programme's state, and displaying some info accordingly.
typedef enum{
    START,
    STOP
} progState;

void printInfo(progState state){
    printf("Lispy version %s\n\n", LISPY_VERSION);
    if(state==STOP)
        puts("Sayounara, senpai...");
    else puts("Welcome to Lispy.\nType \"exit\" and hit Enter to exit\n");
}


//The main function
int main(int argc, char** argv){
    printInfo(START);
    while(1){
        char* input = readline("lispy> ");

        //If the user has entered the exit command, break the loop
        if (!strcmp(input,"exit\n")) break;
        
        printf("No you're a %s", input);
    }
    printInfo(STOP);
    return 0;
}