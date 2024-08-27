#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITY 10000

int min(int a , int b)
{
    if(a<b)
        return a;
    return b;
}

int main()
{
    int num;
    scanf("%d",&num);
    int n = num;
    int rows = n;
    int cols = n;

    int **adj_matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        adj_matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            scanf("%d",&adj_matrix[i][j]);
            if(adj_matrix[i][j]==-1)
                adj_matrix[i][j] = INFINITY;
        }
    }

    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                adj_matrix[i][j] = min(adj_matrix[i][j], adj_matrix[i][k] + adj_matrix[k][j]);
            }
        }
    }

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            if(adj_matrix[i][j]>100)
                printf("-1 ");
            else
                printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");  
    }
}

