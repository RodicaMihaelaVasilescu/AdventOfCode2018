#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

map<char, int> directionsToInteger = { {'N', 0}, {'S', 1}, {'E', 2}, {'W', 3} };
int row[] = {-1, 1, 0, 0 };
int col[] = { 0, 0, 1,-1 };

int  MaximumNumberOfDoors, NoOfRoomsWithAtLeast1000Doors;
map<pair<int, int>, int> NumberOfDoors;

void generateMap( pair<int, int> coordinates = make_pair(0, 0))
{
	auto currentRoomCoordinates = coordinates;
	char ch;
	while (cin >> ch)
	{
		if (directionsToInteger.find(ch) != directionsToInteger.end())
		{
			auto newRoomCoordinates = make_pair(currentRoomCoordinates.first + row[directionsToInteger[ch]], currentRoomCoordinates.second + col[directionsToInteger[ch]]);
			if (NumberOfDoors[newRoomCoordinates] == 0)
			{
				NumberOfDoors[newRoomCoordinates] = NumberOfDoors[currentRoomCoordinates] + 1;
				MaximumNumberOfDoors = max(NumberOfDoors[newRoomCoordinates], MaximumNumberOfDoors);
				NumberOfDoors[newRoomCoordinates] >= 1000 ? NoOfRoomsWithAtLeast1000Doors++ : 0;
			}
			currentRoomCoordinates = newRoomCoordinates;
		}
		else if (ch == '(')
		{
			generateMap(currentRoomCoordinates);
		}
		else if (ch == '|')
		{
			currentRoomCoordinates = coordinates;
		}
		else if(ch == '^')
		{
			continue;
		}
		else
		{
			return;
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	generateMap();
	cout << "Part1: " << MaximumNumberOfDoors << endl;
	cout << "Part2: " << NoOfRoomsWithAtLeast1000Doors<< endl;
	return 0;
}
