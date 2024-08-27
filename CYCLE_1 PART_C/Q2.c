#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct linkedlist{
    int data;
    struct linkedlist *next;
};

typedef struct linkedlist *node;

node createNode(int key) {
node temp; // declare a node
temp = (node ) malloc (sizeof(struct linkedlist));
 // allocate memory using malloc()
if(temp == NULL)
    { 
        printf("Error creating a new node.\n");
        exit(0); 
    }
temp->data = key;
temp->next = NULL; // make next point to NULL
return temp; //return the new node
}

void set_hash_table(node hash_table[],int table_size)
{
    for(int i = 0; i<table_size;i++)
        hash_table[i] = NULL;
}

void print_hash_table(node hash_table[] , int table_size)
{
    for(int i = 0; i<table_size; i++)
    {
        if(hash_table[i]!=NULL)
        {
            node temp = hash_table[i];
            while(temp!=NULL)
            {
                printf("%d ",temp->data);
                temp=temp->next;
            }
            printf("\n");
        }
        else
            continue;
    }
}

void printElementsInChain(node hash_table[] , int index)
{
    if(hash_table[index]!=NULL)
        {
            node temp = hash_table[index];
            while(temp!=NULL)
            {
                printf("%d ",temp->data);
                temp=temp->next;
            }
            printf("\n");
        }
    else
        printf("-1\n");
}
void search_hash_table(node hash_table[], int table_size, int key)  //0-based indexing
{
    int index = key%table_size;
    node temp = hash_table[index];
    int pos = 0;
    int flag = 0;
    while(temp!=NULL)
    {
        if(temp->data==key)
        {
            flag = 1;
            break;
        }
        else
        {
            temp = temp->next;
            pos++;
        }
    }
    if(flag==1)
        printf("%d %d\n",index,pos+1);
    else
        printf("-1\n");
}

int search_hash_table_secondary(node hash_table[], int table_size, int key,int index)
{
    node temp = hash_table[index];
    while(temp!=NULL)
    {
        if(temp->data==key)
            return 1;
        else
            temp = temp->next;
    }
    return 0;
}

void insert_hash_table(int key,int table_size,node hash_table[])
{
    node new = createNode(key);
    int index = key%table_size;
    int check = search_hash_table_secondary(hash_table,table_size,key,index);
    if(check==0) //element not present
    {
        if (hash_table[index]==NULL)  //no collision
        hash_table[index] = new;
    
        else  //in case of collision
        {
            node temp = hash_table[index];
            if(key < temp->data)  //inserting at the head
            {
                new->next = temp;
                hash_table[index] = new;
            }
            else{
                while(temp->next!=NULL)
                {
                    if(temp->data < key && (temp->next == NULL || temp->next->data > key)) //no = sign because there wont be any duplicate elements
                        break;
                    else
                        temp = temp->next;
                }
                new->next = temp->next;
                temp->next = new;
            }
        }
    }
    else
        printf("-1\n");
    return;
}

void delete_hash_table(node hash_table[],int table_size , int key)
{
    int index = key%table_size;
    int check = search_hash_table_secondary(hash_table,table_size,key,index);
    search_hash_table(hash_table,table_size,key);
    if(check==1) //element is present
    {
        
        node temp = hash_table[index];
        node prev = NULL;
        while(temp!=NULL && temp->data!=key)
        {
            prev = temp;
            temp = temp->next;
        }
        if(prev==NULL)
            hash_table[index] = temp->next;
        else
        {
            prev->next = temp->next;
            free(temp);
        }
    }
    return;
}

void insert_hash_table_update(int key,int table_size,node hash_table[])
{
    node new = createNode(key);
    int index = key%table_size;
    int check = search_hash_table_secondary(hash_table,table_size,key,index);
    if(check==0) //element not present
    {
        if (hash_table[index]==NULL)  //no collision
        hash_table[index] = new;
    
        else  //in case of collision
        {
            node temp = hash_table[index];
            if(key < temp->data)  //inserting at the head
            {
                new->next = temp;
                hash_table[index] = new;
            }
            else{
                while(temp->next!=NULL)
                {
                    if(temp->data < key && (temp->next == NULL || temp->next->data > key)) //no = sign because there wont be any duplicate elements
                        break;
                    else
                        temp = temp->next;
                }
                new->next = temp->next;
                temp->next = new;
            }
        }
    }
    // else
    //     printf("-1\n");
    return;
}

