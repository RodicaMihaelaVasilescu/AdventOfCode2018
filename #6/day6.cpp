#include <bits/stdc++.h>
#define INFINITE 99999999
using namespace std;

int n, m;

vector<pair<int, int>> ReadInput()
{
    vector<pair<int, int>> input;
    string x;
    int y;
    while(cin >> x >> y)
    {
        input.push_back(make_pair(stoi(x), y));
        n = max(stoi(x)+1, n);
        m = max(y+1, m);
    }
    return input;
}

int Part1(vector<pair<int, int>> input)
{
    vector <vector <int>> minimumManhattanDistance(n+1, vector<int>(m+1, INFINITE));
    vector <vector <int>> indexMatrix(n+1, vector<int>(m+1));

    int index = 0;
    set <int> indexes;
    for_each(input.begin(), input.end(), [&](pair<int, int> coordinates)
    {
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
    });

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

    int IndexWithMaxFrequency = 0;
    for_each(indexes.begin(), indexes.end(), [&](int index)
    {
        int indexFrequency = 0;
        for(int i = 0; i <= n; i++)
            for(int j = 0 ; j <= m; j++)
                if(indexMatrix[i][j] == index)
                    indexFrequency++;
        IndexWithMaxFrequency = max(indexFrequency, IndexWithMaxFrequency);
    });

    return IndexWithMaxFrequency;
}

int Part2 (vector<pair<int, int>> input)
{
    int regionSize = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0 ; j < m; j++)
        {
            accumulate(input.begin(), input.end(),0, [&](int sum, pair<int, int> coordinate)
            {
                return sum + abs(j-coordinate.first) + abs(i - coordinate.second);
            }) >= 10000 ? : regionSize++;
        }
    }
    return regionSize;
}
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    auto input = ReadInput();
    cout << "Part1: " << Part1(input) << endl;
    cout << "Part2: " << Part2(input) << endl;

    return 0;
}
