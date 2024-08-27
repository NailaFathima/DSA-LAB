#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void set_hash_table(int *hash_table[],int table_size)
{
    for(int i = 0; i<table_size;i++)
        hash_table[i] = NULL;
}

int linear_probing_index(int k , int i , int m)
{
    if(i==0)
        return k%m;
    return (linear_probing_index(k,0,m) + i)%m;
}

int linear_probing(int arr[] , int * hash_table[] , int table_size , int num)
{
    int no_of_collisions = 0;
    for(int j=0;j<num;j++){
        int i = 0;
        while(hash_table[linear_probing_index(arr[j],i,table_size)]!=NULL)
        {
            no_of_collisions++;
            i++;
        }
        int index = linear_probing_index(arr[j],i,table_size);
        hash_table[index] = &arr[j];
        printf("%d ",index);
    }

    return no_of_collisions;

}

int quadratic_probing_index(int k , int i , int m)
{
    if(i==0)
        return k%m;
    return (quadratic_probing_index(k,0,m) + i*i)%m;
}

int quadratic_probing(int arr[] , int * hash_table[] , int table_size , int num)
{
    int no_of_collisions = 0;
    for(int j=0;j<num;j++){
        int i = 0;
        while(hash_table[quadratic_probing_index(arr[j],i,table_size)]!=NULL)
        {
            no_of_collisions++;
            i++;
        }
        int index = quadratic_probing_index(arr[j],i,table_size);
        hash_table[index] = &arr[j];
        printf("%d ",index);
    }

    return no_of_collisions;

}

int prime(int table_size)
{
    int max = 2;
    for(int i = 2;i<table_size;i++)
    {
        int flag = 0;
        for(int j = 2; j<i;j++)
        {
            if(i%j==0)
            {
                flag = 1;
            }
        }
        if(flag==0 && i>max)
            max = i;
    }

    return max;
}

int h1(int key, int table_size)
{
    return key%table_size;
}

int h2(int key , int table_size)
{
    int r = prime(table_size);
    int num = r - (key%r);
    return num;
}

int double_hashing(int arr[] , int * hash_table[] , int table_size , int num)
{
    int no_of_collisions = 0;
    for(int j=0;j<num;j++){
        int i = 0;
        while(hash_table[(h1(arr[j],table_size)+i*h2(arr[j],table_size))%table_size]!=NULL)
        {
            no_of_collisions++;
            i++;
        }
        int index = (h1(arr[j],table_size)+i*h2(arr[j],table_size))%table_size;
        hash_table[index] = &arr[j];
        printf("%d ",index);
    }

    return no_of_collisions;
}

int main()
{
    int table_size;
    scanf("%d",&table_size);
    getchar();

    int arr[1000];
    int count = 0;
    int num = 0;   // Variable to store the formed number from input digits
    int sign = 1;  // Sign of the number
    while (1) {
        int input;
        // Read a character of input
        input = getchar();

        // If the input is Enter, break the loop
        if (input == '\n') {
            arr[count++] = sign * num;
            break;
        }

        if (input >= '0' && input <= '9') {
            // Multiply the formed number by 10 and add the new digit
            num = num * 10 + (input - '0');
        } else if (input == '-') {
            // Handle negative sign
            sign = -1;

        } else {
            // If input is not a digit or a negative sign, process the formed number
            arr[count++] = sign * num;
            // Reset the formed number and sign
            num = 0;
            sign = 1;

        }
    }
    // printf("%d\n",count);
    // for(int i = 0;i<count;i++)
    //   printf("%d ", arr[i]);

    int *hash_table[table_size];

    set_hash_table(hash_table,table_size);
    int numl = linear_probing(arr,hash_table,table_size,count);
    printf("\n");
    printf("%d",numl);
    printf("\n");

    set_hash_table(hash_table,table_size);
    int numq = quadratic_probing(arr,hash_table,table_size,count);
    printf("\n");
    printf("%d",numq);
    printf("\n");
 
    set_hash_table(hash_table,table_size);
    int numd = double_hashing(arr,hash_table,table_size,count);
    printf("\n");
    printf("%d",numd);
    printf("\n");
}
