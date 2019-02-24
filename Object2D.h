#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length,float width, glm::vec3 color, bool fill = false);
	Mesh* CreateCircle(std::string name, glm::vec3 leftBottomCorner, double radius, glm::vec3 color, bool fill);

}

