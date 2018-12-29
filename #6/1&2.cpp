#include <bits/stdc++.h>
#define INFINITE 99999999
using namespace std;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    vector<pair<int, int>> input;
    string X, Y;
    int n, m;
    while(cin >> X >> Y)
    {
        int x = stoi(X), y = stoi(Y);
        input.push_back(make_pair(x, y));
        n = max(x+1, n);
        m = max(y+1, m);
    }

    vector <vector <int>> minimumManhattanDistance(n+1, vector<int>(m+1, INFINITE));
    vector <vector <int>> indexMatrix(n+1, vector<int>(m+1));

    int index = 0;
    set <int> indexes;

    for(auto coordinates: input){

        indexes.insert(++index);

        int x = coordinates.first, y = coordinates.second;

        for(int i = 0; i < n; i++)
        {
             for(int j= 0 ; j < m; j++)
            {
                if(abs(x-j) + abs(y-i) < minimumManhattanDistance[i][j] )
                {
                    minimumManhattanDistance[i][j] = abs(x-j) + abs(y-i);
                    indexMatrix[i][j] = index;
                }
                else if(minimumManhattanDistance[i][j] == abs(x-j) + abs(y-i) )
                {
                    indexMatrix[i][j] = 0;
                }
            }
        }
    }

    for(int i = 0; i < max(n, m); i++)
    {
        if(i < n)
        {
            indexes.erase(indexMatrix[i][0]);
            indexes.erase(indexMatrix[i][m]);
        }

        if(i < m)
        {
            indexes.erase(indexMatrix[0][i]);
            indexes.erase(indexMatrix[n][i]);
        }
    }

    /// Part 1
    int maxIndexFrequency = 0;
    for(auto &index: indexes)
    {
        int indexFrequency = 0;
        for(int i = 0; i <= n; i++)
            for(int j = 0 ; j <= m; j++)
                if(indexMatrix[i][j] == index)
                    indexFrequency++;
        maxIndexFrequency = max(indexFrequency, maxIndexFrequency);
    }
    cout << maxIndexFrequency<<endl;

    /// Part 2
    int regionSize = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0 ; j < m; j++)
        {
            int nr = 0;
            for(auto &coordinate: input)
                nr += abs(j-coordinate.first) + abs(i - coordinate.second);

            nr >= 10000 ? : regionSize++;
        }
    }
    cout << regionSize;

    return 0;

}
