#include  <iostream>
using namespace std;
int main(){ 
    // FIRST PATTERN (RECTANGLE)
    // for(int i=0;i<5;i++){
    //     for(int j=0;j<5;j++){
    //         cout<<"*";
    //     }
    // cout<<endl;
    // }
    // SECOND PATTERN (TRIANGLE)
    //  for(int i=0;i<5;i++){
    //      for(int j=0;j<i+1;j++){
    //          cout<<"*";
    //      }
    //  cout<<endl;
    // THIRD PATTERN
    // for(int i=0;i<5;i++){
    //       for(int j=1;j<i+2;j++){
    //           cout<<j;
    //       }
    //   cout<<endl;
    // fourth pattern
    // for(int i=1;i<6;i++){
    //       for(int j=1;j<i+1;j++){
    //           cout<<i;
    //       }
    //   cout<<endl;
    // learning in for loops the end point is a condition not the endit will run the loop only if the condition is true or not
    // for(int i=1;i<=4;i++){
    //     for(int j=1;j<=4;j++){
    //         if(i==1|| i==4){
    //             cout<<"*";
                
    //         }
    //         else
    //             if(j==1||j==4){
    //                 cout<<"*";
    //             }
    //             else{
    //                 cout<<" ";
    //             }
    //     }
    //     cout<<endl;
    // } 
    // PYRAMID PATTERN
    // for(int=1;i<=n;i++){
    //     for(int j=1;j<=2*n;j++){
    //         if ())
    //         {
    //             /* code */
    //         }
            
    //     }
    // }
for(int i=1;i<=5;i++){
    for(int j=1;j<=9;j++){
        if (i+j<6 || j-i>4)
        {
            cout<<" ";
        }
        else{
            cout<<"*";
        }
        
    }
    cout<<endl; 
for(int i=1;i<=10;i++){
    if (i<=5){
        for(int j=1;j<=9;j++){
            if (i+j<6 || j-i>4)
        {
            cout<<" ";
        }
        else{
            cout<<"*";
        }
    }
    if (i>5)
    {
        for(int j=1;j<=9;j++){
            if (i+j>15 || i-j<)
            {
            
            }
            else{
                cout<<"*";
            }
            
    }
    

    }
    cout<<endl; 
}
return 0;
}
