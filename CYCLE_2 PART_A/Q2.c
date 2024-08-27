#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct avl{
    int data;
    int value;
    int height;
    struct avl *left;
    struct avl *right;
};

typedef struct avl *node;

node createNode(int key , int value) 
{
    node temp; // declare a node
    temp = (node ) malloc (sizeof(struct avl));
    // allocate memory using malloc()
    if(temp == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }

    temp->data = key;
    temp->value = value;
    temp->right = NULL;  // make right and left point to null
    temp->left = NULL;
    temp->height = 1; //every node is inserted as leaf node
    return temp; //return the new node
}

int cal_height(node root)
{
    if (root == NULL)
        return 0;
    else 
    {
        int left = cal_height(root->left);
        int right = cal_height(root->right);
        if (left > right)
            return (left + 1);
        else
            return (right + 1);
    }
}

int max(int a, int b)
{
    return (a>b)?a:b;
}

node right_rotate(node y)
{
    node x = y->left;
    node t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = cal_height(y);
    x->height = cal_height(x);

    return x;
}

node left_rotate(node x)
{
    node y = x->right;
    node t2 = y->left;

    y->left = x;
    x->right = t2;

    y->height = cal_height(y);
    x->height = cal_height(x);

    return y;
}

int cal_balanceFactor(node temp)
{
    if(temp==NULL)
        return 0;
    return cal_height(temp->right) - cal_height(temp->left);
}

node insert(node root, int key, int value)
{
    if(root == NULL) {
        return createNode(key,value);
    }

    if(key < root->data) {
        root->left = insert(root->left, key,value);
    }
    else if(key > root->data) {
        root->right = insert(root->right, key, value);
    }
    else if(key == root->data) {
        root->value = value;
        return root;
    }

    root->height = cal_height(root);
    int balance = cal_balanceFactor(root);
    if(balance >= 2 || balance <= -2)
    {
        node z = root->right;
        node y = root->left;
        int bf_z = cal_balanceFactor(z);
        int bf_y = cal_balanceFactor(y);

        if(bf_z >= 0 && z!=NULL)
        {
            return left_rotate(root);
        }
        else if(bf_y <= 0 && y!=NULL)
        {
            return right_rotate(root);
        }
        else if(bf_z < 0 && z!=NULL)
        {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
        else if(bf_y > 0 && y!=NULL)
        {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
    }
    return root;
}

void inorder(node root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

int size(node root) {
    if (root == NULL)
        return 0;
    else
        return 1 + size(root->left) + size(root->right);
}

int tree_search(node root , int key)
{
    node temp = root;
    while(temp!=NULL)
    {
        if(temp->data < key)
            temp = temp->right;
        else if(temp->data > key)
            temp = temp->left;
        else if(temp->data == key)
        {
            printf("%d %d",temp->data , temp->value);
            return 1;
        }
    }
    return 0;
}

void lower_bound(node root , int key)
{
    int max_key ;
    int max_value ;

    int flag = 0;

    node temp = root;
    while(temp!=NULL)
    {
        if(temp->data >= key)
        {
            flag = 1;
            max_key = temp->data;
            max_value = temp->value;
            temp = temp->left;
        }
        else if(temp->data < key)
            temp = temp->right;
    }

    if(flag==0)
        printf("-1\n");
    else
        printf("%d %d\n",max_key,max_value);
    return;
}

int main()
{
    node root = NULL;

    char ans;

    /*MENU

    i -> insert 
    l -> lower bound
    f -> find
    s -> size
    e -> check if tree is empty
    p -> inorder
    t -> exit

    */

   scanf("%c" , &ans);
   while(ans!='t')
   {
    if (ans=='p')
    {
        inorder(root);
        printf("\n");
    }
    else if (ans=='i')
    {
        int key , value;
        scanf("%d %d",&key , &value);
        root = insert(root , key,value);
    }
    else if (ans=='l')
    {
        int key;
        scanf("%d",&key);
        lower_bound(root,key);
    }
    else if (ans=='f')
    {
        int key;
        scanf("%d",&key);
        int found = tree_search(root,key);
        if(found==0)
            printf("-1");
        printf("\n");
    }
    else if (ans=='s')
    {
        printf("%d\n",size(root));
    }
    else if (ans=='e')
    {
        if(root==NULL)
            printf("1\n");
        else
            printf("0\n");
    }
    scanf(" %c",&ans);
    }
    return 0; 
}
