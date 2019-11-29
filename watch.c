#include "header.h"
void nightswatch(char arr[200])
{
	char **a = calloc(200, sizeof(char*));
	char *ptr = strtok(arr, " \t\n\a\r");
	int i=0;
	int n=0;
	while(ptr!=NULL)
	{
		a[i] = ptr;
     	ptr = strtok(NULL, " \t\n\a\r");
     	i++;
	}
	if(a[2]!=NULL)
	{
		int k=strlen(a[2]);
		int h=1;
		for(int i=k-1;i>=0;i--)
		{
            n+=(h*(a[2][i]-'0'));
            h*=10;
		}
	}
	if(a[1]==NULL || a[2]==NULL || a[1][0]!='-' || a[1][1]!='n')
	{
		printf("Expected: nightswatch -n time command\n");
	}
	else if(strcmp(a[3],"dirty")!=0 && strcmp(a[3],"interrupt")!=0)
	{
		printf("Try : nightswatch -n time dirty/interrupt\n");
	}
	else if(strcmp(a[3],"dirty")==0)
	{
		char *b = calloc(200,sizeof(char));
		strcpy(b,"/proc/meminfo");
		FILE * status;
    	char *line = calloc(200, sizeof(char));
    	size_t len = 0;
    	ssize_t read;
        status = fopen(b,"r");
        if(status==NULL)
        	printf("Dirty memory can't be found,try something else\n");
        else
        {
        	fclose(status);
        	while(1)
        	{
	        	char c=getchar();
	        	if(c=='q')
	        		break;
	        	status = fopen(b,"r");
	        	while((read=getline(&line ,&len, status))!=-1)
	        	{
	        		ptr = strtok(line ," \t\n\a\r");
	        		if(strcmp(ptr,"Dirty:")==0)
	        		{
	        			ptr = strtok(NULL, " \t\n\a\r");
	        			printf("%s kB\n",ptr);
	        			break;
	        		}
	        	}
	        	fclose(status);
	        	sleep(n);
            }
        }
    
	}
	else if(strcmp(a[3],"interrupt")==0)
	{
        char *b = calloc(200,sizeof(char));
		strcpy(b,"/proc/interrupts");
		FILE * status;
    	char *line = calloc(200, sizeof(char));
    	size_t len = 0;
    	ssize_t read;
        status = fopen(b,"r");
        if(status==NULL)
        {
        	printf("There was an error while executing this command,try another one\n");
        }
        else
        {
        	fclose(status);
        	while(1)
        	{
	        	//char c=getch();
	        	// if(c=='q')
	        	// 	break;
	        	status = fopen(b,"r");  
	        	while((read=getline(&line ,&len, status))!=-1)
	        	{
	        		ptr = strtok(line ," \t\n\a\r");
	        		if(strcmp(ptr,"1:")==0)
	        		{
	        			printf("CPU0\tCPU1\tCPU2\tCPU3\tCPU4\tCPU5\tCPU6\tCPU7\n");
	        			int g=8;
	        			while(g--)
	        			{
		        			ptr = strtok(NULL, " \t\n\a\r");
	                        printf("%4s\t",ptr);
	        			}
	        			printf("\n");
	        			break;
	        		}
	        	}
	        	fclose(status);
	        	sleep(n);
	        }
        }
	}
	else
	{
		printf("Error while executing command ,try another one\n");
	}

}