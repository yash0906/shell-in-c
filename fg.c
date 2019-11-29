#include "header.h"
void fg(char arr[200])
{
	char **a = calloc(200, sizeof(char*));
    char *ptr = strtok(arr," \t\n\a\r");
    int i=0,cgrp=-1,pgrp=-2;
    while(ptr!=NULL)
    {
    	a[i++]=ptr;
    	ptr = strtok(NULL, " \t\n\a\r");
    }
	int pid = fork();
	    if(pid<0)
	    {
	    	printf("Error while creating a child process\n");
	    }
	   	else if(pid)
	   	{
	   		curr_running = pid;
	   		wait(NULL);
	   	}
    	else
    	{
	   		sleep(1);
	   		if(execvp(a[0], a)<0)
	   			printf("Error: command not found!\n");
           	exit(1);
	   	}
	free(a);
}