#include "header.h"
void set(char arr[200])
{
	char **comm = calloc(200, sizeof(char*));
	char *ptr = strtok(arr, " ");
	int i=0;
	while(ptr!=NULL)
	{
        comm[i++]=ptr;
        ptr = strtok(NULL, " ");
	}
	if(comm[2]==NULL)
	{
		i++;
		comm[2]=" ";
	}
	i--;
	if(i==0 || i>2)
	{
		printf("Please the number of arguements\n");
	}
	else
	{
        if(setenv(comm[1],comm[2],1)!=0)
        	perror("ERROR");
	}
	free(comm);
}
void unset(char arr[200])
{
	char **comm = calloc(200, sizeof(char*));
	char *ptr = strtok(arr, " ");
	int i=0;
    while(ptr!=NULL)
    {
    	comm[i++] = ptr;
    	ptr=  strtok(NULL, " ");
    }
    if(i==1)
    	printf("Please check number of arguements\n");
    else
    	if(unsetenv(comm[1])!=0)
    		perror("ERROR");
    free(comm);
}
void get(char arr[200])
{
	char **comm = calloc(200, sizeof(char*));
	char *ptr = strtok(arr, " ");
	int i=0;
	while(ptr!=NULL)
	{
		comm[i++] = ptr;
		ptr = strtok(NULL, " ");
	}
	if(i==1)
	{
		printf("Please check number of arguements\n");
	}
	else
	{
		if(getenv(comm[1])==0)
			perror("ERROR");
		else
			printf("%s\n",getenv(comm[1]));
	}
	free(comm);
}