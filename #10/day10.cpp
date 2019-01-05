#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x = 0, y = 0, v1 = 0, v2 = 0;
};
vector <Point> points;

void Read()
{
    string inputLine;
    while(getline(cin, inputLine))
    {
        Point point;
        int i, j;
        i = inputLine.find('<');
        j = inputLine.find(',');
        inputLine[i] = inputLine[j] =  '.';
        point.x = stoi(inputLine.substr(i+1, j-i));

        i = j;
        j = inputLine.find('>');
        inputLine[j] =  '.';
        point.y = stoi(inputLine.substr(i+1, j-i));

        i = inputLine.find('<');
        j = inputLine.find(',');
        point.v1 = stoi(inputLine.substr(i+1, j-i));

        i = j;
        j = inputLine.find('>');
        point.v2 = stoi(inputLine.substr(i+1, j-i));

        points.push_back(point);
    }
}

void printMessage(int xMin, int xMax, int yMin, int yMax, int seconds)
{
    for( int j = yMin; j <= yMax; j++ )
    {
        for(int i = xMin; i <= xMax; i++)
        {
            find_if(points.begin(), points.end(), [&](Point point)
            {
                return point.x + seconds * point.v1 == i && point.y + seconds * point.v2 == j;
            }) != points.end() ? cout << "#" : cout << ".";
        }
        cout << endl;
    }
}

void Solve()
{
    int SECONDS, YMIN, YMAX, XMIN, XMAX,  minDistance = INT_MAX;

    for(int seconds = 0; seconds <= 50000; seconds++)
    {
        int xMin = INT_MAX, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;

        for(auto &k: points)
        {
            xMax = max(k.x + seconds * k.v1, xMax);
            xMin = min(k.x + seconds * k.v1, xMin);
            yMax = max(k.y + seconds * k.v2, yMax);
            yMin = min(k.y + seconds * k.v2, yMin);
        }

        if(xMax - xMin < minDistance)
        {
            minDistance = xMax - xMin;
            SECONDS = seconds;
            YMAX = yMax;
            YMIN = yMin;
            XMIN = xMin;
            XMAX = xMax;
        }
    }

    cout << SECONDS << " seconds\n";
    printMessage(XMIN, XMAX, YMIN, YMAX, SECONDS);
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    Read();
    Solve();

    return 0;
}
