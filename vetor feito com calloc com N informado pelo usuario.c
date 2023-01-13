//FELIPE BORGES BARROS 12211bsi250
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n=0,*p;

int main()
{
    while(n <= 0)
    {
        printf("digite o N:\n");
        scanf("%d",&n);
    }
    p = (int*) calloc (n,sizeof(int));
    int k;
    for(k=0; k < n; k++)
    {
        printf("digite o numero %d do vetor:\n",k);
        scanf("%d",(p + k));
    }
    for(int k = 0;k < n;k++)
    {
        printf("%d\n",p[k]);
    }









}



