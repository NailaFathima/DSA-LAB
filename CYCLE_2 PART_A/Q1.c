#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int right_rotation = 0;
int left_rotation = 0;

// node to root
int j = 0;
int arr[100];

struct avl{
    int data;
    int height;
    struct avl *left;
    struct avl *right;
};

typedef struct avl *node;

node createNode(int key) 
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

node insert(node root, int key)
{
    if(root == NULL) {
        //printf("Inserting node with key: %d\n", key);
        return createNode(key);
    }
    
    //printf("Checking node with key: %d\n", root->data);

    if(key < root->data) {
        //printf("Going left\n");
        root->left = insert(root->left, key);
    }
    else if(key > root->data) {
        //printf("Going right\n");
        root->right = insert(root->right, key);
    }
    else {
        //printf("Key already exists\n");
        return root;
    }

    root->height = cal_height(root);

    //printf("Updating height of node with key: %d, new height: %d\n", root->data, root->height);

    int balance = cal_balanceFactor(root);

    //printf("Balance factor of node with key %d: %d\n", root->data, balance);

    if(balance >= 2 || balance <= -2)
    {
        node z = root->right;
        node y = root->left;
        int bf_z = cal_balanceFactor(z);
        int bf_y = cal_balanceFactor(y);

        if(bf_z >= 0 && z!=NULL)
        {
            //printf("Performing left rotation at node with key: %d\n", root->data);
            left_rotation++;
            return left_rotate(root);
        }
        else if(bf_y <= 0 && y!=NULL)
        {
            //printf("Performing right rotation at node with key: %d\n", root->data);
            right_rotation++;
            return right_rotate(root);
        }
        else if(bf_z < 0 && z!=NULL)
        {
            //printf("Performing right rotation followed by left rotation at node with key: %d\n", root->data);
            root->right = right_rotate(root->right);
            right_rotation++;
            left_rotation++;

            return left_rotate(root);
        }
        else if(bf_y > 0 && y!=NULL)
        {
            //printf("Performing left rotation followed by right rotation at node with key: %d\n", root->data);
            root->left = left_rotate(root->left);
            right_rotation++;
            left_rotation++;
            return right_rotate(root);
        }
    }
    
    return root;
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
            return 1;
        }
    }
    return 0;
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
    node root = NULL;

    char ans;

    /*MENU

    i -> insert 
    x -> search
    p -> preorder
    s -> left and right rotations
    e -> exit

    */

   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='p')
    {
        preorder(root);
        printf("\n");
    }
    else if (ans=='s')
    {
        printf("%d %d\n",left_rotation,right_rotation);
    }
    else if (ans=='i')
    {
        int key;
        scanf("%d",&key);
        root = insert(root , key);
    }
    else if (ans=='x')
    {
        int key;
        scanf("%d",&key);
        int found = tree_search(root , key);
        if(found==0)
        {
            printf("-1");
        }
        else
        {
            int dummy;
            dummy = getPath(root,key);    
            for(int i = 0;i<j;i++)
                printf("%d ",arr[i]);
        }
        printf("\n");
    }
    scanf(" %c",&ans);
    }
    return 0; 
}