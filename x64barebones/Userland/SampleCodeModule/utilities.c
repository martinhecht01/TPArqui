#include <utilities.h>
#include <stdint.h>


void clear(){
    sys_clear();
}

void printDec(int number){
    sys_write_decimal(number);
}

void print(char * string,uint8_t fontColor, uint8_t backColor){
    sys_write(string, fontColor, backColor);
}

char getChar(){
    char c = 0;
    while( c == 0 ){
        sys_read(KEYBOARD_FD, &c);
    }
    return c;
}

// ver si se puede sacar el fd del scanf
void scanf(int fd, char * buffer, int maxlength){
    int size=0;
    char c;
    do {
        if ((c=getChar())!='\n'){
            if (c=='\b' && size>0){
                size--;
            }else if(c!='\b'){
                buffer[size]=c;
                size++;
            }
            put_char(1, c);
        }
    } while (size<maxlength-1 && c != '\n');
    put_char(1,'\n');
    buffer[size] = 0;
}
