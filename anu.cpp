#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

#define NEW 0
#define READY 1
#define WAITING 2
#define RUNNING 3
#define EXIT 4

int ongoingtime=0,time_till_last_ct=0,EXIT_STATE_ALL=0,CT_ALLOWED=1,n,i,j;
struct Process_structure 
{
	int pid;
	int state;
	int timeleft_to_exec;
	int at;
	int wt,tat,ct,exect;
	struct Process_structure *prev;
	struct Process_structure *next;
} *proc_arr;
int chpp;
struct Queue
{
	struct Process_structure *front ,*rear;
}*RQueue;

void enqueue(struct Process_structure *proc)
{
	if(RQueue->front==NULL)
	{
		RQueue->front=proc;
		RQueue->rear=proc;
		proc->next=NULL;
	}
        
	else
	{
		if(proc->timeleft_to_exec<RQueue->front->timeleft_to_exec)
		{
			proc->next=RQueue->front;
			RQueue->front->prev=proc;
			RQueue->front=proc;
		}
               else if(proc->timeleft_to_exec==RQueue->front->timeleft_to_exec)
		{
			proc->next=RQueue->front->next;
			proc->prev=RQueue->front;
			RQueue->front->next=proc;
