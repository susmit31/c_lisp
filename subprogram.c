#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char expression[100] = "";
    for (int i=1; i<argc; i++) strcat(expression, argv[i]);

    printf("Expression [ %s ] = \n", expression);
    eval(expression);
    return 0;
}

void eval(char* expression){
    char prog[1024] = "";
    char sec[100] = "";
    strcat(prog, "#include <math.h>\n#include <stdio.h>\n");
    sprintf(sec, "int main(){\nprintf (\"d\", %s );\n", expression);
    strcat(prog, sec);
    strcat(prog, "}");

    FILE *fp = fopen("./abc.c","w");
    fputs(prog, fp);
    fclose(fp);
    system("gcc -o abc.exe abc.c");
    system("./abc");
}