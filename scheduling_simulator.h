#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ucontext.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>

#include "task.h"
#define STACK_SIZE 16384

enum TASK_STATE {
	TASK_RUNNING,
	TASK_READY,
	TASK_WAITING,
	TASK_TERMINATED
};

typedef struct Task_node{
	ucontext_t uctx_task;
	int pid;
	char* task_name;
	enum TASK_STATE task_state;
	int queue_time;
	int suspend_time;
	char priority;
	char time_quantum;
	struct Task_node *next;
}Task_node;

typedef struct priority_queue_node{
	Task_node *task;
	struct priority_queue_node *next;
}Priority_queue_node;

void hw_suspend(int msec_10);
void hw_wakeup_pid(int pid);
int hw_wakeup_taskname(char *task_name);
int hw_task_create(char *task_name);

void error(char *msg);
void insert_task_q(Task_node* node);
int remove_task_q(int pid);
void insert_priority_q(char priority, Task_node *task_node);
int remove_priority_q(char priority, Task_node *task);
int set_task_priority(int pid, char priority);
int set_task_tquantum(int pid, char tquantum);
void print_tasks();
void print_priority_q();
void shell();
void catcher( int sig );
void simulate();
void reschedule();
void setTimer(int time_usec); //if time_usec==0, disable timer
void updateTaskTime(); //update queue time and suspend time

#endif
