#include "header.h"
void echo(char arr[200])
{
     if(arr[4]!=' ')
     	printf("Incorrect command:Are you thinking about echo\n");
     else
     {
     	int k=4;
     	while(arr[k]==' ')
     		k++;
     	for(int i=k;i<strlen(arr);i++)
     		printf("%c",arr[i]);
     	printf("\n");
     }
}
