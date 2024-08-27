#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Tree{
 int data;
 struct Tree *right;
 struct Tree *left;
};

typedef struct Tree *node;

// node to root
int j = 0;
int arr[100];


int i = 0;

node createNode(int key) 
{
    node temp; // declare a node
    temp = (node ) malloc (sizeof(struct Tree));
    // allocate memory using malloc()
    if(temp == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }

    temp->data = key;
    temp->right = NULL;
    temp->left = NULL; // make right and left point to null
    return temp; //return the new node
}

int isdigitt(char i)
{
    if(i!='('&&i!=')')
        return 1;
    else
        return 0;
}

void preorder(node root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(node root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

node construct_Tree(char s[] , int *index , int length) //to construct binary tree from string representation with parenthesis
{
    if(*index>=length || length==0)
    {
        return NULL;
    }

    int num=0;
    while(*index<length && isdigit(s[*index]))
    {
        int digit = s[*index]-'0';
        num = num*10 + digit;
        *index = *index + 1;
    }

    node head = createNode(num);

    // Check for left child
    if (*index < length && s[*index] == '(') {
        ++(*index);
        head->left = construct_Tree(s, index, length);
    }

    // Check for right child
    if (*index < length && s[*index] == '(') {
        ++(*index);
        head->right = construct_Tree(s, index, length);
    }

    // Skip the closing parenthesis
    ++(*index);
    return head;

}


void PrintRangeValues(node root , int k1 , int k2)
{
    if(root!=NULL)
    {
        PrintRangeValues(root->left,k1,k2);
        if(root->data >= k1 && root->data<= k2)
            printf("%d ",root->data);
        PrintRangeValues(root->right,k1,k2);
    }
}

int getPath(node root, int key)  //arr stores the ancestors;
{
    if(root==NULL)
        return 0;
    arr[j++] = root->data;

    if(root->data == key)
        return 1;
    
    if(getPath(root->left,key)||getPath(root->right,key))
        return 1;

    j--;
    return 0;
}


int main()
{
    char s[100];
    fgets(s, sizeof(s), stdin);
    node root = NULL;
    int index = 0;
    int length = strlen(s);
    root = construct_Tree(s,&index,length);
    // printf("INORDER\n");
    // inorder(root);
    // printf("\n");
    // printf("PREORDER\n");
    // preorder(root);
    // printf("\n");
    char ans;

    /*MENU

    p -> prints values in the specified range
    a -> prints the ancestors
    e -> exit

    */

   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='p')
    {
        int num1,num2;
        scanf("%d %d",&num1,&num2);
        //printf("%d\n",num1);
        //printf("%d\n",num2);
        PrintRangeValues(root,num1,num2);
        printf("\n");
    }
    else if (ans=='a')
    {
        int key;
        scanf("%d",&key);
        int dummy;
        dummy = getPath(root,key);
        while(j--)
        {
            printf("%d ",arr[j]);
        }
        printf("\n");
    }
    scanf("%c",&ans);
    }
    return 0; 

}
