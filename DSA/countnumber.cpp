// brute force approach
// #include <iostream>
// using namespace std;
// int main(){
//     int x;
//     cout<<"enter a number : ";
//     cin>>x;
//     int temp=x;
//     int count=0;
//     while(temp!=0){
//         temp=temp/10;
//         count=count+1;
//     }
//     cout<<"the number of digits are "<<count<<endl;
//     return 0;
// }  
//optimal approach
//use logarithms
#include <iostream>
#include <cmath>
using namespace std;
int countDigits(int n){
    int cnt=(int)(log10(n)+1);
    return cnt;
}
int main(){
    int n;
    cin>>n;
    cout<<countDigits(n)<<endl;
    return 0;
}