#include <iostream>
#include <cmath> // use <cmath> instead of <math.h> for C++
using namespace std;

int main(){
    int n;
    cin >> n;
    int temp = n;
    int rev = 0;
    int count = 0;

    while(temp != 0){
        int digit = temp % 10; // Get the last digit
        rev += digit * pow(10, (int)log10(n) - count); // Calculate the position and add digit accordingly
        temp /= 10; // Remove the last digit from temp
        count++;
    }
    
    cout << "The reversed digits are " << rev << endl;
    return 0;
}

//difference between count++ and count+=1  is 
//
//
//
