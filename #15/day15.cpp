#include <bits/stdc++.h>
#define INFINITE INT_MAX
using namespace std;

int N, M;
vector <string> input;

struct Unit
{
    string type;
    int index = -1, hp, x, y;

    bool operator < (const Unit &otherUnit)
    {
        return (x < otherUnit.x) || (x == otherUnit.x && y < otherUnit.y);
    }
    void operator = (const Unit &otherUnit)
    {
        index = otherUnit.index;
        hp = otherUnit.hp;
        type = otherUnit.type;
        x = otherUnit.x;
        y = otherUnit.y;
    }
};

int r[] = { -1, 0, 0, 1 };
int c[] = { 0, -1, 1, 0 };

vector<Unit> ReadUnits ()
{
    vector<Unit> allElvesAndGoblins;
    string inputLine;

    int index = 0;
    while(getline(cin, inputLine))
    {
        for(int i = 0; inputLine[i] != 0; i++)
        {
            if(inputLine[i] == 'G' || inputLine[i] == 'E')
            {
                Unit unit{string(1, inputLine[i]), index++, 200, input.size(), i };
                allElvesAndGoblins.push_back(unit);
                inputLine[i] = '.';
            }
        }

        input.push_back(inputLine);
        M = inputLine.size();
    }

    N = input.size();
    return allElvesAndGoblins;
}

bool gameOver(vector<Unit> elvesAndGoblins)
{
    bool thereAreGoblins = find_if(elvesAndGoblins.begin(), elvesAndGoblins.end(), [](Unit u)
    {
        return u.type == "G";

    }) == elvesAndGoblins.end() ? false : true;

    bool thereAreElves = find_if(elvesAndGoblins.begin(), elvesAndGoblins.end(), [](Unit u)
    {
        return u.type == "E";

    }) == elvesAndGoblins.end() ? false : true;

    return !(thereAreElves && thereAreGoblins);
}

void initializeDistancesMatrix(int(& distance)[35][35], vector<Unit> elvesAndGoblins )
{
    for(int i = 0; i != N; i++)
    {
        for(int j = 0; j != M; j++)
        {
            if(input[i][j] == '#')
            {
                distance[i][j] = INFINITE;
            }
        }
    }
    for(auto unit: elvesAndGoblins)
    {
        if(unit.hp > 0)
        {
            distance[unit.x][unit.y] = INFINITE;
        }
    }
}

void generateDistancesFromAPoint( Unit start, int (&distance)[35][35], vector <Unit> elvesAndGoblins)
{
    initializeDistancesMatrix(distance, elvesAndGoblins);

    queue<pair<int, int>> queueOfCoordinates;

    queueOfCoordinates.push(make_pair(start.x, start.y));
    distance[start.x][start.y] = 1;

    while(!queueOfCoordinates.empty())
    {
        int x = get<0>(queueOfCoordinates.front());
        int y = get<1>(queueOfCoordinates.front());

        for(int i = 0; i < 4; i++)
        {
            int row = x + r[i];
            int col = y + c[i];

            if((row > 0) && (row < N) && (col > 0) && (col < M) && distance[row][col] == 0)
            {
                distance[row][col] = distance[x][y]+1;
                queueOfCoordinates.push(make_pair(row, col));
            }
        }
        queueOfCoordinates.pop();
    }
}

void Move(Unit &unit, vector<Unit> elvesAndGoblins)
{
    if(unit.hp < 0)
        return;

    int distanceFromUnit[35][35] {}, MinDistance = INFINITE;
    generateDistancesFromAPoint(unit, distanceFromUnit, elvesAndGoblins);

    Unit enemyNeighbour ;

    for(auto possibleEnemy: elvesAndGoblins)
    {
        if(possibleEnemy.type != unit.type && possibleEnemy.hp > 0)
        {
            if(abs(unit.x - possibleEnemy.x) + abs(unit.y - possibleEnemy.y) == 1)
                return;

            for(int i = 0; i < 4; i++)
            {
                int row = possibleEnemy.x + r[i];
                int col = possibleEnemy.y + c[i];

                if(distanceFromUnit[row][col] > 0 && distanceFromUnit[row][col] < MinDistance)
                {
                    MinDistance = distanceFromUnit[row][col];
                    enemyNeighbour = possibleEnemy;
                    enemyNeighbour.x = row;
                    enemyNeighbour.y = col;
                }
            }
        }
    }

    Unit unitNeighbour;

    MinDistance = INFINITE;
    if(enemyNeighbour.index != -1)
    {
        int distanceFromEnemy[35][35] {};

        generateDistancesFromAPoint(enemyNeighbour, distanceFromEnemy, elvesAndGoblins);

        for(int i = 0; i < 4; i++)
        {
            int row = unit.x + r[i];
            int col = unit.y + c[i];
            if(distanceFromEnemy[row][col] > 0 && distanceFromEnemy[row][col] < MinDistance)
            {
                MinDistance = distanceFromEnemy[row][col];
                unitNeighbour = unit;
                unitNeighbour.x = row;
                unitNeighbour.y = col;
            }
        }
    }

    if(enemyNeighbour.index != -1)
    {
        unit.x = unitNeighbour.x;
        unit.y = unitNeighbour.y;
    }
}

set<int> indexesOfUnitsToRemove;
void Attack(Unit unit, vector<Unit> &elvesAndGoblins)
{
    if(unit.hp < 0)
        return;

    Unit enemy;
    enemy.hp = INFINITE;
    for(auto possibleEnemy: elvesAndGoblins)
    {
        if(possibleEnemy.type != unit.type && possibleEnemy.hp > 0 &&possibleEnemy.hp < enemy.hp && abs(unit.x- possibleEnemy.x) + abs(unit.y - possibleEnemy.y) == 1)
        {
            enemy = possibleEnemy;
        }
    }

    if(enemy.index == -1 || enemy.hp == INFINITE)
        return;

    for(auto &u: elvesAndGoblins)
    {
        if(enemy.index == u.index)
        {
            u.hp -= 3;
            if(u.hp < 0)
            {
                indexesOfUnitsToRemove.insert(u.index);
            }
            break;
        }
    }
}

int main()
{
    freopen ("in.txt", "r", stdin);
    freopen ("out.txt", "w", stdout);

    auto elvesAndGoblins = ReadUnits();

    int round = -1;
    while(!gameOver(elvesAndGoblins))
    {
        round++;
        sort(elvesAndGoblins.begin(), elvesAndGoblins.end());
        for(auto &unit: elvesAndGoblins)
        {
            Move(unit, elvesAndGoblins);
            Attack(unit, elvesAndGoblins );
        }

        for(auto i = indexesOfUnitsToRemove.rbegin(); i != indexesOfUnitsToRemove.rend(); i++)
        {
            elvesAndGoblins.erase(remove_if(elvesAndGoblins.begin(), elvesAndGoblins.end(), [&](Unit const & a)
            {
                return a.index == *i;
            }),
            elvesAndGoblins.end());
        }
        indexesOfUnitsToRemove.clear();
    }

    ///Part1
    cout << "Part1 : " << round * accumulate(elvesAndGoblins.begin(), elvesAndGoblins.end(), 0, [](int sum, Unit unit)
    {
        return sum + unit.hp;
    });

    return 0;
}
