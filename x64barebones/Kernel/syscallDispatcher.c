#include <syscallDispatcher.h>

#define KEYBOARD_FD 1
#define SCREEN_FD 0

extern uint8_t hasRegDump;
extern uint64_t regdump[17];

void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8){
	switch(r8){
		case 1:
			int_80(rdi,rsi,rdx,rcx);
            break;
        case 2:
            int_81(rdi);
            break;
        case 3:
            int_82();
            break;
        case 4:
            int_83(rdi);
            break;
        case 6:
            int_85(rdi);
            break;
        case 7:
            int_86();
            break;

	}
}

void schedulerDispatcher(char * name, void * func, uint64_t parametro,uint64_t flags){
    add_task(name, func, parametro, flags);
}

//a lo mejor en el futuro haya que agregar cases o mas parametros para el split screen
void int_80(char * buffer, uint8_t fontColor, uint8_t backColor, int length) {
     int param;

    param=getActivePId();
    if(tasksRunning()==1){
        param=0;
    }
    for (int i = 0; i < length; i++) {
        restoreDefault();
        if (buffer[i] == '\n') {
            switch(param){
                case 0:
                    ncNewline();
                    break;
                case 1:
                    newLineLeft();
                    break;
                case 2:
                    newLineRight();
                    break;
            }
        } else if (buffer[i] == '\b') {
            backspace();
        } else if (param==0)
            ncPrintCharWithAtt(buffer[i], fontColor);
        else if (param == 1)
            printCharLeft(buffer[i],fontColor);
        else if (param == 2)
            printCharRight(buffer[i],fontColor);
    }
}


void int_81(char * buffer){
    buffer[0]=getKbBuffer();
}

void int_82(){
    ncClear();
}

void int_83(){
    schedulerExit(1);
}

int int_85(uint64_t * registers){
    for (int i = 0; i < 17; i++){
        if(hasRegDump){
            for(uint8_t i=0; i<17; i++){
                registers[i] = regdump[i];
            }
        }
    }
    return hasRegDump;
}

void int_86(){
    printCurrentTime();
}
