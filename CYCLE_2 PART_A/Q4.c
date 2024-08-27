#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct rb_tree{
    int data;
    char color;
    struct rb_tree *left;
    struct rb_tree *right;
    struct rb_tree *parent;
};

typedef struct rb_tree *node;

node createNode(int key) 
{
    node temp; // declare a node
    temp = (node ) malloc (sizeof(struct rb_tree));
    // allocate memory using malloc()
    if(temp == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }

    temp->data = key;
    temp->right = NULL;  // make right,left,parent point to null
    temp->left = NULL;
    temp->parent = NULL;
    temp->color = 'B';//every node is inserted as leaf node
    return temp; //return the new node
}

void preorder(node root)
{
    if(root!=NULL)
    {
        //if(root->color!='X')
        printf("%d %c ",root->data , root->color);
        preorder(root->left);
        preorder(root->right);
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
    //printf("%d ",num);
    if (*index < length && (s[*index + 1] == 'R' || s[*index+1]=='B')) {
        ++(*index);
        head->color = s[*index];
        *index = *index + 2;

    }

    // Check for left child
    if (*index < length && s[*index] == '(') {
        *index = *index + 1;
        head->left = construct_Tree(s, index, length);
    }

    // Check for right child
    if (*index < length && s[*index] == '(') {
        *index = *index + 1;
        head->right = construct_Tree(s, index, length);
    }

    // Skip the closing parenthesis
    ++(*index);
    return head;

}

int checkRedblackTree(node root, int *blackHeight) {
    // Base case: Empty tree is a valid red-black tree
    if (root == NULL) {
        *blackHeight = 0;
        return 1;
    }

    int leftBlackHeight, rightBlackHeight;

    // Recursively check left and right subtrees
    int leftValid = checkRedblackTree(root->left, &leftBlackHeight);
    int rightValid = checkRedblackTree(root->right, &rightBlackHeight);

    // No two adjacent red nodes
    if ((root->color == 'R' && (root->left && root->left->color == 'R')) ||
        (root->color == 'R' && (root->right && root->right->color == 'R'))) {
        return 0;
    }

    // checking if Every path from a node to its descendant NULL nodes has the same number of black nodes
    if (leftValid && rightValid && leftBlackHeight == rightBlackHeight) {
        // Updating the black height
        *blackHeight = leftBlackHeight + (root->color == 'B' ? 1 : 0);
        return 1;
    }

    // If any of the properties are not satisfied, return 0
    return 0;
}


int main()
{
    //char s[] = "(10 B (4 B (2 R ()())(5 R ()()))(15 B ()()))" ;
    char s[100];
    fgets(s, sizeof(s), stdin);
    //char s[] = "(15 B (8 B (4 R ()())())(34 B (27 R (22 B ()())())(63 B ())()))";
    node root = NULL;
    int index = 0;
    int length = strlen(s);
    root = construct_Tree(s,&index,length);
    root = root->left;
    //preorder(root);
    int blackheight = 0;
    printf("%d",checkRedblackTree(root,&blackheight));

    return 0; 
}
