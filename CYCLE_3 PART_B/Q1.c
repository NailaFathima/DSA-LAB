#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
        }
    }

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
        for(int k =0;k<n;k++)
        {
            if(mst[k]==0)
            {
                if(key[k]<min)
                {
                    min = key[k];
                    min_node = k;
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
    for(int m =0;m<n;m++)
        sum = sum + key[m];

    printf("%d\n",sum);

    return 0;
}

