#include <bits/stdc++.h>
using namespace std;

int N, M;

struct Rectangle
{
    int id, leftPadding, topPadding, width, height;
};

vector<Rectangle> ReadInput()
{
    vector<Rectangle> input;
    string idStr, padding, length, ignoreString;
    while(cin >> idStr >> ignoreString >> padding >> length)
    {
        Rectangle rectangle;

        rectangle.id = stoi(idStr.substr(1));
        int pos = padding.find(',');
        rectangle.leftPadding = stoi(padding.substr(0, pos));
        rectangle.topPadding = stoi(padding.substr(pos+1, padding.size()- pos -1));
        pos = length.find('x');
        rectangle.width = stoi(length.substr(0, pos));
        rectangle.height = stoi(length.substr(pos+1, length.size()-pos));

        M = max(M, rectangle.width + rectangle.leftPadding);
        input.push_back(rectangle);
    }
    N = input.size();

    return input;
}

int Part1(vector<Rectangle> input)
{
    vector <vector<char>> fabric(N, vector<char>(M));
    int squaresOfFabricWithinMoreClaims = 0;

    for_each(input.begin(), input.end(), [&](Rectangle rectangle )
    {
        for (int i = rectangle.leftPadding; i < rectangle.width + rectangle.leftPadding; i++)
        {
            for (int j = rectangle.topPadding; j < rectangle.height + rectangle.topPadding; j++)
            {
                if (fabric[i][j] == 0)
                {
                    fabric[i][j] = 1;
                }
                else if(fabric[i][j] == 1)
                {
                    fabric[i][j] = 2;
                    squaresOfFabricWithinMoreClaims++;
                }
            }
        }
    });

    return squaresOfFabricWithinMoreClaims;
}

int Part2(vector<Rectangle> input)
{
    vector <vector<int>> fabric(N, vector<int>(M));
    set<int> IDsThatDoesNotOverlap;

    for_each(input.begin(), input.end(), [&](Rectangle rectangle )
    {
        bool doesOverlap = false;
        for (int i = rectangle.leftPadding; i < rectangle.width + rectangle.leftPadding; i++)
        {
            for (int j = rectangle.topPadding; j < rectangle.height + rectangle.topPadding; j++)
            {
                if (fabric[i][j] == 0)
                {
                    fabric[i][j] = rectangle.id;
                }
                else
                {
                    IDsThatDoesNotOverlap.erase(fabric[i][j]);
                    doesOverlap = true;
                }
            }
        }

        if(!doesOverlap)
        {
            IDsThatDoesNotOverlap.insert(rectangle.id);
        }
    });

    return *IDsThatDoesNotOverlap.begin();

}
int main()
{
    freopen ("in.txt", "r", stdin);
    freopen ("out.txt", "w", stdout);

    vector<Rectangle> input = ReadInput();
    cout << "Part1: " << Part1(input) << endl;
    cout << "Part2: " << Part2(input) << endl;

    return 0;
}
