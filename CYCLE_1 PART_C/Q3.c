#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linkedlist {
    char name[20];
    char rollno[10];
    int age;
    struct linkedlist *next;
};

typedef struct linkedlist *node;

node createNode(int age, char name1[], char rollno1[]) {
    node temp = (node)malloc(sizeof(struct linkedlist));
    if (temp == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    temp->age = age;
    strncpy(temp->name, name1, sizeof(temp->name) - 1);
    temp->name[sizeof(temp->name) - 1] = '\0'; // Ensure null-terminated
    strncpy(temp->rollno, rollno1, sizeof(temp->rollno) - 1);
    temp->rollno[sizeof(temp->rollno) - 1] = '\0'; // Ensure null-terminated
    temp->next = NULL;
    return temp;
}

int hash_function(char name[], int age)
{
    int length = strlen(name);
    int index = 0;
    for(int i =0;i<length;i++)
        index = index + name[i];
    index = index + age;
    return index%4;
}

void set_hash_table(node hash_table[], int table_size)
{
    for(int i = 0; i<table_size;i++)
        hash_table[i] = NULL;
}

void print_hash_table(node hash_table[], int table_size)
{
    for(int i = 0; i<table_size; i++)
    {
        if(hash_table[i]!=NULL)
        {
            node temp = hash_table[i];
            while(temp!=NULL)
            {
                printf("%s ",temp->name);
                printf("%s ",temp->rollno);
                printf("%d ",temp->age);
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
            int count = 0;
            node temp = hash_table[index];
            node temp1 = temp;
            while(temp1!=NULL)
            {
                count++;
                temp1=temp1->next;
            }
            printf("%d ",count);
            while(temp!=NULL)
            {
                printf("%s ",temp->name);
                // printf("%s ",temp->rollno);
                // printf("%d ",temp->age);
                temp=temp->next;
            }
            printf("\n");
        }
    else
        printf("0\n");
}

void printElementsInChainSameDept(node hash_table[] , int index , char a , char b)
{
    char rollno[20]; 
    int count = 0;
    if(hash_table[index]!=NULL)
        {
            node temp = hash_table[index];
            while(temp!=NULL)
            {   
                strcpy(rollno,temp->rollno);
                int j = strlen(rollno);
                if (rollno[j-1]==b && rollno[j-2==a])
                {
                    printf("%s ",temp->name);
                    count++;
                }   
                temp=temp->next;
            }
            // printf("\n");
        }
    if(count==0)
        printf("-1");
    else if(hash_table[index]==NULL)
        printf("-1");
    printf("\n");
}

void insert_hash_table(char name[], char rollno[],int age, int table_size,node hash_table[])
{
    node new = createNode(age,name,rollno);
    int index = hash_function(name,age);
    if (hash_table[index]==NULL)  //no collision
        hash_table[index] = new;
    
    else  //in case of collision
    {
        node temp = hash_table[index];
        while(temp->next!=NULL)
            temp = temp->next;
        temp->next = new;
    }
    return;
}

int main()
{
    int table_size;
    scanf("%d",&table_size);
    node hash_table[table_size];
    set_hash_table(hash_table,table_size);
    char ans;
    int k = table_size;

    for(int i =0;i<k;i++)
    {
        char name[20];
        char rollno[10];
        int age;
        scanf("%s",name);
        getchar();
        scanf("%s",rollno);
        getchar();
        scanf("%d",&age);
        insert_hash_table(name,rollno,age,table_size,hash_table);
    }
    /*MENU

    c (followed by k) -> prints the student list of group k
    m (followed by 2 characters) -> prints the names of students who belong to the given dept

    */
   getchar();
   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='c')
    {   
        getchar();
        int k;
        scanf("%d",&k);
        printElementsInChain(hash_table,k);
    }
    else
    {
        int k = ans - '0';
        getchar();
        char c1,c2;
        scanf("%c",&c1);
        scanf("%c",&c2);
        if(c1>=97)
            c1 = c1-32;
        if(c2>=97)
            c2 = c2-32;
        printElementsInChainSameDept(hash_table,k,c1,c2);
    
    }
    getchar();
    scanf("%c",&ans);
    }
    return 0; 

}
