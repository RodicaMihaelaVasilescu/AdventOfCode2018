#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int counter = 0, n;
    char a[300][300], b[300][300];
    string inputLine;

    while(getline(cin, inputLine))
    {
        n = inputLine.size();
        counter++;
        for(int i = 0; inputLine[i]!= 0; i++)
        {
            a[counter][i+1] = inputLine[i];
        }
    }

    vector<int> valueLumberCollection;
    counter = 0;

    while( ++counter < 1000 )
    {
        int noOfTrees = 0, noOfLumberyard  = 0;
        for(int i = 1; i <= n ; i++)
        {
            for(int j = 1; j <= n ; j++ )
            {
                a[i][j] == '|' ? noOfTrees++ : a[i][j] == '#' ? noOfLumberyard++ : 0;
            }
        }

        ///Part1
        if(valueLumberCollection.size() == 10)
        {
            cout << "Part1: " << noOfTrees*noOfLumberyard  << endl;
        }

        valueLumberCollection.push_back(noOfTrees*noOfLumberyard);

        for(int i = 1; i <= n ; i++)
        {
            for(int j = 1; j <= n ; j++ )
            {
                int trees = 0, lumberyard = 0;
                for(int i1 = i-1; i1 <= i+1; i1++)
                {
                    for(int j1 = j-1; j1 <= j+1; j1++)
                    {
                        a[i1][j1] == '|' ? trees++ : a[i1][j1] == '#' ? lumberyard++ :0 ;
                    }
                }

                if(a[i][j] == '.')
                {
                    b[i][j]  = trees >= 3 ? '|': '.';
                }
                else if(a[i][j] == '|')
                {
                    b[i][j]  = lumberyard >= 3 ? '#': '|';
                }
                else
                {
                    b[i][j]  = lumberyard-1 >= 1 && trees >= 1 ? '#': '.';
                }
            }
        }

        for(int i = 1; i <= n ; i++)
            for(int j = 1; j <= n ; j++ )
                a[i][j] = b[i][j];

    }

    ///Part2
    int randomNumber = 500;
    int cycle  = find(valueLumberCollection.begin()+ randomNumber + 1, valueLumberCollection.end(), valueLumberCollection[randomNumber]) - valueLumberCollection.begin() - randomNumber;
    cout<<"Part2: " << valueLumberCollection[cycle*10 + 1000000000%cycle];

    return 0;
}
