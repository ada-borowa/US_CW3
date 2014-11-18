#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_


//maksymalna liczba zadañ
#define MAX_NUMBERS_OF_TASKS 8
#define NULL ((void*)0)

typedef void (*task_f)(void);

/*definiuje zadanie, curr jest licznikiem */
typedef struct tasks{
	uint16_t period;
	uint16_t curr;
	task_f func_ptr;
	void * params;
	uint8_t status;
	
} task;



task TASKS_TAB[MAX_NUMBERS_OF_TASKS];


void schedule();
void execute();
void addTask(int priority, uint8_t period, task_f func_ptr, void * params);
void init_scheduler();

#endif