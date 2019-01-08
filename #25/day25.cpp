#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int id, a = 0, b = 0, c = 0, d = 0;
};

int graph[1500][1500], visited[1500];
vector<Point> points;

void dfs(int startNode, int indexConnectedComponent)
{
    visited[startNode] = indexConnectedComponent;

     for_each(points.begin(), points.end(), [&](Point p)
    {
        if ( graph[startNode][p.id] == 1 && visited[p.id] == 0)
        {
            dfs(p.id, indexConnectedComponent);
        }
    });
}
int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string inputLine;
    int id = 0;

    while(cin >> inputLine)
    {
        Point x;
        x.id = id++;

        int i, j;
        i = inputLine.find(',');
        x.a = stoi(inputLine.substr(0,i));

        j = inputLine.find(',',i+1);
        x.b = stoi(inputLine.substr(i+1, j-i));

        i = j;
        j = inputLine.find(',',i+1);
        x.c = stoi(inputLine.substr(i+1, j-i));

        x.d = stoi(inputLine.substr(j+1, inputLine.size() - j));

        points.push_back(x);
    }

    for(auto &p1: points)
    {
        for(auto &p2: points)
        {
            if(abs(p2.a - p1.a) + abs(p2.b - p1.b) + abs(p2.c - p1.c) + abs(p2.d - p1.d) <= 3 && p1.id != p2.id)
            {
                graph[p1.id][p2.id] = graph[p2.id][p1.id] = 1;
            }
        }
    }

    int noOfConnectedComponents = 0;

    for_each(points.begin(), points.end(), [&](Point p)
    {
        if(visited[p.id] == 0)
        {
            noOfConnectedComponents++;
            dfs(p.id, noOfConnectedComponents);
        }
    });

    cout << noOfConnectedComponents << endl;
    return 0;
}
