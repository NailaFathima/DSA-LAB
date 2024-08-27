#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int top = -1;
int ind = 0;
int no_of_bridges = 0;
int no_of_ap = 0;

int min(int a, int b)
{
    return (a<b)?a:b;
}

void append_sizes(int sizes[], int visited[], int n)
{
    int count = 0;
    for(int i = 1;i<n;i++)
    {
        if(visited[i]==1)
            count++;
    }
    if(ind == 0)
        sizes[ind]=count;
    else
    {
        int sum = 0;
        for(int i=0;i<ind;i++)
            sum = sum + sizes[i];

        count = count - sum;
        sizes[ind] = count;
    }
    //printf("count = %d ",count);
    ind++;

    return;
}

void sort_and_print(int arr[] , int index)
{
    int key,i;
    for(int j =1;j<index;j++)
    {
        key = arr[j];
        i = j-1;
        while(i>=0 && arr[i]>key)
        {
            arr[i+1] = arr[i];
            i = i-1;
        }
        arr[i+1] = key;
    }

    for(int k =0;k<index;k++)
        printf("%d ",arr[k]);
    printf("\n");
}

void print_adj_matrix(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int stack_not_empty(int stack[])
{
    if(top==-1)
        return 0;
    else
        return 1;
}
int pop(int stack[])
{
    int check = stack_not_empty(stack);
    if (check==-1)
    {    
        return -1;
    }
    else
    {
        int num = stack[top];
        top--;
        return num;
    }
}
void push(int stack[] , int data)
{
    top = top+1;
    stack[top] = data;
    return;
}

void dfs(int **adj_matrix, int n, int u,int visited[],int stack[]) {
    visited[u] = 1; // Mark current vertex as visited
    //printf("%d ", u); // Print the current vertex

    // Visit all adjacent vertices of vertex u
    for (int v = 0; v < n; v++) {
        if (adj_matrix[u][v] == 1 && !visited[v]) {
            dfs(adj_matrix, n, v,visited,stack); // Recursive call to DFS for adjacent unvisited vertex
        }
    }
    push(stack,u);

}

void dfs_for_bridge(int u, int ** adj_matrix, int visited[], int disc[],int low[],int parent,int n)
{
    static int time = 0;
    visited[u] = 1;
    disc[u] = low[u] = ++time;

    for(int i  = 1;i<n;i++)
    {
        if(adj_matrix[u][i]==1)
        {
            int v = i;

            if(v==parent)
                continue;
            
            if(visited[v])
            {
                low[u] = min(low[u],disc[v]);
            }

            else
            {
                parent = u;
                dfs_for_bridge(v,adj_matrix,visited,disc,low,parent,n);

                low[u] = min(low[u],low[v]);
                if(low[v]>disc[u])
                    no_of_bridges++;
            }
        }
    }
}

void dfs_for_ap(int u, int ** adj_matrix, int visited[], int disc[],int low[],int parent,int n,int isAP[])
{

    int no_of_children = 0;
    static int time = 0;
    visited[u] = 1;
    disc[u] = low[u] = ++time;

    for(int i  = 1;i<n;i++)
    {
        if(adj_matrix[u][i]==1)
        {
            if(!visited[i])
            {
                no_of_children++;
                dfs_for_ap(i,adj_matrix,visited,disc,low,parent,n,isAP);

                low[u] = min(low[u],low[i]);

                if(parent!= -1 && low[i]>=disc[u])
                {
                    isAP[u] = 1;
                    no_of_ap++;
                }
                    
            }

            else if(i != parent)
                low[u] = min(low[u],disc[i]);
        }
    
    }
    if(parent == -1 && no_of_children > 1)
            no_of_ap++;


}

int main()
{
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
           adj_matrix[i][j] = 0;
        }
    }
       
        
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
                adj_matrix[node][n] = 1;
            }
            scanf("%c",&c);
        }
    }
    
    int visited[n];
    for(int i =0;i<n;i++)
        visited[i] = 0;
    
    int stack[n];

    int sizes[n];

    char ans;

    /* 
    n - no of connected components
    s - size of connected components
    b - no of bridges
    a - no of articulation points
    t - terminates
    */

   scanf("%c",&ans);

   while(ans!='t')
   {
        if(ans=='n')
        {
            for(int i =0;i<n;i++)
                visited[i] = 0;
            
            top = -1;
            int scc = 0;
            ind = 0;


            for (int i = 1; i < n; i++) 
            {
                if (!visited[i]) 
                {   
                    scc++;
                    dfs(adj_matrix, n, i,visited,stack);
                    append_sizes(sizes,visited,n);
                }
            }

            printf("%d\n",scc);
            //sort_and_print(sizes,ind);
        }
        else if(ans== 's')
        {
            for(int i =0;i<n;i++)
                visited[i] = 0;
            
            top = -1;
            int scc = 0;
            ind = 0;


            for (int i = 1; i < n; i++) 
            {
                if (!visited[i]) 
                {   
                    scc++;
                    dfs(adj_matrix, n, i,visited,stack);
                    append_sizes(sizes,visited,n);
                }
            }

            //printf("%d\n",scc);
            sort_and_print(sizes,ind);
        }
        else if(ans=='b')
        {
            for(int i =0;i<n;i++)
                visited[i] = 0;
            int low[n];
            int disc[n];
            top = -1;
            int parent = -1; //no parent initially
            for(int i = 1;i<n;i++)
            {
                if(visited[i]!=1)
                    dfs_for_bridge(i,adj_matrix,visited,low,disc,parent,n);
            }
            printf("%d\n",no_of_bridges);
        }
        else if(ans=='a')
        {
            int low[n];
            int disc[n];
            int isAP[n];
            for(int i =0;i<n;i++)
            {
                visited[i] = 0;
                disc[i] = 0;
                isAP[i] = 0;
            }
            int parent = -1;
            for(int i = 1;i<n;i++)
            {
                if(visited[i]!=1)
                    dfs_for_ap(i,adj_matrix,visited,low,disc,parent,n,isAP);
            }
             printf("%d\n",no_of_ap);

        }

        scanf("%c",&ans);
    }
    return 0;

}
