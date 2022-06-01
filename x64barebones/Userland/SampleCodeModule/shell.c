#include <shell.h>

typedef void (*functionPointer)(void);

typedef struct{
    char * name;
    functionPointer func;
}FunctionType;

static FunctionType programs[] = {{"fibonacci", &fibonacci},{"help",&help},{"primos", &primos},{"primoFibo", &primoFibo}, {0,0}}; //CAMBIAR


int run(char * buffer){
    for( int i = 0 ; programs[i].name ; i++){
        if( strcmp(buffer, programs[i].name) == 0){
            programs[i].func();
            return 0;
        }
    }
    if (*buffer!=0)
    {
        print(buffer, RED, BLACK,0);
        print(" is not a valid command \n", WHITE, BLACK,0);
    }
    return 1;
}


void shell(){
    while(1){
        print("~$ ",GREEN, BLACK,0);
		char readBuffer[BUFFER_LENGTH]={0};
		scanf(KEYBOARD_FD, readBuffer, BUFFER_LENGTH);
		run(readBuffer);
    }
}
