#include <stdio.h>
#include <string.h>
// int stack_empty(char stack[] , int top)
// {
//     if(top==-1)
//         return -1;
//     else
//         return 1;
// }
// int stack_full(char stack[] , int top , int size)
// {
//     if(top==size-1)
//         return -1;
//     else
//         return 1;
// }
// int pop(char stack[] , int *top)
// {
//     //int check = stack_empty(stack , top);
//     //if (check==-1)
//     //{    //printf("-1\n");
//         //return -1;
//     //}
//     {
//         //printf("%c\n" , stack[*top]);
//         *top = *top - 1;
//         return stack[*top+1];
//     }
// }
// int push(char stack[] , int top , int size, char data)
// {
//     int check = stack_full(stack,top,size);
//     if(check == -1)
//     {
//         printf("-1\n");
//         return top;
//     }
//     else
//     {
//         top = top+1;
//         stack[top] = data;
//         return top;
//     }
// }
// void display(char stack[] , int top)
// {
//     for (int i =0 ;i<=top;i++)
//         printf("%c", stack[i]);
// }
// void duplicate_parenthesis(char exp[] , int size)
// {
//     char stack[100];
//     int top = -1;
//     //int check=0;
//     for(int i=0;i<size;i++)
//     {
//         if(exp[i]!= ')')
//             top = push(stack,top,size,exp[i]);
//         else
//         {
//             char buffer[100];
//             int btop = -1;
//             while(pop(stack,&top)!='(')
//                 push(buffer,&btop,100,pop(stack,&top));
//             int flag=0;
//             while(btop!=-1)
//             {
//                 char a = pop(buffer,&btop);
//                 if( a =='+'|| a=='-' || a=='%'|| a=='/' || a=='*')
//                 {
//                     //operator is present
//                     //valid parenthesis
//                     btop = -1;
//                     flag = 1;
//                     break;
//                 }
//             }
//             if(flag==0)
//             {
//                 printf("1");
//                 return;
//             }
//         }
//     }
//     printf("0");
//     return;
// }
int main()
{
    char exp[1000];
    int size;
    scanf("%d",&size);
    scanf("%s",exp);
    //printf("%s\n",exp);
    // duplicate_parenthesis(exp,size);
    int no_of_parenthesis = 0 ;
    int no_of_operators = 0;
    for(int i = 0;i<size;i++)
    {
        if(exp[i]=='(')
            no_of_parenthesis++;
        else if(exp[i]=='+' || exp[i]=='*' || exp[i]=='/'||exp[i]=='-'||exp[i]=='%')
            no_of_operators++;
        else
            continue;
    }
    if(no_of_operators>=no_of_parenthesis)
        printf("0");
    else
        printf("1");
}
