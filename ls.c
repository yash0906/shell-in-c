#include "header.h"
void ls(char arr[200])
{
    DIR *d;
    int hidden =0;
    int expand=0;
    struct dirent *dir;
    struct stat fileStat;
    char *s = calloc(200,sizeof(char));
    char **tokens = calloc(200, sizeof(char*));
    char *arrcopy = arr;
    //printf("%s\n",arrcopy);
    char *ptr = strtok(arr," ");
    int i=0;
    while(ptr!=NULL)
    {
    	tokens[i++]=ptr;
        ptr = strtok(NULL, " ");
    }
    strcat(s,current_path);
    strcat(s,"/");
    if(tokens[1]==NULL)
    	strcat(s,".");
    else if(tokens[1][0]=='-')
    {
         if(tokens[1][1]=='l')
         	expand=1;
         if(tokens[1][1]=='a')
         	hidden=1;
         if(tokens[1][2]!='\0' && tokens[1][2]=='l')
         	expand=1;
         if(tokens[1][2]!='\0' && tokens[1][2]=='a')
         	hidden=1;
         int sum=hidden+expand;
         //printf("sum = %d\n",sum);
         // if(tokens[2]!=NULL)
         // {
         //     strcat(s,tokens[2]);
         // }
         char *a = "-a";
         char *l = "-l";
         if(hidden==0)
         	{
         		if(tokens[2]!=NULL)
         		{
         			if(strcmp(tokens[2],a)==0)
         				hidden=1;
         		}
            }
         if(expand==0)
         	{
         		if(tokens[2]!=NULL)
         		{
         			if(strcmp(tokens[2],l)==0)
         				expand=1;
         		}
            }
         int sum2 = hidden+expand;
         //printf("sum2 = %d\n",sum2);
         int p=0;
         if(sum2-sum>=1)
         {
         	p=1;
         	//printf("iander");
         	if(tokens[3]!=NULL)
         		{
         			 if(tokens[3][0]=='~')
                         strcpy(s,local_home);
                     else if(tokens[3][0]=='/')
                        strcpy(s,tokens[3]);
                     else
                    strcat(s,tokens[3]);
         			
         		}
         }
         if(p==0 && tokens[2]!=NULL)
         	{
                if(tokens[2][0]=='~')
                    strcpy(a,local_home);
                else if(tokens[2][0]=='/')
                    strcpy(s,tokens[2]);
                else
                    strcat(s,tokens[2]);
            }
    }
    else
    {
    	if(tokens[1][0]=='~')
            strcpy(s,local_home);
        else if(tokens[1][0]=='/')
            strcpy(s,tokens[1]);
        else
            strcat(s,tokens[1]);
    }
    //printf("expand = %d hidden = %d\n",expand,hidden);
    //printf("%s\n",s);
    d = opendir(s);
    if(d)
    {
     	int n = strlen(s);
     	while((dir = readdir(d)) != NULL)
     	{
     		//printf("%s\n",dir->d_name);
     		if(dir->d_name[0]!='.' || hidden==1)
     		{
			    char *asd = calloc(200, sizeof(char));
			    strcpy(asd,s);
                if(s[n-1]!='/')
                	strcat(asd,"/");
                strcat(asd,dir->d_name);
			    int k=stat(asd, &fileStat);
			    if(k<0)
			    {
			    	perror("error");
			    	continue;
			    }
			    if(expand==1)
			    {
				    //printf("%d\n",k);
				    printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
				    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
				    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
				    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
				    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
				    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
				    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
				    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
				    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
		            struct passwd *pw = getpwuid(fileStat.st_uid);
		            struct group *gr = getgrgid(fileStat.st_gid);
				    printf("\t%s\t%s",pw->pw_name, gr->gr_name);
				    //printf("%s",ctime(&fileStat.st_mtime));
				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        char * full_time = strtok(ctime(&fileStat.st_mtime)," ");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
				    char **break_time = malloc(1000*sizeof(char*));
				    int pos=0;
				    printf("%8ld\t",fileStat.st_size);
		            while(full_time!=NULL)
		            {
		            	break_time[pos++] = full_time;
		            	full_time = strtok(NULL, " ");
		            }
		            printf("%s %s %s ",break_time[1],break_time[2],break_time[3]);
		            free(break_time);
	            }
                if(S_ISDIR(fileStat.st_mode))
                    printf("\033[1;34m");
                else if(fileStat.st_mode & S_IXUSR)
                    printf("\033[1;32m");
     		    printf("%s\n",dir->d_name);
                printf("\033[0m");

     		    free(asd);
     	    }

     	}
     	closedir(d);
     }
     else
     perror("opendir");   
     free(s);
     free(tokens);
     return;
}