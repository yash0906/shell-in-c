#include "header.h"
void bg(char arr[200])
{
        
            char **a = calloc(200, sizeof(char*));
        	char *ptr = strtok(arr," \t\n\a\r");
	    	int i=0;
            bgn++;
	    	while(ptr!=NULL)
	    	{
	    		a[i++]=ptr;
	    		ptr = strtok(NULL, " \t\n\a\r");
	    	}
            if(a[1]!=NULL && a[1][0]=='&')
                a[1]=NULL;
            if(a[2]!=NULL && a[2][0]=='&')
                a[2]=NULL;
            a[4]=NULL;
            i=1;              
            strcpy(bg_jobs[bgn].p_name,a[0]);
            while(a[i]!=NULL)
            {
                strcat(bg_jobs[bgn].p_name, " ");
                strcat(bg_jobs[bgn].p_name,a[i]);
                i++;
            }
            strcpy(bg_jobs[bgn].status,"Running");
	        int pid = fork();
            if(pid<0)
            {
            	printf("Error while creating a child process\n");
            }
            else if(pid)
            {
            	bg_jobs[bgn].pid = pid+1;
                return;
            }
            else
            {
            	
                int pid2 = fork();
                //printf("%d\n",pid2); 
            	if(pid2<0)
            	{
            		printf("Error while creating a child process\n");
            	}
            	else if(pid2==0)
            	{
            		if(strcmp("cronjob",a[0])==0)
                        {
                            int sleeptime = str_to_int(a[4]);
                            int totaltime=str_to_int(a[6]);
                            int total=0;
                            while(total<totaltime)
                            {
                                sleep(sleeptime);
                                mainloop(a[2]);
                                total+=sleeptime;
                            }
                        }
                        else
                        {      
                  		    execvp(a[0],a);
                  		    exit(1);
                        }
            	}
            	else
            	{
            		int status,ret_pid;
            		ret_pid = waitpid(pid2,&status,0);
                    for(int i=1;i<=bgn;i++)
                    {
                        if(bg_jobs[i].pid==ret_pid)
                            bg_jobs[i].pid=-1;
                        //printf("ret = %d     pid2 = %d\n",ret_pid,pid2);
                    }
            		if(WIFEXITED(status)==1)
            		{
            			printf("%s with pid %d exited normally\n",a[0],ret_pid);
            		}
            		else
            		{
            			printf("%s with pid %d exited abnormally\n",a[0],ret_pid);
            		}
            	}

            }
            free(a);
}