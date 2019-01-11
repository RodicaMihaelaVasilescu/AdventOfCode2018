#include <bits/stdc++.h>

using namespace std;

struct Point
{
    long x, y, z, r;
};
vector <Point> points;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    Point Max;
    Max.r = INT_MIN;
    string coordinates, radius;

    while(cin >> coordinates >> radius)
    {
        Point point;

        int i, j;

        i = coordinates.find('<');
        j = coordinates.find(',');
        point.x = stoi(coordinates.substr(i+1,j-i));


        i = j;
        j = coordinates.find(',', j+1);
        point.y = stoi(coordinates.substr(i+1,j-i));

        i = j;
        j = coordinates.find(',', j+1);
        point.z = stoi(coordinates.substr(i+1,j-i));

        point.r = stoi(radius.substr(2, radius.size() - 2));

        points.push_back(point);

        if(point.r > Max.r)
        {
            Max.r = point.r;
            Max.x = point.x;
            Max.y = point.y;
            Max.z = point.z;
        }
    }

    cout << count_if (points.begin(),points.end(), [&](Point p)
    {
        return abs(p.x - Max.x) + abs(p.y - Max.y) + abs(p.z - Max.z) <= Max.r;
    });

    return 0;
}
