#include <bits/stdc++.h>
using namespace std;

struct marble
{
    int info;
    struct marble *next, *prev;
};

long long Solve(int playersNumber, int marblesNumber )
{
    struct marble *root = (struct marble *) malloc( sizeof ( struct marble));
    root -> next = root;
    root -> prev = root;
    root -> info = 0;

    vector <int> marbles {root -> info};
    unordered_map <int, long long> playerScore;

    struct marble *index = root;

    int counter = 0, currentPlayer = -1;
    while( ++counter <= marblesNumber)
    {
        ++currentPlayer %= playersNumber;

        if( counter % 23 == 0)
        {
            index = index -> prev->prev->prev->prev->prev->prev->prev;
            index -> prev -> next = index -> next;
            index -> next -> prev = index -> prev;

            playerScore[currentPlayer] += counter;
            playerScore[currentPlayer] += index -> info;

            auto toRemove = index;
            index = index -> next;
            free(toRemove);
        }
        else
        {
            struct marble *newElement =  (struct marble *) malloc( sizeof ( struct marble));
            auto prev = index -> next;
            auto next = index -> next -> next;

            newElement -> info = counter;
            newElement -> next = next;
            newElement -> prev = prev;

            next -> prev = newElement;
            prev -> next = newElement;

            index = newElement;
        }
    }

    return get<1>( *max_element(playerScore.begin(), playerScore.end(), []( pair<int, long long> a, pair<int, long long> b)
    {
        return a.second < b.second;
    }));

}
int main()
{

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    string input;
    getline(cin, input);

    istringstream iss(input);
    vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());

    int playersNumber = stoi(results[0]);
    int marblesNumber = stoi(results[6]);

    ///Part1
    cout << Solve(playersNumber, marblesNumber) << endl;
    ///Part2
    cout << Solve(playersNumber, marblesNumber * 100);

    return 0;
}
