#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // to created a weighted adjacency matrix
    // 0-based indexing
    // used prim's algo hehe :)
    
    int n;
    scanf("%d",&n);
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
           adj_matrix[i][j] = 0;
        }
    }
    
    int no_of_neighbours[n];
    for(int i=0;i<n;i++)
        no_of_neighbours[i] = 0;
        
    for(int i = 0;i<n;i++)
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

    for(int i = 0;i<n;i++)
    {
        int node;
        scanf("%d",&node);
        
        int count = 0;
        while(count<no_of_neighbours[node])
        {   
            int wt;
            scanf("%d",&wt);
            count++;
            for(int i = 0;i<n;i++)
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

    // for(int i = 0;i<n;i++)
    // {
    //     for(int j = 0;j<n;j++)
    //     {
    //         printf("%d ", adj_matrix[i][j]);
    //     }
    //     printf("\n");  
    // }

    int mst[n];  //1 if the node is already present in the mst; 0 otherwise
    int parent[n];  //maintains the parent to each node
    int key[n];  //maintains the least wait to each vertex from the source vertex

    for(int i=0;i<n;i++)
    {
        mst[i] = 0;
        key[i] = 10000;

    }

    //initialising source vertex as 0
    key[0] = 0;
    parent[0] = -1;
    mst[0] = 1;

    for(int i=0;i<n;i++)
    {
        int min = 10000;
        int min_node;
        for(int i =0;i<n;i++)
        {
            if(mst[i]==0)
            {
                if(key[i]<min)
                {
                    min = key[i];
                    min_node = i;
                }
            }
        }
        mst[min_node] = 1;
        for(int j =0;j<n;j++)
        {
            if((adj_matrix[min_node][j]!=0) && (mst[j]==0) && (adj_matrix[min_node][j]<key[j]))
            {
                key[j] = adj_matrix[min_node][j];
                parent[j] = min_node;
            }
        }
    }

    int sum = 0;
    for(int i =0;i<n;i++)
        sum = sum + key[i];

    printf("%d",sum);

    return 0;
    
}
