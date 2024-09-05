
#include<bits/stdc++.h>
#include<vector>
using namespace std;

void rotateMatrix(vector<vector<int>>& matrix) 
    {
        int n = matrix.size();
        vector<vector<int>> temp(n, vector<int>(n));
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                temp[i][j]=matrix[j][3-i];
            }
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                printf("%d",temp[i][j]);
            }
        }


    }
    int main()
    {
        vector<vector<int>> matrix= {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        rotateMatrix(matrix);
        printf("hello");
        return 0;
    }