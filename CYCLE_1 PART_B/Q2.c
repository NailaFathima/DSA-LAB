#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

struct Tree{
 int data;
 struct Tree *right;
 struct Tree *left;
};

typedef struct Tree *node;

int i = 0;

// node to root
int j = 0;
int arr[100];

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

void preorder(node root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
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


void left_view(node root, int level)
{
    if(root==NULL)
        return;
    if(level==i)
    {
        printf("%d ",root->data);
        i++;
    }
        
    left_view(root->left,level+1);
    left_view(root->right,level+1);

}

void right_view(node root, int level)
{
    if(root==NULL)
        return;
    if(level==i)
    {
        printf("%d ",root->data);
        i++;
    }
        
    right_view(root->right,level+1);
    right_view(root->left,level+1);

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

int getPath(node root, int key)
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

void levelorder(node root)
{
    node array[100];
    int a = 0;
    int b = 0;

    array[a++] = root;
    
    while(b!=a)
    {
        if(array[b]->left!=NULL)
            array[a++] = array[b]->left;
        if(array[b]->right!=NULL)
            array[a++] = array[b]->right;
        b++;
    }

    int start;
    for(start = 0; start<a ; start++)
         printf("%d ",array[start]->data);

}

int isValidBST(node root, int min, int max) {
    if (root == NULL)
        return 1;
    if (root->data <= min || root->data >= max)
        return 0;
    return isValidBST(root->left, min, root->data) && isValidBST(root->right, root->data, max);
}

int sumOfKeys(node root) {
    if (root == NULL)
        return 0;
    return root->data + sumOfKeys(root->left) + sumOfKeys(root->right);
}

int maxSumBSTUtil(node root, int* maxSum) {
    if (root == NULL)
        return 0;
    
    // Check if the subtree rooted at 'root' is a valid BST
    if (isValidBST(root, INT_MIN, INT_MAX)) {
        int sum = sumOfKeys(root); // Calculate the sum of keys in the subtree
        *maxSum = (*maxSum < sum) ? sum : *maxSum; // Update the maximum sum if needed
    }
    
    // Recursively check left and right subtrees
    maxSumBSTUtil(root->left, maxSum);
    maxSumBSTUtil(root->right, maxSum);
    
    return *maxSum;
}

int maximumSumBST(node root) {
    int maxSum = 0;
    maxSumBSTUtil(root, &maxSum);
    return maxSum;
}

// int main()
// {
//     //dry run for Q2
//     node root = createNode(1);
//     root->left = createNode(4);
//     root->right = createNode(3);
//     root->left->left = createNode(2);
//     root->left->right = createNode(4);
//     root->right->left = createNode(2);
//     root->right->right = createNode(5);
//     root->right->right->left = createNode(4);
//     root->right->right->right = createNode(6);

//     //right_view(root,0);

//     //levelorder(root);

//     int sum = maximumSumBST(root);
//     printf("%d\n",sum);

//     return 0;
// }

// int main()
// {
//     //dry run for Q3
//     node root = createNode(7);
//     root->left = createNode(5);
//     root->right = createNode(9);
//     root->left->left = createNode(2);
//     root->left->right = createNode(6);
//     root->right->left = createNode(8);
//     root->right->right = createNode(10);

//     // preorder(root);
//     // printf("\n");
//     PrintRangeValues(root,5,8);
//     printf("\n");
//     //PRINTING ANCESTORS
//     int dummy;
//     dummy = getPath(root,8);
//     while(j--)
//     {
//         printf("%d ",arr[j]);
//     }

// }

int main()
{
    char s[100];
    fgets(s, sizeof(s), stdin);
    node root = NULL;
    int index = 0;
    int length = strlen(s);
    root = construct_Tree(s,&index,length);
    char ans;

    /*MENU

    l -> prints the level order traversal of tree
    m -> prints the maximum sum of a subtree which is bst
    r -> prints right view of tree
    e -> exit

    */

   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='l')
    {
        levelorder(root);
        printf("\n");
    }
    else if (ans=='m')
    {
        int sum = maximumSumBST(root);
        printf("%d\n",sum);
    }
    else if (ans=='r')
    {
        right_view(root,0);
        printf("\n");
    }
    scanf("%c",&ans);
    }
    return 0; 

}
