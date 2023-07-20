#pragma once
#include "glm/vec2.hpp"
namespace spf {
class Node
{
public:
	float G = 0;
	float H = 0;
	float F() { return G + H; };
	float Weight() { return weight; }
	glm::ivec2 position;
	glm::ivec2 parrent = glm::ivec2(0);
	bool isWall = false;

	Node(glm::ivec2 position, float weight = 1.0f, bool isWall = false) : position(position), weight(weight), isWall(isWall) { };

private:
	float weight;
};
}