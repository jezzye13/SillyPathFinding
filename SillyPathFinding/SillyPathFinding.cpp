// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// SillyPathFinding.cpp : Defines the functions for the static library.
#include "pch.h"
#include "framework.h"
#include "glm/glm.hpp"
#include "glm/vec2.hpp"

namespace spf {

Node* GetNode(std::vector<spf::Node>& grid, const glm::ivec2& position)
{
	for (std::vector<spf::Node>::size_type i = 0; i != grid.size(); i++) {
		if (grid[i].position == position)
		{
			return &grid[i];
		}
	}
	return nullptr;
}

bool AStar(std::vector<spf::Node>& grid, const glm::ivec2& start, const glm::ivec2& finish, std::vector<glm::ivec2>& path)
{
	const  glm::ivec2 directions[] = {
		 glm::ivec2(-1, 0),
		 glm::ivec2(-1, -1),
		 glm::ivec2(0, -1),
		 glm::ivec2(1, -1),
		 glm::ivec2(1, 0),
		 glm::ivec2(1, 1),
		 glm::ivec2(0, 1),
		 glm::ivec2(-1, 1), };

	glm::ivec2 currentNode;
	int currentIndex = 0;
	std::vector<glm::ivec2> openList;
	std::vector<glm::ivec2> closeList;

	glm::ivec2 startPosition = start;

	openList.push_back(start);
	GetNode(grid, start)->parrent = start;

	while (!openList.empty())
	{
		currentNode = openList[0];
		currentIndex = 0;

		for (int i = 0; i < openList.size(); i++)
		{
			glm::ivec2 item = openList[i];
			if (GetNode(grid, item)->F() < GetNode(grid, currentNode)->F())
			{
				currentNode = item;
				currentIndex = i;
			}
		}

		openList.erase(openList.begin() + currentIndex);
		closeList.push_back(currentNode);

		if (currentNode == finish)
		{
			std::vector<glm::ivec2> returnPath;
			glm::ivec2 current = currentNode;

			int safety = 0;
			while (current != startPosition && safety < 4000)
			{
				returnPath.push_back(current);
				current = GetNode(grid, current)->parrent;
				safety++;
			}
			returnPath.push_back(startPosition);
			path = returnPath; // todo return reversed path
			return true;
		}

		std::vector<glm::ivec2> children;
		for (size_t i = 0; i < 8; i++)
		{
			glm::ivec2 look = currentNode + directions[i];
			Node* node = GetNode(grid, look);
			if (node != nullptr)
			{
				if (!node->isWall)
				{
					if (!std::count(closeList.begin(), closeList.end(), look))
					{
						node->parrent = currentNode;
						children.push_back(look);
					}
				}
			}
		}

		for (glm::ivec2 child : children)
		{
			bool ignore = false;
			for (glm::ivec2 closedChild : closeList)
			{
				if (child == closedChild)
				{
					ignore = true;
				}
			}
			if (ignore) { continue; }

			Node* node = GetNode(grid, child);
			node->G = GetNode(grid, currentNode)->G + GetNode(grid, currentNode)->Weight();
			node->H = glm::distance(glm::vec2(child), glm::vec2(finish));

			ignore = false;
			for (glm::ivec2 openNode : openList)
			{
				if (std::count(openList.begin(), openList.end(), child) && GetNode(grid, child)->G > GetNode(grid, openNode)->G)
				{
					ignore = true;
				}
			}
			if (ignore) { continue; }

			openList.push_back(child);
		}
	}
	return false;
}
} // namespace spf