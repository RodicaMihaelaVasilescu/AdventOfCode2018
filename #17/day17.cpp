#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
};

vector<Point> points;
char matrix[2000][2000];

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int xMin, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;

    string inputLine;
    while(getline(cin, inputLine))
    {
        Point point;

        int i, j;
        i = inputLine.find('=');
        j = inputLine.find(',');
        inputLine[i] = inputLine[j] =  'x';

        if(inputLine[0] == 'x')
        {
            point.x1 = stoi(inputLine.substr(i+1, j-i));
        }
        else
        {
            point.y1 = stoi(inputLine.substr(i+1, j-i));
        }

        i = inputLine.find('=');
        j = inputLine.find('.');
        inputLine[i] = inputLine[j] =  'x';

        if(inputLine[i-1] == 'x')
        {
            point.x1 = stoi(inputLine.substr(i+1, j-i));
            point.x2 = stoi(inputLine.substr(j+2, inputLine.size()-j - 2));
        }
        else
        {
            point.y1 = stoi(inputLine.substr(i+1, j-i));
            point.y2 = stoi(inputLine.substr(j+2, inputLine.size()-j - 2));
        }

        point.x2 == 0 ? point.x2 = point.x1 : 0;
        point.y2 == 0 ? point.y2 = point.y1 : 0;

        swap(point.x1, point.y1);
        swap(point.x2, point.y2);

        xMax = max(point.x2, xMax);
        yMin = min(point.y1, yMin);
        yMax = max(point.y2, yMax);

        points.push_back(point);

    }

    xMin = 0;
    yMin--;
    yMax++;
    xMax++;

    for(int i = xMin; i <= xMax; i++)
        for(int j = yMin ; j <= yMax; j++)
            matrix[i][j] = '.';

    for(auto &point: points )
        for(int i = point.x1; i <= point.x2; i++)
            for(int j = point.y1; j <= point.y2; j++ )
                matrix[i][j] = '#';

    queue <pair<int, int>> ramificari;
    ramificari.push(make_pair(0, 500));

    while(!ramificari.empty())
    {
        int x = get<0>(ramificari.front());
        int y = get<1>(ramificari.front());
        ramificari.pop();

        if(matrix[x][y] != '.')
            continue;

        while(matrix[x][y] != '#' && x <= xMax  )
        {
            if(matrix[x][y]=='.')
            {
                matrix[x][y] = '|';
            }
            x++;
        }

        if( x == xMax )
        {
            continue;
        }

        int leftColumn = y, rightColumn = y;

        while(matrix[x][leftColumn] == '#')
            leftColumn--;

        while(matrix[x][rightColumn] == '#')
            rightColumn++;

        x--;
        leftColumn++;
        rightColumn--;

        int topRowLeft = x, topRowRight = x;

        while(matrix[topRowLeft][leftColumn] == '#')
            topRowLeft--;

        while(matrix[topRowRight][rightColumn] == '#')
            topRowRight--;

        bool isThereClayBetweenLimits = true;
        int rowLimit;

        for(int i = leftColumn+1; i <= rightColumn-1; i++)
        {
            if(matrix[topRowRight-1][i] =='#')
            {
                isThereClayBetweenLimits = false;
                break;
            }
        }

        if(topRowLeft >= topRowRight && isThereClayBetweenLimits)
            ramificari.push(make_pair(topRowLeft, leftColumn-1));

        if(topRowRight >= topRowLeft && isThereClayBetweenLimits)
            ramificari.push(make_pair(topRowRight, rightColumn+1));

        if(!isThereClayBetweenLimits)
        {
            if(abs(leftColumn - y) < abs(rightColumn - y))
            {
                ramificari.push(make_pair(topRowLeft, leftColumn-1));
                rowLimit = topRowLeft;
            }
            else
            {
                ramificari.push(make_pair(topRowRight, rightColumn+1));
                rowLimit = topRowRight;
            }
        }
        else
            rowLimit = max(topRowLeft, topRowRight);

        while( x != rowLimit )
        {
            int leftColumn2 = y, rightColumn2 = y;
            for( ; matrix[x][leftColumn2] !='#' && leftColumn2 != leftColumn; leftColumn2--)
            {
                matrix[x][leftColumn2] ='~';
                if(matrix[x+1][leftColumn2] == '.')
                    ramificari.push(make_pair(x+1, leftColumn2));

            }
            for( ; matrix[x][rightColumn2] !='#' && rightColumn2 != rightColumn; rightColumn2++)
            {
                matrix[x][rightColumn2] ='~';
                if(matrix[x+1][rightColumn2] == '.')
                    ramificari.push(make_pair(x+1, rightColumn2));
            }
            x--;
            if(x == rowLimit)
            {
                for(int i = y; i <= rightColumn &&  matrix[x][i]!= '#'; i++)
                    if(matrix[x][i]!='~')
                        matrix[x][i] = '|';
                for(int i = y; i >= leftColumn &&  matrix[x][i]!= '#'; i--)
                    if(matrix[x][i]!='~')
                        matrix[x][i] = '|';
            }
        }
    }

    if(ramificari.empty())
    {
        int Sum1 = 0, Sum2 = 0;
        for(int i = xMin+4; i <= xMax-1; i++)
            for(int j = yMin ; j <= yMax; j++)
                matrix[i][j] == '~' ? Sum1++ : matrix[i][j] == '|' ? Sum2++ : 0;

        cout << "Part1: " << Sum1 + Sum2 << endl;
        cout << "Part2: " << Sum1 ;
    }

    return 0;
}
