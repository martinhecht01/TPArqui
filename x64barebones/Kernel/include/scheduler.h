#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <naiveConsole.h>

void add_task(char *name, void * task, uint64_t parametro, uint64_t flags);
int tasksRunning(void);

//recive por parametro flag para saber que caso tiene que ejecutarse
//(matar a un programa activo, ambos, solo izq, solo derecha)
void schedulerExit(int amountOfFuncs);
int getParameter();
int getActivePId();
int shellRunning();
uint64_t * registerManager(uint64_t * registers, uint8_t load);
int getProcesses();
int getSplitScreen();

//a partir de los programas activos, alterna el ActivePID
void next();
void freeze(int func);

#endif
