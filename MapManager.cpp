#include "MapManager.h"

#include <set>
#include <algorithm>

#include <iostream>

using namespace std;

#include "ASNode.h"

using std::shared_ptr;
using std::set;

int MapManager::GetDistance(int sx, int sy, int dx, int dy)
{
	int absX = abs(sx - dx);
	int absY = abs(sy - dy);

	int minV, maxV;

	if (absX < absY)
	{
		minV = absX;
		maxV = absY;
	}
	else
	{
		minV = absY;
		maxV = absX;
	}

	return minV * 14 + (maxV - minV) * 10;
}

string MapManager::GetKey(int x, int y)
{
	return std::to_string(x) + "," + std::to_string(y);
}

bool MapManager::CheckIndex(int x, int y)
{
	if (x < 0 || x >= MAP_SIZE_X || y < 0 || y >= MAP_SIZE_Y)
		return false;

	return true;
}

MapManager::MapManager(vector<vector<char>> _worldMap)
 : worldMap(_worldMap) 
{
	MAP_SIZE_X = worldMap.size();
	MAP_SIZE_Y = worldMap.front().size();
}

vector<pair<int, int>> MapManager::AStar(const vector<vector<char>>& worldMap, int sx, int sy, int dx, int dy)
{
	auto comp = [](const shared_ptr<ASNode> n1, const shared_ptr<ASNode> n2)
	{
		return n1->g + n1->h < n2->g + n2->h;
	};

	multiset<shared_ptr<ASNode>, decltype(comp)> opened(comp);
	set<string> closed;

	shared_ptr<ASNode> start = std::make_shared<ASNode>(sx, sy, 0, GetDistance(sx, sy, dx, dy));
	opened.insert(start);

	vector<pair<int, int>> ret;

	while (!opened.empty())
	{
		shared_ptr<ASNode> cur = (*opened.begin());
		opened.erase(opened.begin());
		closed.insert(GetKey(cur->x, cur->y));

		// 찾았다!
		if (cur->x == dx && cur->y == dy)
		{
			while (true)
			{
				ret.push_back({ cur->x, cur->y });

				if (cur->x == sx && cur->y == sy)
				{
					reverse(ret.begin(), ret.end());
					return ret;
				}

				cur = cur->parent;
			}
		}

		for (int i = 0; i < 8; ++i)
		{
			int nx = cur->x + nextX[i];
			int ny = cur->y + nextY[i];

			if (!CheckIndex(nx, ny) || worldMap[nx][ny] == 'W' || closed.find(GetKey(nx, ny)) != closed.end())
				continue;

			int nextG = GetDistance(cur->x, cur->y, nx, ny) + cur->g;
			int nextH = GetDistance(nx, ny, dx, dy);

			multiset<shared_ptr<ASNode>>::iterator it = opened.begin();

			for (; it != opened.end(); ++it)
				if ((*it)->x == nx && (*it)->y == ny)
					break;

			if (it != opened.end()) // opened에 이미 추가된 노드
			{
				shared_ptr<ASNode> n = (*it);

				if (n->g + n->h > nextG + nextH)
				{
					opened.erase(it);

					shared_ptr<ASNode> newNode = std::make_shared<ASNode>(nx, ny, nextG, nextH);
					newNode->parent = cur;
					opened.insert(newNode);
				}
			}
			else // opened에 추가되지 않은 노드
			{
				multiset<shared_ptr<ASNode>>::iterator it = opened.begin();

				shared_ptr<ASNode> newNode = std::make_shared<ASNode>(nx, ny, nextG, nextH);
				newNode->parent = cur;
				auto e = opened.insert(newNode);
			}
		}
	}

	return ret;
}
