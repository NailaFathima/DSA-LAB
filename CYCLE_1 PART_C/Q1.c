#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int *intersection[100];
int k = 0;

void set_hash_table(int *hash_table[],int table_size)
{
    for(int i = 0; i<table_size;i++)
        hash_table[i] = NULL;
}

void set_intersection(int *intersection[],int k)
{
    for(int i = 0; i<k;i++)
        intersection[i] = NULL;
    k = 0;
}

int check_hash_table_empty(int *hash_table[] , int table_size)
{
    int flag = 1;
    for(int i =0 ; i<table_size;i++)
    {   
        if(hash_table[i]!=NULL){
            flag = 0;
            return flag;
        }   
    }
    return flag;
}

void print_hash_table(int *hash_table[] , int table_size)
{
    int check = check_hash_table_empty(hash_table,table_size);
    if(check==1)
    {
        printf("-1");
        return;
    }
    for(int i =0 ; i<table_size;i++)
    {   
        if(hash_table[i]!=NULL)
            printf("%d ", *hash_table[i]);
    }
    return; 
}
int search_hash_table(int *hash_table[] , int key , int table_size)
{
    for(int i = 0; i<table_size;i++)
    {
        if (hash_table[i] != NULL && *hash_table[i] == key)
            return 1;
        // else if (hash_table[i] == NULL)
        //     return 0;
    }
    return 0;
}

void linear_probing(int arr[] , int * hash_table[] , int table_size , int num)
{
    for(int j=0;j<num;j++)
    {
        int i = j;
        int flag = search_hash_table(hash_table,arr[j],table_size); // check if the element is already present in hash table
        if(flag == 0) //if it is not present add it
        {
            while(hash_table[i%table_size]!=NULL)
                i++;
            int index = i%table_size;
            hash_table[index] = &arr[j];       
        }
    }
}

void print_union(int arr1[] , int arr2[] , int *hash_table[] , int num1 , int num2,int table_size)
{
    linear_probing(arr1,hash_table,num1,num1);

    for(int j = 0;j<num2;j++){
        int flag = search_hash_table(hash_table,arr2[j],table_size);
        if(flag == 0)
        {
            int i = j;
            while(hash_table[i%table_size]!=NULL)
            {
                i++;
            }
            hash_table[i%table_size] = &arr2[j];
        }
    }
}

int search_hash_table_difference(int *hash_table[] , int key , int table_size)
{
    for(int i = 0; i<=table_size;i++)
    {
        if (hash_table[i] != NULL && *hash_table[i] == key)
        {
            hash_table[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void print_difference(int arr1[] , int arr2[] , int *hash_table[] , int num1 , int num2,int table_size) //arr1 - arr2
{
    linear_probing(arr1,hash_table,num1,num1);

    for(int j = 0;j<num2;j++){
        int flag = search_hash_table_difference(hash_table,arr2[j],num1);
    }
}

int search_hash_table_intersection(int *hash_table[] , int key , int table_size)
{
    for(int i = 0; i<=table_size;i++)
    {
        if (hash_table[i] != NULL && *hash_table[i] == key)
        {
            //hash_table[i] = NULL;
            intersection[k++] = hash_table[i];
            hash_table[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void print_intersection(int arr1[] , int arr2[] , int *hash_table[] , int num1 , int num2,int table_size) //arr1 - arr2
{
    linear_probing(arr1,hash_table,table_size,num1);

    // print_hash_table(hash_table,table_size);

    // printf("$$$$$$\n");

    for(int j = 0;j<num2;j++){
        int flag = search_hash_table_intersection(hash_table,arr2[j],num1);
    }
}

int main()
{
    int m , n;
    scanf("%d %d",&m,&n);

    int a[m];
    int b[n];
    

    for(int i = 0; i<m;i++)
        scanf("%d",&a[i]);
    for(int i = 0; i<n;i++)
        scanf("%d",&b[i]);

    int table_size = (m>n) ? 2*m: 2*n;

    int *hash_table[table_size];

    char ans;

    /*MENU

    u -> prints the union of two arrays
    i -> prints the intersection of two arrays
    s -> prints the set difference of two arrays
    e -> exit

    */

   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='u')
    {   
        getchar();
        char c1,c2;
        scanf("%c %c",&c1,&c2);
        if(c1=='A')
        {
            set_hash_table(hash_table,table_size);  //a union b
            print_union(a,b,hash_table,m,n,table_size);
            print_hash_table(hash_table,table_size);
            printf("\n");
        }
        else
        {
            set_hash_table(hash_table,table_size);  //b union a
            print_union(b,a,hash_table,n,m,table_size);
            print_hash_table(hash_table,table_size);
            printf("\n");
        }
    }
    else if (ans=='i')
    {
        getchar();
        char c1,c2;
        scanf("%c %c",&c1,&c2);
        if(c1=='A')
        {
            set_hash_table(hash_table,table_size);
            set_intersection(intersection,k+1);
            print_intersection(b,a,hash_table,n,m,table_size); //a intersection b
            print_hash_table(intersection,k+1);
            printf("\n");
        }
        else
        {
            set_hash_table(hash_table,table_size);
            set_intersection(intersection,100);
            print_intersection(a,b,hash_table,m,n,table_size); //b intersection a
            print_hash_table(intersection,k+1);
            printf("\n");
        }
    }
    else if (ans=='s')
    {   
        getchar();
        char c1,c2;
        scanf("%c %c",&c1,&c2);
        if(c1=='A')
        {
            set_hash_table(hash_table,table_size);
            print_difference(a,b,hash_table,m,n,table_size); //a-b
            print_hash_table(hash_table,table_size);
            printf("\n");
        }
        else
        {
            set_hash_table(hash_table,table_size);
            print_difference(b,a,hash_table,n,m,table_size); //b-a
            print_hash_table(hash_table,table_size);
            printf("\n");
        }
    }
    scanf("%c",&ans);
    }
    return 0; 

}

