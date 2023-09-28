#pragma once

std::string PathToString(std::vector<spf::Node>& grid, const int& gridWidth, const std::vector<glm::ivec2>& path, const int gridSizeX, const int gridSizeY)
{
	std::string output;
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
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
			if (spf::GetNode(grid, gridWidth, glm::ivec2(x, y))->isWall)
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
	return output;
}