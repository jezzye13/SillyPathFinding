// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include "glm/vec3.hpp"
#include "../SillyPathFinding/SillyPathFinding.cpp"
#include "../SillyPathFinding/Node.cpp"

constexpr auto SIZE_X = 20;
constexpr auto SIZE_Y = 50;

int main()
{
	std::cout << "Hello Silly PathFinding!\n";

	std::vector<spf::Node> grid;

	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			bool isWall = false;
			if (x < 8 && y == 5)
			{
				isWall = true;
			}

			grid.push_back(spf::Node(glm::ivec2(x, y), 1.0f, isWall));
		}
	}

	std::vector<glm::ivec2> path;

	bool foundPath = spf::AStar(grid, glm::ivec2(4, 3), glm::ivec2(12, 44), path);

	printf("Path found: ");
	printf(foundPath ? "true" : "false");
	printf("\n");

	std::string output;
	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			bool pathFound = false;
			for (glm::ivec2 item : path)
			{
				if (item.x == x && item.y == y) {
					output += "@";
					pathFound = true;
					continue;
				}
			}
			if (spf::GetNode(grid, glm::ivec2(x, y))->isWall)
			{
				output += "W";
			}
			else if (!pathFound)
			{
				output += ".";
			}
		}
		output += "\n";
	}
	std::cout << output;
}
