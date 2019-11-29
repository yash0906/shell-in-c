#include "header.h"
char fixed[200];
int ret=0;
char* commands[] = {"ls", "cd", "pwd", "echo", "pinfo", "history" , "nightswatch", "quit", "c", "[A", "setenv" , "unsetenv", "getenv","cronjob", "jobs","kjob", "overkill", "bg", "fg"};
void handle_sigint(int sig)
{
	//printf("curr = %d\n   shell = %d",curr_running,shell_pid);
	//if(curr_running!=shell_pid)
	//{
	if(curr_running>0)
	kill(curr_running ,9);
	//}
	// else
	// 	start();
}
void start()
{
	if(strncmp(local_home,current_path,strlen(local_home))==0)
	{
        char *buff = (char*)calloc(1+strlen(current_path)-strlen(local_home),sizeof(char));
        buff[0]='~';
        int k=1;
        for(int i=strlen(local_home);i<strlen(current_path);i++)
        {
        	buff[k]=current_path[i];
        	k++;
        }

        printf("\033[1;32m");
        printf("%s",fixed);
        printf("\033[1;34m");
        printf("%s%s",buff,">");
        printf("\033[0m");
        free(buff);
	}
	else
	{
		printf("\033[1;32m");
        printf("%s",fixed);
        printf("\033[1;34m");
        printf("%s%s",current_path,">");
        printf("\033[0m");
	}
}
void init()
{
	
	char *username = getenv("USER");
    
	//gethostname(hostname,sizeof(hostname));
	struct utsname userInfo;
    uname(&userInfo);
    const char *hostname = userInfo.sysname;
	strcat(fixed,"<");
	strcat(fixed, username);
	strcat(fixed,"@");
	strcat(fixed,hostname);
	strcat(fixed,":");
	getcwd(local_home,100);
	strcpy(current_path,local_home);
}
void mainloop(char input[200])
{
		//curr_running = shell_pid;
	signal(SIGINT, SIG_IGN);
		char *colon_sep = strtok(input, ";");
		char **comm = calloc(200, sizeof(char*));
		int i=0;
		while(colon_sep!=NULL)
		{
			comm[i] = colon_sep;
			colon_sep = strtok(NULL, ";");
			i++;
		}
		i=0;
		//printf("%s\n",comm[0]);
		//printf("%sqwer\nqwer",qwer);
		//printf("%d\n",strcmp(qwer,comm[0]));
		while(comm[i]!=NULL)
			{
				//printf("%s",comm[i]);
				int p=0;
				for(int j=0;j<strlen(comm[i]);j++)
				{
					if(comm[i][j]=='|' || comm[i][j]=='>' || comm[i][j]=='<')
						{
							p=1;
							break;
						}
				}
				if(p==1)
					piping(comm[i]);
                else if(strncmp(comm[i], commands[0], strlen(commands[0]))==0)
                    ls(comm[i]);
                else if(strncmp(comm[i], commands[1], strlen(commands[1]))==0)
                	cd(comm[i]);
                else if (strncmp(comm[i], commands[2], strlen(commands[2]))==0)
                    pwd();
                else if (strncmp(comm[i], commands[3], strlen(commands[3]))==0)
                    echo(comm[i]);
                else if (strncmp(comm[i], commands[4], strlen(commands[4]))==0)
                	pinfo(comm[i]);
                else if(strncmp(comm[i], commands[5], strlen(commands[5]))==0)
                	history(comm[i]);
                else if(strncmp(comm[i], commands[6], strlen(commands[6]))==0)
                	nightswatch(comm[i]);
                else if(strncmp(comm[i], commands[7], strlen(commands[7]))==0)
                	ret =1;
                else if(strncmp(comm[i], commands[8], strlen(commands[8]))==0 && (strlen(comm[i])==strlen(commands[8])))
                	printf("\e[1;1H\e[2J");
                else if(strncmp(comm[i], qwer,strlen(qwer))==0)
                	upkey(comm[i]);
                else if(strncmp(comm[i], commands[10],strlen(commands[10]))==0)
                	set(comm[i]);
                else if(strncmp(comm[i], commands[11],strlen(commands[11]))==0)
                	unset(comm[i]);
                else if(strncmp(comm[i], commands[12],strlen(commands[12]))==0)
                	get(comm[i]);
                else if(strncmp(comm[i], commands[13],strlen(commands[13]))==0)
                	bg(comm[i]);
                else if(strncmp(comm[i], commands[14],strlen(commands[14]))==0)
                	jobs();
                else if(strncmp(comm[i], commands[15],strlen(commands[15]))==0)
                	kjobs(comm[i]);
                else if(strncmp(comm[i], commands[16],strlen(commands[16]))==0)
                	overkill();
                else if(strncmp(comm[i], commands[17],strlen(commands[17]))==0)
                	bgup(comm[i]);
                else if(strncmp(comm[i], commands[18],strlen(commands[18]))==0)
                	fgup(comm[i]);
                else
                	check(comm[i]);
                i++;
			}
			//printf("done\n");
			//free(input);
			free(comm);

}
int main()
{
	bgn=0;
	signal(SIGINT, handle_sigint);	
	for(int i=1;i<=100;i++)
		bg_jobs[i].pid = -1;
	shell_pid = getpid();
	//curr_running = shell_pid;
	qwer[0]=27;
	qwer[1]='[';qwer[2]='A';
	original_out = dup(1);
	original_in = dup(0);
	char *abs = calloc(200,sizeof(char));
	printf("\e[1;1H\e[2J");
	init();
	hist_n=0;
	FILE *p;
	strcpy(abs,local_home);
	strcat(abs,"/history");
	while(1)
	{
        start();
        char* input = (char*)calloc(1000, sizeof(char));
		scanf("%[^\n]s",input);
		int n=strlen(input);
		//printf("%d\n",n);
		getchar();
		//printf("input = %s",input);
        p=fopen(abs,"a+");
        if(p!=NULL && input[0]!=27)
		{
			fputs(input,p);
			fputs("\n",p);
			fclose(p);
		}
		else if(input[0]!=27)
		{
			perror("cannot write to history file");
		}
		//printf("%s\n",input);
		mainloop(input);
		free(input);
		if(ret==1)
			{
				overkill();
				kill(shell_pid, SIGINT);
				return 0;
			}

	}
	fclose(p);
	return 0;
}