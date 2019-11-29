#include "header.h"
void kjobs(char arr[200])
{
	char **a = calloc(200, sizeof(char*));
    char *ptr = strtok(arr," \t\n\a\r");
    int i=0;
	while(ptr!=NULL)
	{
	    a[i++]=ptr;
	    ptr = strtok(NULL, " \t\n\a\r");
	}
	int x=str_to_int(a[1]);
	int y=str_to_int(a[2]);
	//printf("x = %d y = %d\n",x,y);
	if(bg_jobs[x].pid==-1)
		printf("Process with job number %d do not exist\n",x);
	else
		{
			int p=kill(bg_jobs[x].pid,y);
			if(p==-1)
				perror("ERROR");

		}
}
void overkill()
{
    for(int i=1;i<=bgn;i++)
    {
    	if(bg_jobs[i].pid!=-1)
    	kill(bg_jobs[i].pid,9);
    }
}