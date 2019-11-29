#include "header.h"
void history(char arr[200])
{
	char *ptr = strtok(arr, " \t\n\a\r");
	ptr = strtok(NULL, " \t\n\a\r");
	int n=-1;
	if(ptr == NULL)
        n=10;
    else
    {
    	int k=strlen(ptr);
    	int r=0;
    	int l=ptr[--k]-'0';
    	if(k==1)
    		r=ptr[--k]-'0';
    	
    	n = 10*r + l;  
    }
    char **a = calloc(1000,sizeof(char*));
    int q=0 ;
    size_t len = 0;
    char *line = calloc(200, sizeof(char));
    ssize_t read;
    FILE *status;
    char *abs = calloc(200,sizeof(char));
    strcpy(abs,local_home);
    strcat(abs,"/history");
    status=fopen(abs,"r");
    if(status!=NULL)
    {	
    while((read = getline(&a[q], &len, status))!=-1)
	   {
			q++;
	   }
	   fclose(status);
	}
    //printf("%d\n",n);
	if(n>q)
		n=q;
	int start = q-1;
    while(n)
    {
    	printf("%s", a[start]);
    	n--;
    	start--;
    }
    free(a);
}