#include "header.h"
void cd(char arr[100])
{
	char *ptr = strtok(arr, " ");
	ptr = strtok(NULL, " ");
	// char s[100];
	// printf("%s\n",getcwd(s,100));
	if(ptr == NULL)
		{
			int k=chdir("/home/yash");
			//printf("%d\n",k);
			getcwd(current_path, 200);
		}
	else
	    {
			int n=strlen(ptr);
			char *s = calloc(200,sizeof(char));
			int i=0;
			while(ptr[i]!='~' && i<n)
			{
				s[i]=ptr[i];
				i++;
			}
            if(i<n)
            {
            	strcat(s,local_home);
            	i++;
            }
            int k=strlen(s);
            while(i<n)
            {
            	s[k]=ptr[i];
            	i++;
            	k++;
            }
            //printf("%s\n",s);
			k=chdir(s);
			//printf("%d\n",k);
			getcwd(current_path,200);
			free(s);
			//free(ptr);
		}
	//printf("%s\n",getcwd(s,100));
    
}