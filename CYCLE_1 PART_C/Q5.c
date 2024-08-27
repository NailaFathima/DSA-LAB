#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void countDistinctElements(int hash_table[] , int arr [], int n , int k)
{
    int distinct_count = 0;

    for(int i =0;i<k;i++)
    {
        if(hash_table[arr[i]]==0)
            distinct_count++;
        
        hash_table[arr[i]]++;

    }

    printf("%d ",distinct_count);

    for(int i = k;i<n;i++)
    {
        if(hash_table[arr[i-k]]==1)
            distinct_count--;
        
        hash_table[arr[i-k]]--;

        if(hash_table[arr[i]]==0)
            distinct_count++;

        hash_table[arr[i]]++;

        printf("%d ",distinct_count);
    }
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int arr[n];
    int hash_table[n];

    for(int j = 0;j<n;j++)  //initialising all elements in hash table to zero
        hash_table[j] = 0;

    for(int j = 0;j<n;j++)
        scanf("%d",&arr[j]);

    countDistinctElements(hash_table,arr,n,k);

    return 0;
}
