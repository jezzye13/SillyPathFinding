// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// SillyPathFinding.cpp : Defines the functions for the static library.
#include "pch.h"
#include "framework.h"
#include "glm/glm.hpp"
#include "glm/vec2.hpp"
#include "Heap.h"

namespace spf {

Node* GetNode(std::vector<spf::Node>& grid, const unsigned int& gridWidth, const glm::ivec2& position)
{
	int index = (position.x * gridWidth) + position.y;
	size_t size = grid.size();
	if (index < 0 || index >= size)
	{
		return nullptr;
	}
	else
	{
		return &grid.at(index);
	}
}

int ToInt(glm::ivec2 v, int width) {
	return (v.x * width) + v.y;
}

bool AStar(std::vector<spf::Node>& grid, const unsigned int& gridWidth, const glm::ivec2& start, const glm::ivec2& finish, std::vector<glm::ivec2>& path)
{
	const glm::ivec2 directions[] = {
		 glm::ivec2(-1, 0),
		 glm::ivec2(-1, -1),
		 glm::ivec2(0, -1),
		 glm::ivec2(1, -1),
		 glm::ivec2(1, 0),
		 glm::ivec2(1, 1),
		 glm::ivec2(0, 1),
		 glm::ivec2(-1, 1), };

	glm::ivec2 currentNode;
	jv::Heap<glm::ivec2> openList{};
	openList.length = grid.size();
	openList.data = new jv::KeyPair<glm::ivec2>[grid.size()];
	std::unordered_set<int> closeList;

	glm::ivec2 startPosition = start;

	openList.Insert(start, GetNode(grid, gridWidth, start)->F());
	closeList.insert(ToInt(start, gridWidth));
	GetNode(grid, gridWidth, start)->parrent = start;

	/*
	if you want to have the perfect path:
	if you see that a child is already in closed, check if the previous F value is larger than the current one.
	if its smaller, you update the F value in the closed thingy and you add the child in open regardless.
	*/

	while (openList.count > 0)
	{
		currentNode = openList.Pop();

		if (currentNode == finish)
		{
			std::vector<glm::ivec2> returnPath;
			glm::ivec2 current = currentNode;

			int safety = 0;
			while (current != startPosition && safety < 4000)
			{
				returnPath.push_back(current);
				current = GetNode(grid, gridWidth, current)->parrent;
				safety++;
			}
			returnPath.push_back(startPosition);
			path = returnPath;
			delete[] openList.data;
			return true;
		}

		std::vector<glm::ivec2> children;
		for (size_t i = 0; i < 8; i++)
		{
			glm::ivec2 look = currentNode + directions[i];
			Node* node = GetNode(grid, gridWidth, look);
			if (node != nullptr)
			{
				if (!node->isWall)
				{
					if (closeList.find(ToInt(look, gridWidth)) == closeList.end())
					{
						node->parrent = currentNode;
						children.push_back(look);
					}
				}
			}
		}

		for (glm::ivec2 child : children)
		{
			Node* node = GetNode(grid, gridWidth, child);
			node->G = GetNode(grid, gridWidth, currentNode)->G + GetNode(grid, gridWidth, currentNode)->Weight();
			node->H = glm::distance(glm::vec2(child), glm::vec2(finish));

			openList.Insert(child, node->F());
			closeList.insert(ToInt(child, gridWidth));
		}
	}
	delete[] openList.data;
	return false;
}
} // namespace spf