#include"header.h"
void jobs()
{
	//printf("%d jobs\n",bgn);
	for(int i=1;i<=bgn;i++)
	{
		if(bg_jobs[i].pid!=-1)
		{
			char *pid_path = calloc(200, sizeof(char));
			strcat(pid_path, "/proc/");
            char *buf = calloc(100, sizeof(char));
            char *ptr = calloc(100, sizeof(char));
	        sprintf(buf,"%d",bg_jobs[i].pid);
	    	strcat(pid_path,buf);
            strcat(pid_path,"/status");
    		FILE * status;
    		char *line = calloc(200, sizeof(char));
    		size_t len = 0;
    		ssize_t read;
			status = fopen(pid_path, "r");
		    if(status!= NULL)
		    {
			   while((read = getline(&line, &len, status))!=-1)
			   {
					ptr = strtok(line, " \t\n\a\r");
				   if(strcmp(ptr,"State:")==0)
					  {
		                    ptr = strtok(NULL, " \t\n\a\r");
					  		//printf("%s\n",ptr);
					  		break;
					  }
			   }
			   fclose(status);
			   int f=0;
			   if(strcmp(ptr,"R")==0 || strcmp(ptr,"S")==0)
			        strcpy(bg_jobs[i].status,"Running");
			   else if(strcmp(ptr,"T")==0)
                    strcpy(bg_jobs[i].status,"Stopped");
               else
                    strcpy(bg_jobs[i].status,"Terminated");

			   printf("[%d] %s %s [%d]\n",i,bg_jobs[i].status, bg_jobs[i].p_name, bg_jobs[i].pid);

		    }

		}
	}
}
void bgup(char arr[200])
{
	char *ptr = calloc(100,sizeof(char));
	strtok(arr," \t\n\a\r");
	ptr = strtok(NULL, " \t\n\a\r");
	int k = str_to_int(ptr);
	if(bg_jobs[k].pid!=-1)
	{
		kill(bg_jobs[k].pid,SIGCONT);
	}

}
void fgup(char arr[200])
{
	char *ptr = calloc(100, sizeof(char));
	strtok(arr," \t\n\a\r");
	ptr = strtok(NULL, " \t\n\a\r");
	int k=str_to_int(ptr);
	int status;
	if(bg_jobs[k].pid!=-1)
	{
		setpgid(bg_jobs[k].pid, bg_jobs[k].pid);
		kill(bg_jobs[k].pid, SIGCONT);
		curr_running = bg_jobs[k].pid; 
		int o=waitpid(bg_jobs[k].pid-1,&status,WUNTRACED);
		//perror("ERROR");
		//printf("%d\n",o);
	}
}