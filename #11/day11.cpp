#include <bits/stdc++.h>
#define N 301
using namespace std;

int  topLeftCornerX, topLeftCornerY, squareLength, sumMax = INT_MIN;

void Solve(int matrix[N][N], int k)
{
    int partialSum[N][N];

    for (int j = 0; j < N; j++)
    {
        int sum = 0;
        for (int i = 0; i < k; i++)
        {
            sum += matrix[i][j];
        }

        for (int i = 1; i < N - k + 1; i++)
        {
            sum += matrix[i+k-1][j] - matrix[i-1][j];
            partialSum[i][j] = sum;
        }
    }

    for (int i = 0; i < N - k + 1; i++)
    {
        int sum = accumulate(partialSum[i], partialSum[i] + k, 0);
        for (int j = 1; j < N-k+1; j++)
        {
            sum += partialSum[i][j+k-1] - partialSum[i][j-1];

            if (sum > sumMax)
            {
                sumMax = sum;
                topLeftCornerX = i;
                topLeftCornerY = j;
                squareLength = k;
            }
        }
    }
}

int main()
{
    ifstream cin("in.txt");
    ofstream cout ("out.txt");
    int matrix[N][N];

    int input;
    cin >> input;

    for(int  i = 1; i < N; i++)
    {
        for(int j = 1; j < N; j++)
        {
            matrix[i][j] = (((i+10)*j + input)*(i+10))/100%10-5;
        }
    }

    ///Part1
    Solve(matrix, 3);
    cout << "Part1: " << topLeftCornerX << "," << topLeftCornerY <<endl;

    ///Part2
    sumMax = INT_MIN;
    for(int k = 1; k < N; k++)
    {
        Solve(matrix, k);
    }
    cout << "Part2: " << topLeftCornerX << "," << topLeftCornerY << "," << squareLength;

    return 0;
}
