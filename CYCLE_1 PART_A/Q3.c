#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct LinkedList{
    int severity;
    char name[100];
    char time[10];
    struct LinkedList* next;
};

typedef struct LinkedList *node;

node createNode(int severity , char name[] , char time[]) {
    node temp; // declare a node
    temp = (node ) malloc (sizeof(struct LinkedList));
    // allocate memory using malloc()
    if(temp == NULL)
        { 
            printf("Error creating a new node.\n");
            exit(0); 
        }
    temp->next = NULL; // make next point to NULL
    temp->severity = severity;
    strcpy(temp->name, name);
    strcpy(temp->time, time);

    return temp; //return the new node
}

void display(node head)
{
    node temp = head;
    while(temp!=NULL)
    {
        printf("%s %d %s\n" , temp->name , temp->severity , temp->time);
        temp = temp->next;
    }
}

void display_first(node head)
{
    printf("%s %d %s\n" , head->name , head->severity , head->time);
}

node list_search_func(node head, int severity) {
    node temp = head;
    // while (temp != NULL && temp->next != NULL && temp->severity >= severity) {
    //     temp = temp->next;
    // }
    while(temp!=NULL && temp->next!=NULL)
    {
        if(temp->severity >= severity && temp->next->severity < severity)
            return temp;
        else
            temp=temp->next;
    }
    return temp;
}

node list_search_for_delete(node head , char time[] , char name[])
{
    node temp = head;
    while(strcmp(temp->time , time)!=0 || strcmp(temp->name , name)!=0)
        temp = temp->next;
    return temp;
}


node list_insert_tail( node first , node temp) //function to insert at the end
{
    node p; 
    if(first == NULL) //when the linked list is empty
        first = temp;  
    else 
    {
      p = first; 
      while(p->next != NULL) 
        p = p->next; 
      p->next = temp; 
    }
    return first;
}

node list_insert(node head , int severity , char name[] , char time[]) //function to insert after particular node
{
    node temp,find,p ;
    temp = createNode(severity , name , time);
    
    if(head==NULL)
    {
        //printf("Inside 1\n");
        head = temp;
        return head;
    }
    else if(head->severity<temp->severity)
    {
        //printf("Inside 2\n");
        temp->next = head;
        head = temp;
        return head;
    }
    else
    {   
        find = list_search_func(head , severity);
        if(find->next!=NULL)
    {   
        //printf("Inside 3\n");
        //printf("Y\n");
        p = head;
        while(p!=find)
            p=p->next;
        node temp2;
        temp2 = p->next;
        temp->next = temp2;
        p->next = temp;
        return head;
    }
    else //node to be inserted is after the last node
    {
        //printf("Inside 4\n");
        head = list_insert_tail(head , temp);
        return head;
    }
    }
    
}

node list_delete_first(node head) //function to delete at the beginning
{
    if(head != NULL)
    {   
        if(head->next != NULL)
        {
            node temp;
            temp = head->next;
            printf("%s %d %s\n",head->name , head->severity , head->time);
            free(head);
            head = temp;
            return head;
        }
        else //linked list contains only one node
        {
            printf("%s %d %s\n",head->name , head->severity , head->time);
            free(head);
            head = NULL;
            return head;
        }
    }
    else
    {
        printf("-1\n");
        return head;
    }
}

node list_delete_first_copy(node head) //function to delete at the beginning
{
    if(head != NULL)
    {   
        if(head->next != NULL)
        {
            node temp;
            temp = head->next;
            //printf("%s %d %s\n",head->name , head->severity , head->time);
            free(head);
            head = temp;
            return head;
        }
        else //linked list contains only one node
        {
            //printf("%s %d %s\n",head->name , head->severity , head->time);
            free(head);
            head = NULL;
            return head;
        }
    }
    else
    {
        printf("-1\n");
        return head;
    }
}

node list_delete_last(node head) //function to delete at the end
{   
    node temp,temp2;
    if(head!=NULL)
    {
        if(head->next != NULL)
        {
            temp = head;
            while(temp->next->next != NULL)
            {   
                temp = temp->next;
            }
            //printf("%s %d %s\n",head->name , head->severity , head->time);
            free(temp->next);
            temp->next = NULL;
            return head;
        }
        else //thelinked list contains only one node
        {
            //printf("%s %d %s\n",head->name , head->severity , head->time);
            free(head);
            head = NULL;
            return head;
        }
    }
    else
    {
        printf("-1\n");
        return head;
    }
}

node list_delete(node head , char time[] , char name[]) //function to delete a particular node
{
    node temp;
    temp = list_search_for_delete(head ,time , name);
    node p = head;
    if(temp!=NULL)
    {
        if(temp == head) //if the node to be deleted is the first node
        {
            head = list_delete_first_copy(temp);
            return head;
        }
        else if(temp->next == NULL) //if the node to be deleted is the last node
        {
            head = list_delete_last(head);
            return head;
        }
        else
        {
            while(p->next != temp)
                p = p->next;
            node temp2;
            temp2 = p->next->next;
            //printf("%s %d %s\n",temp->name , temp->severity , temp->time);
            free(temp);
            p->next = temp2;
            return head;
        }
    }
    else
    {
        printf("-1");
        return head;
    }
}

node update_condition_priority(node head , char name[] , char time[] , int severity_new)
{
    node temp;
    head = list_delete(head , time , name);
    head = list_insert(head , severity_new , name ,time);
    return head;
}

int main()
{
    char ans;
    node head = NULL;
    /*MENU

    a -> insertion of node in priority queue
    t -> deletion of node at the beginning and deleted node's key is printed
    c -> prints the details of the node at beginning ( highest priority)
    d -> removes a specific node - check
    u -> update the severity of a node - check
    p -> prints the entire priority queue
    e -> exit

    */

   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='a')
    {
        int severity;
        char name [100];
        char time[10];
        scanf("%s %d %5s",name , &severity , time);
        //printf("Y\n");
        head = list_insert(head , severity ,  name , time);
    }
    else if (ans=='t')
    {
        head = list_delete_first(head);
    }
    else if (ans=='c')
    {
        display_first(head);
    }
    else if (ans=='d')
    {
        char name [100];
        char time[10];
        scanf("%s %s",name , time);
        head = list_delete(head , time ,name);
    }
    else if (ans=='u')
    {
        int severity_new;
        char name [100];
        char time[10];
        scanf("%s %s %d",name , time , &severity_new);
        head = update_condition_priority(head,name,time,severity_new);
    }
    else if (ans=='p')
    {
        display(head);
    }
    scanf("%c",&ans);
    }
    return 0; 
}
