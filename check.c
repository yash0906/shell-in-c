#include "header.h"
#include <time.h>
void check(char arr[200])
{
        char arr2[200];
	    strcpy(arr2,arr);
	    char **a = calloc(200, sizeof(char*));
        char *ptr = strtok(arr," \t\n\a\r");
	    int i=0;
	    while(ptr!=NULL)
	    {
	    	    a[i++]=ptr;
	    	    ptr = strtok(NULL, " \t\n\a\r");
	    }
	    if((a[1]!=NULL && a[1][0]=='&') || (a[2]!=NULL && a[2][0]=='&'))
	    {
            bg(arr2);
	    }  
	    else
	    {
	    	fg(arr2);
	    }
	    free(a);
  
}
int str_to_int(char arr[200])
{
     int k=strlen(arr);
     int r=1;
     int t=0;
     for(int i=k-1;i>=0;i--)
     {
          t+=(r*(arr[i]-'0'));
          r*=10;
     }
     return t;
}