#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define DOOR 'D'
#define ROOM 'R'

map<char, int> directionsToInteger = { {'N', 0}, {'S', 1}, {'E', 2}, {'W', 3} };
int row[] = { -1, 1, 0, 0 };
int col[] = { 0, 0, 1,-1 };

map<pair<int, int>, char> CoordonatesOfRoomsAndDoors;
int index;

void generateMap(string regex, pair<int, int> coordinates = make_pair(0, 0))
{
	auto currentCoordinates = coordinates;
	for (index++; regex[index] != 0; index++)
	{
		if (directionsToInteger.find(regex[index]) != directionsToInteger.end())
		{
			int x = currentCoordinates.first + row[directionsToInteger[regex[index]]];
			int y = currentCoordinates.second + col[directionsToInteger[regex[index]]];
			CoordonatesOfRoomsAndDoors[make_pair(x, y)] = DOOR;
			x += row[directionsToInteger[regex[index]]];
			y += col[directionsToInteger[regex[index]]];
			CoordonatesOfRoomsAndDoors[make_pair(x, y)] = ROOM;
			currentCoordinates = make_pair(x, y);
		}
		else if (regex[index] == '(')
		{
			generateMap(regex, currentCoordinates);
		}
		else if (regex[index] == '|')
		{
			currentCoordinates = coordinates;
		}
		else
		{
			return;
		}
	}
}

void Solve()
{
	int MaximumNumberOfRooms = 0, AtLeast1000Doors = 0;
	map<pair<int, int>, int> CoordinatesOfRooms_NumberOfDoors;
	queue<pair<int, int>> CoordinatesOfRoomsQueue;
	CoordinatesOfRoomsQueue.push(make_pair(0, 0));
	while (!CoordinatesOfRoomsQueue.empty())
	{
		auto coordinates = CoordinatesOfRoomsQueue.front();
		CoordinatesOfRoomsQueue.pop();

		for (int i = 0; i < 4; i++)
		{
			int x = coordinates.first + row[i];
			int y = coordinates.second + col[i];
			if (CoordonatesOfRoomsAndDoors[make_pair(x, y)] == DOOR)
			{
				x += row[i];
				y += col[i];
				if (CoordinatesOfRooms_NumberOfDoors[make_pair(x, y)] == 0)
				{
					CoordinatesOfRooms_NumberOfDoors[make_pair(x, y)] = CoordinatesOfRooms_NumberOfDoors[coordinates] + 1;
					CoordinatesOfRoomsQueue.push(make_pair(x, y));

					MaximumNumberOfRooms = max(CoordinatesOfRooms_NumberOfDoors[make_pair(x, y)], MaximumNumberOfRooms);
					CoordinatesOfRooms_NumberOfDoors[make_pair(x, y)] >= 1000 ? AtLeast1000Doors++ : 0;
				}
			}
		}
	}
	cout << "Part1: " << MaximumNumberOfRooms << endl;
	cout << "Part2: " << AtLeast1000Doors << endl;
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	string input;
	cin >> input;
	generateMap(input);
	Solve();
	return 0;
}
