#include "header.h"
void pipeline(char **cmd)
{

	pid_t pid;
	int fdd = 0;		
    int j=0;
	while (cmd[j] != NULL)
	{
		char **a = calloc(200, sizeof(char*));
		char *arr = calloc(200,sizeof(char));
		strcpy(arr,cmd[j]);
    	char *ptr = strtok(arr," \t\n\a\r><");
    	int i=0;
    	int redir=0,append=0,file_des=1;
    	while(ptr!=NULL)
    	{
    		a[i++]=ptr;
    		ptr = strtok(NULL, " \t\n\a\r><");
    	}
    	for(int h=0;h<strlen(cmd[j]);h++)
    	{
    		if(cmd[j][h]=='<')
    		{
    			redir=2;                
                file_des = open(a[i-1],O_RDONLY);
                dup2(file_des,0);
                close(file_des);

    		}
    	}
    	if(cmd[j+1]==NULL)
    	{
    		for(int h=0;h<strlen(cmd[j]);h++)
    		{
    			if(cmd[j][h]=='>')
    			{
    				redir=1;
    				if(cmd[j][h+1]=='>')
    					{
    						append=1;
    					}
    				strcpy(cmd[j],a[0]);
    				for(int w=1;w<i-1;w++)
    				{
    					strcat(cmd[j]," ");
    					strcat(cmd[j],a[w]);
    				}
    			}
    		}
    	}
    	if(redir==1)
    	{
    		if(append==1)
    		{
                file_des = open(a[i-1],O_CREAT|O_RDWR|O_APPEND, 0600);
                if(file_des==-1)
                	perror("file cant be opened");
    		}
    		else
    		{
                file_des = open(a[i-1],O_WRONLY|O_CREAT|O_TRUNC , 0600);
                if(file_des==-1)
                	perror("file cant be opened");
    		}
    	}
		pipe(fd);	
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (cmd[j+1] != NULL) {
				dup2(fd[1], 1);
			}
			if(cmd[j+1]==NULL && redir==1)
			{
				dup2(file_des,1);
				close(file_des);
			}
			close(fd[0]);
			close(fd[1]);
            if(strncmp(cmd[j], "ls", strlen("ls"))==0)
                    {
                    	ls(cmd[j]);
                    	exit(1);
                    }
            else if(strncmp(cmd[j], "cd", strlen("cd"))==0)
           	    	{
           	    		cd(cmd[j]);
           	    		exit(1);
           	    	}
            else if(strncmp(cmd[j], "pwd", strlen("pwd"))==0)
                    {
                    	pwd();
                    	exit(1);
                    }
            else if(strncmp(cmd[j], "echo", strlen("echo"))==0)
                    {
                    	echo(cmd[j]);
                    	exit(1);
                    }
            else if(strncmp(cmd[j], "pinfo", strlen("pinfo"))==0)
                	{
                		pinfo(cmd[j]);
                		exit(1);
                	}
            else if(strncmp(cmd[j], "history", strlen("history"))==0)
                	{
                		history(cmd[j]);
                		exit(1);
                	}
            else if(strncmp(cmd[j], "nightswatch", strlen("nightswatch"))==0)
                	{
                		nightswatch(cmd[j]);
                		exit(1);
                	}
            else if(strncmp(cmd[j], "jobs", strlen("jobs"))==0)
                    {
                        jobs();
                        exit(1);
                    }
            else
            {
				if(redir>0)
					a[i-1]=NULL;
				execvp(a[0], a);
				exit(1);
			}
		}
		else {
			wait(NULL); 		
			close(fd[1]);
			fdd = fd[0];
			j++;
		}
	}
}

void piping(char arr[200])
{ 
    char *dup_arr = strdup(arr);
    char **cmd = calloc(200, sizeof(char*));
    char *pipe_sep = strtok(arr, "|");
    int i=0;
    while(pipe_sep!=NULL)
    {
    	cmd[i++] = pipe_sep;
    	pipe_sep = strtok(NULL, "|");
    }
    cmd[i]=NULL;
    int fd0 = dup(0);
    int fd1 = dup(1);
    pipeline(cmd);
    dup2(fd0,0);
    dup2(fd1,1);
    close(fd0);close(fd1);


}