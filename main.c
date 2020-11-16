#include "mpc.h"

//If running on Windows, keep the following lines after preprocessing
#ifdef _WIN32

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
    printf("\n\nLispy version %s\n", LISPY_VERSION);
    if(state==STOP)
        puts("Sayounara, senpai...\n\n");
    else puts("Welcome to Lispy.\nType \"exit\" and hit Enter to exit\n");
}


//The main function
int main(int argc, char** argv){
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("opeartor");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");
    mpca_lang(MPCA_LANG_DEFAULT, "\
        number: /-?[0-9]+/ ; \
        operator: '+' | '-' | '*' | '/' ; \
        expr: <number> | '(' <operator> <expr>+ ')' ; \
        lispy: /^/<operator> <expr>+ /$/; \
    ",
    Number, Operator, Expr, Lispy);

    printInfo(START);
    while(1){
        char* input = readline("lispy> ");

        //If the user has entered the exit command, break the loop
        if (!strcmp(input,"exit\n")) break;

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)){
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else{
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
    }
    printInfo(STOP);

    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    return 0;
}