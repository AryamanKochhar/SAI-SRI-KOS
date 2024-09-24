#include <stdio.h>
#include <math.h>

void ToH(int n,char A,char B,char C)
{
    if(n==1)
    {
        printf("Move disk %d from %c to %c\n",n,A,B);
        return;
    }
    ToH(n-1,A,C,B);
    printf("Move disk %d from %c to %c\n",n,A,B);
    ToH(n-1,C,B,A);
}

int main()
{
    int n;
    scanf("%d",&n);
    int moves = pow(2,n) - 1;
    ToH(n,'A','C','B');
    printf("Total number of moves: %d\n",moves);
}