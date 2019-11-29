#include "header.h"
void upkey(char arr[200])
{
    //printf("upkey\n");
    int n=strlen(arr);
    int k=0;
    for(int i=0;i<n;i++)
    {
    	if(arr[i]=='[')
    		k++;
    }
    //printf("k= %d",k);
    char* abs = calloc(200,sizeof(char));
    strcpy(abs,local_home);
    strcat(abs,"/history");
    char **a = calloc(1000,sizeof(char*));
    int q=0;
    size_t len=0;
    char *line = calloc(200,sizeof(char));
    ssize_t read;
    FILE *status;
    status = fopen(abs,"r");
    if(status!=NULL)
    {
    	while((read = getline(&a[q], &len, status))!=-1)
    	{
    		q++;
    	}
    	fclose(status);
    }
    //printf("q= %d\n",q);
    if(q-k<0)
        printf("Not enough command in history\n");
    else
        {
            //printf("%s",a[q-k]);
            FILE *p;
            p=fopen(abs,"a+");
            if(p!=NULL)
            {
                fputs(a[q-k],p);
                fputs("\n",p);
                fclose(p);
            }
            start();
            printf("%s",a[q-k]);
            mainloop(a[q-k]);
        }


}