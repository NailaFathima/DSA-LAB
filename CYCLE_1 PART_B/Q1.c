#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tree{
 int data;
 struct Tree *right;
 struct Tree *left;
};

typedef struct Tree *node;

int ans1[100];

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

void printArray(int arr[])
{
    for(int i = 0;i<=(sizeof(arr)/sizeof(arr[0]));i++)
        printf("%d ",arr[i]);
}

int max(int a, int b) {
    return (a > b) ? a : b;
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

int search(int inorder[] , int start , int end , int curr)
{
    for(int i = start;i<=end;i++){
        if(inorder[i]==curr){
            return i;
        }
    }
    return -1;
}

node buildTree (int preorder[] , int inorder[] , int start , int end) //to build tree from preorder and inorder traversals given
{
    static int index = 0;
    if(start>end){
        return NULL;
    }

    int curr = preorder[index];
    index++;
    node temp = createNode(curr);
    if(start==end){
        return temp;
    }

    int pos = search(inorder, start, end, curr);
    temp->left = buildTree(preorder , inorder, start, pos-1);
    temp->right = buildTree(preorder, inorder , pos+1 , end);

    return temp;
}

int calcHeight(node root)  // function to calculate height of the tree
{
    if(root==NULL)
    {
        return 0;
    }
    int lheight = calcHeight(root->left);
    int rheight = calcHeight(root->right);
    return max(lheight,rheight) + 1;
}

int calcDiameter(node root) //function to calculate diameter of the tree
{
    if(root==NULL)
    {
        return 0;
    }

    int leftheight = calcHeight(root->left);
    int rightheight = calcHeight(root->right);
    int currentDiamter = leftheight + rightheight +1;

    int leftDiameter = calcDiameter(root->left);
    int rightDiamter = calcDiameter(root->right);

    return max(currentDiamter , max(leftDiameter,rightDiamter));
}

void leftLeavesSum(node root , int isLeft , int *sum)  //Prints the sum of the values of left leaf nodes.
{
    if(root==NULL)
    {
        return;
    }

    if(root->left==NULL && root->right==NULL && isLeft)
    {
        *sum = *sum + root->data;
    }

    leftLeavesSum(root->left , 1 , sum);
    leftLeavesSum(root->right , 0 , sum);
}

void traversal(node root , int level , int *index)
{
    if(root==NULL)
        return;
    if(level<(sizeof(ans1)/sizeof(ans1[0])))
    {
        if(root->data > ans1[level])
            ans1[level] = root->data;
        else
        {
            ans1[*index] = root->data;
            *index = *index + 1;
        }
        traversal(root->left,level+1,index);
        traversal(root->right,level+1,index);
    }
}

void Level(node root, int level, int l)
{
    if (root == NULL)
        return;
    if (level == 1)
        //cout << root->data << " ";
        printf("%d ",root->data);
else if (level > 1) 
    {
        if (l)
        {
            Level(root->left,level - 1, l);
            Level(root->right,level - 1, l);
        }
        else 
        {
            Level(root->right,level - 1, l);
            Level(root->left,level - 1, l);
        }
    }
}

int height(node root)
{
    if (root == NULL)
        return 0;
    else 
    {
        int left = height(root->left);
        int right = height(root->right);
        if (left > right)
            return (left + 1);
        else
            return (right + 1);
    }
}

void zigzag(node root)
{
    int h = height(root);
    int i;
    int ltr = 1;
    for(i = 1; i <= h; i++)
    {
        Level(root, i, ltr);
        //ltr = !ltr;

        ltr = (ltr) ? 0 : 1;
    }
}

int main()
{
    int size;
    scanf("%d",&size);

    int preorder[size];
    int inorder[size];

    for(int i = 0;i<size;i++)
        scanf("%d",&inorder[i]);
    for(int i = 0;i<size;i++)
        scanf("%d",&preorder[i]);

    node root = NULL;
    root = buildTree(preorder,inorder,0,size-1);
    // printf("//////////////////");
    // printf("\n");
    // postorder(root);
    // printf("\n");
    // printf("%d",calcHeight(root));
    // printf("\n");
    // printf("%d",calcDiameter(root));
    // printf("\n");
    // int sum = 0;
    // leftLeavesSum(root , 0 , &sum);
    // printf("sum = %d",sum);
    // printf("\n");
    // int index = 0;
    // traversal(root,0,&index);
    // printArray(ans);
    // printf("\n");
    // zigzag(root);

    char ans;

    /*MENU

    p -> prints the postorder traversal of tree
    z -> prints the zigzag traversal of tree
    m -> prints the max element at each level
    d -> prints the diameter of tree
    s -> prints the sum of left leaf nodes
    e -> exit

    */

   scanf("%c" , &ans);
   while(ans!='e')
   {
    if (ans=='p')
    {
        postorder(root);
        printf("\n");
    }
    else if (ans=='z')
    {
        zigzag(root);
        printf("\n");
    }
    else if (ans=='m')
    {
        traversal(root,0,&index);
        printArray(ans1);
        printf("\n");
    }
    else if (ans=='d')
    {
        printf("%d",calcDiameter(root));
        printf("\n");
    }
    else if (ans=='s')
    {
        int sum = 0;
        leftLeavesSum(root , 0 , &sum);
        printf("%d",sum);
        printf("\n");
    }
    scanf("%c",&ans);
    }
    return 0; 

}



