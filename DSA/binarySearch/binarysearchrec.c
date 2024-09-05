#include <stdio.h>
int binarysearch(int array[],int x,int high,int low){
    if(high>=low){
        int mid=(high+low)/2;
        if(array[mid]==x){
            return mid;
        }
        if(array[mid]>x){
            binarysearch(array,x,mid-1,low);
        }
        if(array[mid]<x){
            binarysearch(array,x,high,mid+1);
        }
    }
return -1;
}
int main(){
    int arra[]={1,2,3,4,5,6,7,8,9};
    int x;
    printf("enter the element you want to find");
    scanf("%d",&x);
    int n=sizeof(arra)/sizeof(arra[1]);
    int result=binarysearch(arra,x,n-1,0);
    if(result==-1){
        printf("the element is NOT  there in the array");
    }
    return 0;
}