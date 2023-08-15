#pragma once
#include <stdexcept>
#include "../SillyPathFinding/SillyPathFinding.cpp"
#include "../SillyPathFinding/Node.h"
#include "glm/glm.hpp"
#include "glm/vec2.hpp"

#pragma warning (push, 0)
#include "DocTest.h"
#pragma warning (pop)


TEST_CASE("Find simple the path") {
	constexpr auto SIZE_X = 20;
	constexpr auto SIZE_Y = 50;

	std::vector<spf::Node> grid;

	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			grid.push_back(spf::Node(glm::ivec2(x, y)));
		}
	}

	std::vector<glm::ivec2> path;

	bool foundPath = spf::AStar(grid, glm::ivec2(4, 3), glm::ivec2(12, 44), path);

	CHECK(foundPath);
}

TEST_CASE("Find simple the path with wall") {
	constexpr auto SIZE_X = 20;
	constexpr auto SIZE_Y = 50;

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

	CHECK(foundPath);
}

TEST_CASE("Impossible to find simple the path") {
	constexpr auto SIZE_X = 20;
	constexpr auto SIZE_Y = 50;

	std::vector<spf::Node> grid;

	for (size_t x = 0; x < SIZE_X; x++)
	{
		for (size_t y = 0; y < SIZE_Y; y++)
		{
			bool isWall = false;
			if (y == 5)
			{
				isWall = true;
			}

			grid.push_back(spf::Node(glm::ivec2(x, y), 1.0f, isWall));
		}
	}

	std::vector<glm::ivec2> path;

	bool foundPath = spf::AStar(grid, glm::ivec2(4, 3), glm::ivec2(12, 44), path);

	CHECK(!foundPath);
}
