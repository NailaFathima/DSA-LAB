#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct LinkedList{
 int data;
 struct LinkedList *next;
};

typedef struct LinkedList *node;

node createNode() {
 node temp; // declare a node
 temp = (node ) malloc (sizeof(struct LinkedList));
 // allocate memory using malloc()
 if(temp == NULL)
    { 
        printf("Error creating a new node.\n");
        exit(0); 
    }
 temp->next = NULL; // make next point to NULL
 return temp; //return the new node
}

node list_insert_tail( node first , int data) //function to insert at the end
{
    node temp,p; 
    temp = createNode();
    temp->data = data;
    temp->next=NULL; 
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

node search_using_index(node head, int index)
{
    node p;
    p = head;
    int count = 1;
    if(head!=NULL)
    {
        while(p!=NULL)
        {
            if(count==index)
                return p;
            else
            {
                count++;
                p=p->next;
            }
        }
        printf("-1\n");  //when node of particular index is not found
        return NULL;
    } 
    else //when linked list is empty
    {
        printf("-1\n");
        return NULL;
    }   
}
node list_delete_first(node head) //function to insert at the beginning
{
    if(head != NULL)
    {   
        if(head->next != NULL)
        {
            node temp;
            temp = head->next;
            printf("%d\n",head->data);
            free(head);
            head = temp;
            return head;
        }
        else //linked list contains only one node
        {
            printf("%d\n" , head->data);
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
            printf("%d\n", temp->next->data);
            free(temp->next);
            temp->next = NULL;
            return head;
        }
        else //thelinked list contains only one node
        {
            printf("%d\n" , head->data);
            free(head);
            head = NULL;
            return head;
        }
    }
    else
    {
        //printf("-1\n");
        return head;
    }
}

node list_delete_last_copy(node head) //function to delete at the end
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
            //printf("%d\n", temp->next->data);
            free(temp->next);
            temp->next = NULL;
            return head;
        }
        else //thelinked list contains only one node
        {
            //printf("%d\n" , head->data);
            free(head);
            head = NULL;
            return head;
        }
    }
    else
    {
        //printf("-1\n");
        return head;
    }
}

node list_delete(node head , int index) //function to delete a particular node using index
{
    node temp;
    temp = search_using_index(head , index);
    node p = head;
    if(temp!=NULL)
    {
        if(temp == head) //if the node to be deleted is the first node
        {
            head = list_delete_first(temp);
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
            printf("%d\n",p->next->data);
            free(p->next);
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

void delete_node(node head , node temp) //function to delete a particular node using index
{   
    node p = head;
    if(temp->next == NULL) //if the node to be deleted is the last node
    {
        head = list_delete_last_copy(head);
        //return head;
    }
    else
    {
        while(p->next != temp)
            p = p->next;
        node temp2;
        temp2 = p->next->next;
        //printf("%d\n",p->next->data);
        free(p->next);
        p->next = temp2;
        //return head;
    }
    
}

void printlist(node head) //function to print the LL
{
  if(head==NULL)
    printf("\n");
  else
  {
    while(head->next!=NULL)
    {
      printf("%d ",head->data);
      head=head->next;
    }
    printf("%d\n",head->data);
  }
}

node list_reverse(node head) //function to reverse the LL
{
    node prev , current , next;
    current = head;
    prev = NULL;
    while(current!=NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    //printf("%d\n",prev->data);
    return prev;
}

node middle(node head)
{
    node slow = head;
    node fast = head;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void list_palindrome(node head)
{
    if(head==NULL)
    {
        printf("Y\n");
        return;
    }
    else
    {
        node mid = middle(head);
        node last = list_reverse(mid->next);
        mid->next = last;
        //printlist(head);

        node current = head;
        while(last!=NULL)
        {
            if(last->data != current->data)
        
            {   
                printf("N\n");
                return;
            }
            {   //printf("%d %d\n",last->data,current->data);
                last = last->next;
                current = current->next;
            }

        }
        if(current!=NULL && current->data != mid->data)
        {
            printf("N\n");
            return;
        }
        printf("Y\n");
        return;
    }
}

void list_duplicate(node head)

{   
    //printf("Inside duplicate function\n");
    int map[101];
    for(int i =0;i<101;i++)
        map[i] = 0;
    node ptr = head;
    while(ptr!=NULL)
    {
        if(map[ptr->data]!=1)
        {
            map[ptr->data] = 1;
            //printf("%d %d\n" , ptr->data , map[ptr->data]);
            ptr = ptr->next;
        }    
        else
        {
            node temp = ptr;
            ptr = ptr->next;
            delete_node(head , temp);
            
        }
           
    }

    printlist(head);
}

int main()
{
    char ans[100];
    node head = NULL;
    /*MENU

    t -> insrtion at the last
    r -> deletion of node at particular index and deleted node's key is printed
    p -> check if the linked list is palindrome or not //return Y for yes and N for no
    d -> removes duplicates and prints the updated list
    s -> print the list
    e -> exit

    */

   scanf("%s" , ans);
   while((strcmp(ans,"e")!=0))
   {
    if ((strcmp(ans,"a")==0))
    {
        int key;
        scanf("%d",&key);
        head = list_insert_tail(head , key);
    }
    else if ((strcmp(ans,"r")==0))
    {
        int index;
        scanf("%d",&index);
        head = list_delete(head , index);
    }
    else if ((strcmp(ans,"p")==0))
    {
        list_palindrome(head);
    }
    else if ((strcmp(ans,"d")==0))
    {
        list_duplicate(head);
    }
    else if ((strcmp(ans,"s")==0))
    {
        printlist(head);
    }
    scanf("%s",ans);
    }
    return 0; 
}



