// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include "glm/vec3.hpp"
#include "../SillyPathFinding/SillyPathFinding.cpp"
#include "../SillyPathFinding/Node.cpp"
#include "PrintPath.h"

int main()
{
	std::cout << "Hello Silly PathFinding!\n";

	// Run path basic
	{
		const int SIZE_X = 20;
		const int SIZE_Y = 50;
		std::vector<spf::Node> grid;

		// Define nodes
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int y = 0; y < SIZE_Y; y++)
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

		bool foundPath = spf::AStar(grid, SIZE_Y, glm::ivec2(4, 3), glm::ivec2(12, 44), path);

		std::cout << "Path found: " << (foundPath ? "true" : "false") << "\n";

		std::cout << PathToString(grid, SIZE_Y, path, SIZE_X, SIZE_Y);
	}
	//

	// Run path L shape
	{
		const int SIZE_X = 40;
		const int SIZE_Y = 60;
		std::vector<spf::Node> grid;

		// Define nodes
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int y = 0; y < SIZE_Y; y++)
			{
				bool isWall = false;
				if (x < 8 && y == 5) // small wall
				{
					isWall = true;
				}

				if (y < 40 && x == 30) //wall for L shape
				{
					isWall = true;
				}

				if (x < 30 && y == 39) // small wall
				{
					isWall = true;
					if (x == 5) // create a small hole in the wall
					{
						isWall = false;
					}
				}

				grid.push_back(spf::Node(glm::ivec2(x, y), 1.0f, isWall));
			}
		}

		std::vector<glm::ivec2> path;

		bool foundPath = spf::AStar(grid, SIZE_Y, glm::ivec2(4, 3), glm::ivec2(35, 55), path);

		std::cout << "Path found: " << (foundPath ? "true" : "false") << "\n";

		std::cout << PathToString(grid, SIZE_Y, path, SIZE_X, SIZE_Y);
	}
	//

	// Run path with big wall
	{
		const int SIZE_X = 20;
		const int SIZE_Y = 50;
		std::vector<spf::Node> grid;

		// Define nodes
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int y = 0; y < SIZE_Y; y++)
			{
				bool isWall = false;
				if (x < 8 && y == 5)
				{
					isWall = true;
				}

				if (y > 15 && y < 25 && x < 15) // big wall
				{
					isWall = true;
				}

				grid.push_back(spf::Node(glm::ivec2(x, y), 1.0f, isWall));
			}
		}

		std::vector<glm::ivec2> path;

		bool foundPath = spf::AStar(grid, SIZE_Y, glm::ivec2(1, 1), glm::ivec2(1, 44), path);

		std::cout << "Path found: " << (foundPath ? "true" : "false") << "\n";

		std::cout << PathToString(grid, SIZE_Y, path, SIZE_X, SIZE_Y);
	}
	//

	// Run path with big map and wall
	{
		const int SIZE_X = 120;
		const int SIZE_Y = 120;
		std::vector<spf::Node> grid;

		// Define nodes
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int y = 0; y < SIZE_Y; y++)
			{
				bool isWall = false;
				if (y > 15 && y < 50 && x < 50) // big wall
				{
					isWall = true;
				}

				grid.push_back(spf::Node(glm::ivec2(x, y), 1.0f, isWall));
			}
		}

		std::vector<glm::ivec2> path;

		bool foundPath = spf::AStar(grid, SIZE_Y, glm::ivec2(0, 0), glm::ivec2(119, 119), path);

		std::cout << "Path found: " << (foundPath ? "true" : "false") << "\n";

		std::cout << PathToString(grid, SIZE_Y, path, SIZE_X, SIZE_Y);
	}
	//

	std::cout << "Done!\n";
	return 0;
}
