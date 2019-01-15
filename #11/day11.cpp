#include <bits/stdc++.h>
#define N 301
using namespace std;

tuple<int, int, int, int> Solve(vector<vector<int>> matrix, int k)
{
    int topLeftCornerX, topLeftCornerY, squareLength, sumMax = INT_MIN;
    vector<vector<int>> partialSum(N,vector<int>(N)) ;

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
        int sum = accumulate(partialSum[i].begin(), partialSum[i].begin() + k, 0);
        for (int j = 1; j < N-k+1; j++)
        {
            sum += partialSum[i][j+k-1] - partialSum[i][j-1];

            if (sum > sumMax)
            {
                topLeftCornerX = i;
                topLeftCornerY = j;
                squareLength = k;
                sumMax = sum;
            }
        }
    }
    return make_tuple( topLeftCornerX, topLeftCornerY, squareLength, sumMax);
}

int main()
{
    ifstream cin("in.txt");
    //ofstream cout("out.txt");
    
    vector<vector<int>> matrix(N,vector<int>(N)) ;

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
    auto largest3x3Square =  Solve(matrix, 3);
    cout << "Part1: " << get<0>(largest3x3Square) << "," << get<1>(largest3x3Square) <<endl;

    ///Part2
    tuple<int, int, int, int> largestSquare;
    for(int k = 1; k < N; k++)
    {
        auto largestKxKSquare = Solve(matrix, k);
        if(get<3> (largestKxKSquare) > get<3>(largestSquare))
        {
            largestSquare = largestKxKSquare;
        }
    }
    cout << "Part2: " << get<0>(largestSquare) << "," << get<1>(largestSquare) << "," << get<2>(largestSquare);

    return 0;
}
