#include "header.h"
void pwd()
{
    if(strncmp(local_home,current_path,strlen(local_home))==0)
	{
        printf("~");
        for(int i=strlen(local_home);i<strlen(current_path);i++)
        	printf("%c",current_path[i]);
        printf("\n");
	}
	else
	{
		printf("%s\n",current_path);
	}
}