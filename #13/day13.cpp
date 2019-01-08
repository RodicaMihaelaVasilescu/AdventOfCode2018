#include <bits/stdc++.h>
using namespace std;

struct Cart
{
    int x, y, direction;
    char directionCharacter; /// '<', '>' 'v' '^'
};

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string inputLine;
    vector <string> input;
    vector <Cart> carts;
    while(getline(cin, inputLine))
    {
        input.push_back(inputLine);

        for(int i = 0 ; inputLine[i] != 0; i++)
        {
            if(inputLine[i] == '>' || inputLine[i] == '<' || inputLine[i]== '^' || inputLine[i] == 'v' )
            {
                Cart aux;
                aux.x = input.size()-1;
                aux.y = i;
                aux.directionCharacter = inputLine[i];
                aux.direction = -1;
                carts.push_back(aux);
            }
        }
    }

    for(int i = 0; i < (int) input.size(); i++)
    {
        for(int  j = 0; j < (int) input[i].size(); j++)
        {
            if(input[i][j] == '>' || input[i][j] == '<')
            {
                input[i][j] = '-';
            }
            if(input[i][j] == '^' || input[i][j] == 'v')
            {
                input[i][j] = '|';
            }
        }
    }

    bool isThisTheFirstCrash = true;
    set<int> indexesToRemove;
    while( carts.size() != 1 )
    {
        sort(carts.begin(), carts.end(), [](Cart a, Cart b)
        {
            return a.x < b.x || a.x == b.x && a.y < b.y;
        });

        for(auto &cart : carts)
        {
            if(cart.directionCharacter == '>')
            {
                cart.y++;
                if(input[cart.x][cart.y] == '+')
                {
                    ++cart.direction %= 3;
                    cart.direction == 0 ? cart.directionCharacter = '^' : cart.direction == 1 ? 0 : cart.directionCharacter = 'v';
                }
                else if( input[cart.x][cart.y] == 92) /// '\'
                {
                    cart.directionCharacter = 'v';
                }
                else if( input[cart.x][cart.y] == 47) /// '/'
                {
                    cart.directionCharacter = '^';
                }
            }
            else

                if(cart.directionCharacter == '<')
                {
                    cart.y--;
                    if(input[cart.x][cart.y] == '+')
                    {
                        ++cart.direction %= 3;
                        cart.direction == 0 ? cart.directionCharacter = 'v' : cart.direction == 1 ? 0 : cart.directionCharacter = '^';
                    }
                    else if( input[cart.x][cart.y] == 92) /// '\'
                    {
                        cart.directionCharacter = '^';
                    }
                    else if( input[cart.x][cart.y] == 47) /// '/'
                    {
                        cart.directionCharacter = 'v';
                    }
                }
                else if(cart.directionCharacter == '^')
                {
                    cart.x--;
                    if(input[cart.x][cart.y] == '+')
                    {
                        ++cart.direction %= 3;
                        cart.direction == 0 ? cart.directionCharacter = '<' : cart.direction == 1 ? 0 : cart.directionCharacter = '>';
                    }
                    else if( input[cart.x][cart.y] == 92) /// '\'
                    {
                        cart.directionCharacter = '<';
                    }
                    else if( input[cart.x][cart.y] == 47) /// '/'
                    {
                        cart.directionCharacter = '>';
                    }
                }
                else

                    if(cart.directionCharacter == 'v')
                    {
                        cart.x++;
                        if(input[cart.x][cart.y] == '+')
                        {
                            ++cart.direction %= 3;
                            cart.direction == 0 ? cart.directionCharacter = '>' : cart.direction == 1 ? 0 : cart.directionCharacter = '<';
                        }
                        else if( input[cart.x][cart.y] == 92) /// '\'
                        {
                            cart.directionCharacter = '>';
                        }
                        else if( input[cart.x][cart.y] == 47) /// '/'
                        {
                            cart.directionCharacter = '<';
                        }
                    }

            for(int i = 0; i != (int)carts.size(); i++)
            {
                for(int j = i+1; j != (int)carts.size(); j++)
                {
                    if(carts[i].x == carts[j].x && carts[i].y == carts[j].y)
                    {
                        ///Part1
                        if(isThisTheFirstCrash)
                        {
                            cout << "Part1 : " << carts[i].y << " " << carts[i].x << endl;
                            isThisTheFirstCrash = false;
                        }

                        indexesToRemove.insert(i);
                        indexesToRemove.insert(j);
                        break;
                    }
                }
            }
        }
        for(auto i = indexesToRemove.rbegin(); i != indexesToRemove.rend(); i++)
        {
            carts.erase(carts.begin() + *i);
        }
        indexesToRemove.clear();
    }

    ///Part2
    cout <<"Part2 : "<< carts[0].y << " " << carts[0].x;

    return 0;
}
