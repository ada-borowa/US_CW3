#ifndef _SCHEDULER_C_
#define _SCHEDULER_C_

#include <avr/io.h>
#include "scheduler.h"
#include <avr/interrupt.h>
#include <inttypes.h>


void init_scheduler(){
	/*tworze pusta tablice zadan*/
	for(uint8_t i=0;i<MAX_NUMBERS_OF_TASKS; i++){
		TASKS_TAB[i].period = 0;
		TASKS_TAB[i].curr = 0;
		TASKS_TAB[i].func_ptr = NULL;
		TASKS_TAB[i].params = NULL;
		TASKS_TAB[i].status = 0;
	}
}

void schedule(){
	
	for(uint8_t i = 0; i<MAX_NUMBERS_OF_TASKS; i++){
		/*zwiekszam kazdemu zadaniu licznik curr i sprawdzam czy jest on rowny czestosci wykonywania zadania, jesli tak 
		i zadanie nie czeka juz na wykonanie to zmieniam jego status na 1, czyli oczekujacy na wykonanie*/
		TASKS_TAB[i].curr++;
		if(TASKS_TAB[i].curr == TASKS_TAB[i].period && TASKS_TAB[i].status != 1){
			TASKS_TAB[i].status = 1;
		}
	}
	

}

void execute(){
	while(1){
		for(uint8_t i=0; i<MAX_NUMBERS_OF_TASKS; i++){
			/*sprawdzam po kolei czy kolejne zadania czekaja na wykonanie,
 jesli jakies czeka, wykonuje je i wracam na poczatek tablicy*/
			if(TASKS_TAB[i].status == 1 ){
				(TASKS_TAB[i].func_ptr)();
				TASKS_TAB[i].status = 0;
				TASKS_TAB[i].curr = 0;
				i = MAX_NUMBERS_OF_TASKS;
			}
			
		}
	}
}

void addTask(int priority, uint8_t period, task_f func_ptr, void * params){
	TASKS_TAB[priority].period = period;
	TASKS_TAB[priority].curr = 0;
	TASKS_TAB[priority].func_ptr = func_ptr;
	TASKS_TAB[priority].params = params;
	TASKS_TAB[priority].status = 0;
}

#endif