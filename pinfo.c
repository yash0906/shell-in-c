#include "header.h"
void pinfo(char arr[200])
{
    char *ptr = strtok(arr ," ");
    ptr = strtok(NULL, " ");
    // if(ptr!=NULL)
	   // printf("%s\n",ptr);
    char *pid_path = calloc(200, sizeof(char));
    strcat(pid_path, "/proc/");
    //strcat(pid_path ,"/status");
    char *pid = calloc(100, sizeof(char));
    if(ptr==NULL)
    {
	    char *buf = calloc(100, sizeof(char));
	    sprintf(buf,"%d",getpid());
	    strcat(pid_path,buf);
	    strcpy(pid, buf);
	    free(buf);
    }
    else
    {
	    strcat(pid_path,ptr);
	    strcpy(pid, ptr);
    }
    strcat(pid_path,"/status");
    FILE * status;
    char *line = calloc(200, sizeof(char));
    size_t len = 0;
    ssize_t read;
    //printf("%s\n",pid_path);
    status = fopen(pid_path, "r");
    if(status== NULL)
    {
	   printf("NO SUCH PROCESS\n");
	   return ;
    }
    else
    {
	   printf("PID -- %s\n",pid);
	   //free(pid);
	   while((read = getline(&line, &len, status))!=-1)
	   {
			ptr = strtok(line, " \t\n\a\r");
			//ptr = strtok(NULL, " \t\n\a\r");
			//printf("%s %ld\n",ptr,strlen(ptr));
		   if(strcmp(ptr,"State:")==0)
			  {
                    ptr = strtok(NULL, " \t\n\a\r");
			  	printf("Process Status -- %s\n",ptr);
			  }
		   else if(strcmp(ptr,"VmSize:")==0)
			  {
                    ptr = strtok(NULL, " \t\n\a\r");
			  	printf("Memory -- %s\n",ptr);
			  }
	   }
	    fclose(status);
	    char *exe_path = calloc(200 ,sizeof(char));
        strcat(exe_path,"/proc/"); 
     	strcat(exe_path,pid);	   	
     	strcat(exe_path, "/exe");
        char *buf = calloc(200, sizeof(char));
        read = readlink(exe_path, buf, 199);
        if(!read)
        {
        	perror("Executable path -- not found");
        }
        else
        {
        	printf("%s\n",buf);
		    if(strncmp(local_home,buf,strlen(local_home))==0)
			{
		        char *buff = (char*)calloc(200,sizeof(char));
		        buff[0]='~';
		        int k=1;
		        for(int i=strlen(local_home);i<strlen(buf);i++)
		        {
		        	buff[k]=buf[i];
		        	k++;
		        }

		        printf("Executable path -- %s\n",buff);
		        free(buff);
			}
			else
			{
				printf("Executable path -- %s\n",buf);
			}

        }
    }


}