void delete_hash_table_update(node hash_table[],int table_size , int key)
{
    int index = key%table_size;
    int check = search_hash_table_secondary(hash_table,table_size,key,index);
    search_hash_table(hash_table,table_size,key);
    if(check==1) //element is present
    {
        
        node temp = hash_table[index];
        node prev = NULL;
        while(temp!=NULL && temp->data!=key)
        {
            prev = temp;
            temp = temp->next;
        }
        if(prev==NULL)
            hash_table[index] = temp->next;
        else
        {
            prev->next = temp->next;
            free(temp);
        }
    }
    return;
}


void update_hash_table(node hash_table[],int table_size , int old_key , int new_key)
{
    int index_old_key = old_key%table_size;
    int index_new_key = new_key%table_size;
    int check_old_key = search_hash_table_secondary(hash_table,table_size,old_key,index_old_key);
    int check_new_key = search_hash_table_secondary(hash_table,table_size,new_key,index_new_key);
    if(check_new_key==0 && check_old_key==1)
    {
        delete_hash_table_update(hash_table,table_size,old_key);
        insert_hash_table_update(new_key,table_size,hash_table);
    }
    else
    {
        printf("-1");
    }
    return;
}

// int main()
// {
//     int table_size = 6;
//     //scanf("%d",&table_size);

//     node hash_table[table_size];

//     set_hash_table(hash_table,table_size);

//     insert_hash_table(1,table_size,hash_table);
//     insert_hash_table(2,table_size,hash_table);
//     insert_hash_table(7,table_size,hash_table);
//     insert_hash_table(14,table_size,hash_table);
//     insert_hash_table(0,table_size,hash_table);
//     insert_hash_table(4,table_size,hash_table);
//     insert_hash_table(3,table_size,hash_table);
//     insert_hash_table(13,table_size,hash_table);
//     insert_hash_table(15,table_size,hash_table);

//     print_hash_table(hash_table,table_size);
//     //printElementsInChain(hash_table,2);
//     //search_hash_table(hash_table,table_size,1);
//     search_hash_table(hash_table,table_size,7);
//     //delete_hash_table(hash_table,table_size,15);
//     update_hash_table(hash_table,table_size,7,6);
//     printf("////AFTER DELETION///\n");
//     print_hash_table(hash_table,table_size);
//     return 0;

    
// }

int main(){
    int table_size;
    scanf("%d",&table_size);
    node hash_table[table_size];
    set_hash_table(hash_table,table_size);
    char ans;

    /*MENU

    i (followed by integer) -> inserts the key in the hash_table
    d (followed by  integer) -> deletes the key in the hash_table
    u (followed by oldKey newKey) -> deletes the oldKey and inserts the newKey -> updates the hash_table
    s (followed by integer) -> searches for the key in hash table
    p (followed by integer) -> prints elements in chain k
    e -> terminates

    */

   //getchar();
   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='i')
    {   
        int k;
        scanf("%d",&k);
        insert_hash_table(k,table_size,hash_table);
    }
    else if (ans=='d')
    {
        int k;
        scanf("%d",&k);
        delete_hash_table(hash_table,table_size,k);
    }
    else if (ans=='u')
    {
        int old_key,new_key;
        scanf("%d %d",&old_key,&new_key);
        update_hash_table(hash_table,table_size,old_key,new_key);
    }
    else if (ans=='s')
    {
        int k;
        scanf("%d", &k);
        search_hash_table(hash_table,table_size,k);
    }
    else if (ans=='p')
    {
        int k;
        scanf("%d", &k);
        printElementsInChain(hash_table,k);
    }
    else if(ans =='a')
    {
        print_hash_table(hash_table,table_size);
    }

    scanf("%c",&ans);
    }
    return 0; 
}
