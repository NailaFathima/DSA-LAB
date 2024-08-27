#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 1000
int main()
{
    // to created a weighted adjacency matrix
    // 1-based indexing

    int num;
    scanf("%d",&num);
    int n = num+1;
    int rows = n;
    int cols = n;

    int **adj_matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        adj_matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    for(int i =0;i<n;i++)
    {
        for (int j = 0; j<n; j++)
        {
           adj_matrix[i][j] = INFINITY;
        }
    }
    
    int no_of_neighbours[n];
    for(int i=0;i<n;i++)
        no_of_neighbours[i] = 0;
        
    for(int i = 1;i<n;i++)
    {
        int node;
        scanf("%d ",&node);
        char c;
        scanf("%c",&c);
        while(c!='\n')
        {
            if(c!=' ')
            {
                int n = c -'0';
                adj_matrix[node][n] = 100;
                no_of_neighbours[node]++;
            }
            scanf("%c",&c);
        }
    }

    for(int i = 1;i<n;i++)
    {
        int node;
        scanf("%d",&node);
        
        int count = 0;
        while(count<no_of_neighbours[node])
        {   
            int wt;
            scanf("%d",&wt);
            count++;
            for(int i = 1;i<n;i++)
            {
                if(adj_matrix[node][i]==100)
                {
                    adj_matrix[node][i]= wt;
                    break;
                }
            }
        }
        continue;
    }

    int source;
    scanf("%d",&source);
    int shortest_path[n];
    for(int i=0;i<n;i++)
    {
        shortest_path[i] = INFINITY;
    }

    for(int i =1;i<n;i++)
    {
        if(adj_matrix[source][i]<shortest_path[i])
            shortest_path[i] = adj_matrix[source][i];
    }

    for(int k=1;k<n;k++)
    {
            for(int i=1;i<n;i++)
        {
            int min = shortest_path[i];
            for(int j=1;j<n;j++)
            {
                if(((adj_matrix[i][j]+min) < shortest_path[j]) && j!=source)
                    shortest_path[j] = adj_matrix[i][j]+min;
            }
        }
    }
    
    shortest_path[source] = 0;

    for(int i = 1;i< n;i++){
        printf("%d ",shortest_path[i]);
    }

    for (int i = 0; i < n; i++) {
        free(adj_matrix[i]);
    }
    free(adj_matrix);
    return 0;
}