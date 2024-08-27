#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    temp->color = 'R';//every node is inserted as leaf node
    return temp; //return the new node
}

node insert(node root , node temp , int key)
{
    if(root==NULL)
        return temp;
    if(key<root->data)
    {
        node leftchild = insert(root->left ,temp, key);
        root->left = leftchild;
        leftchild->parent = root;
    }
    else if (key>root->data)
    {
        node rightchild = insert(root->right ,temp, key);
        root->right = rightchild;
        rightchild->parent = root;
    }
    return root;
}

node right_rotate(node y, node root)
{
    node x = y->left;
    y->left = x->right;
    if(x->right!=NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if(y->parent==NULL)
        root = x;
    else if(y == y->parent->right)
        y->parent->right = x;
    else y->parent->left = x;
    x->right = y;
    y->parent = x;
    return root;

}

node left_rotate(node x, node root)
{
    node y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else x->parent->left = y;
    y->left = x;
    x->parent = y;
    return root;
}


node rb_insert_fixup(node root , node z)
{
    while(z->parent!= NULL && z->parent->color == 'R' && z->parent->parent != NULL)
    {
        if(z->parent == z->parent->parent->left)
        {
            node y = z->parent->parent->right;
            char color;
            if(y==NULL)
                color = 'B';
            else
                color = y->color;
            if(color=='R') 
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else 
            {
                if(z == z->parent->right)
                {
                    z = z->parent;
                    root = left_rotate(z,root);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                root=right_rotate(z->parent->parent,root);
            }
        }

        else
        {
            node y = z->parent->parent->left;
            char color;
            if(y==NULL)
                color = 'B';
            else
                color = y->color;

            if(color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else 
            {
                if(z==z->parent->left)
                {
                    z = z->parent;
                    root = right_rotate(z,root);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                root = left_rotate(z->parent->parent,root);
            }
        }
    }
    root->color = 'B';
    return root;
}

void preorder(node root)
{
    if(root!=NULL)
    {
        printf("%d %c ",root->data , root->color);
        preorder(root->left);
        preorder(root->right);
    }
}

void printParenthesizedRepresentation(node root) {
    if (root == NULL) {
        printf("( ) ");
        return;
    }
    printf("(%d %c ", root->data, root->color);
    printParenthesizedRepresentation(root->left);
    printParenthesizedRepresentation(root->right);
    printf(") ");
}

int main() {
    node root = NULL;
    int num = 0;

    // Read input until 'e' is encountered
    while (1) {
        char ch;
        scanf("%c", &ch);
        if (ch == 'e')
            break;
        else if (ch != '\n') {
            int digit  = ch - '0';
            num  = num * 10 + digit;
        }
        else{
            node temp = createNode(num);
            root = insert(root , temp, num);
            root = rb_insert_fixup(root , temp);
            printParenthesizedRepresentation(root);
            printf("\n");
            num = 0;
        }
    }

    return 0;
}