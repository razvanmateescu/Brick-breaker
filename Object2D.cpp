#include "Object2D.h"

#include <Core/Engine.h>
#include <vector>
Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	

	std::vector<VertexFormat>  vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length,0,0), color),
		VertexFormat(corner + glm::vec3(length,width,0), color),
		VertexFormat(corner + glm::vec3(0,width,0), color)
	};
	
				
	
	
	Mesh* square = new Mesh(name);

	std::vector<unsigned short> indices = { 0,1,2,3 }; //= { 0, 1, 2, 3, 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 leftBottomCorner, double radius, glm::vec3 color, bool fill)
{


	glm::vec3 corner = leftBottomCorner;



	std::vector<VertexFormat>  vertices;

	for (int i = 0; i <= 360; i++) {
		vertices.push_back(VertexFormat(corner + glm::vec3(radius * cos(2.0f * M_PI * i / 360), radius * sin(2.0f * M_PI * i / 360), 0), color));
		
	}


	Mesh* circle = new Mesh(name);

	std::vector<unsigned short> indices; //= { 0, 1, 2, 3, 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	for (int i = 0; i < 359; i++)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}