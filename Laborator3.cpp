#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

struct patrat{
	float x;
	float y;
	float lungime;
	float inaltime;
};

struct cerc {
	float x;
	float y;
	double raza;
};
struct perete {
	float x;
	float y;
	float lungime;
	float inaltime;
};

patrat sq,sq2,sq3,sq4,sq5; 
cerc circle;
perete wall1, wall2, wall3;
glm::mat3 platforma = glm::mat3(1);
glm::mat3 bila = glm::mat3(1);
glm::mat3 brick = glm::mat3(1);

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

bool showBrick[12][12];

void Laborator3::Init()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			showBrick[i][j] = true;
		}
	}
	
	time_from_start = 0;

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	


	glm::vec3 corner = glm::vec3(0,0,0);
	float squareSide = 50;
	float latime = 30;
	float latime2 = 10;
	float squareSide2 = 200;
	double radius = 10.0;
	float latime3 = 620;
	float squareSide3 = 20;
	float latime4 = 20;
	float squareSide4 = 1280;


	

	
		Mesh* square1= Object2D::CreateSquare("square1", glm::vec3(220, 280, 0), squareSide, latime, glm::vec3(1, 0, 0), true);
		AddMeshToList(square1);

		Mesh* square2 = Object2D::CreateSquare("square2", glm::vec3(550, 25, 0), squareSide2, latime2, glm::vec3(0, 1, 0), true);
		AddMeshToList(square2);

		Mesh* square3 = Object2D::CreateSquare("square3", glm::vec3(0, 80, 0), squareSide3, latime3, glm::vec3(1, 0, 0), true);
		AddMeshToList(square3);

		Mesh* square4 = Object2D::CreateSquare("square4", glm::vec3(0, 700, 0), squareSide4, latime4, glm::vec3(1, 0, 0), true);
		AddMeshToList(square4);

		Mesh* square5 = Object2D::CreateSquare("square5", glm::vec3(1260, 80, 0), squareSide3, latime3, glm::vec3(1, 0, 0), true);
		AddMeshToList(square5);

	
	Mesh* circle1 = Object2D::CreateCircle("circle1", glm::vec3(650,65,0), radius, glm::vec3(1, 1, 1),true);
	AddMeshToList(circle1);

	Mesh* circle2 = Object2D::CreateCircle("circle2", glm::vec3(0, 30, 0), radius, glm::vec3(1, 1, 1), true);
	AddMeshToList(circle2);

	sq.x = 220;
	sq.y = 280;
	sq.lungime = 70;
	sq.inaltime = 50;

	sq2.x = 550;
	sq2.y = 25;
	sq2.lungime = 200;
	sq2.inaltime = 10;

	sq3.x = 0;
	sq3.y = 80;
	sq3.lungime = 20;
	sq3.inaltime = 620;

	sq4.x = 0;
	sq4.y = 700;
	sq4.lungime = 1280;
	sq4.inaltime = 20;

	sq5.x = 1260;
	sq5.y = 80;
	sq5.lungime = 20;
	sq5.inaltime = 620;

	circle.x = 650;
	circle.y = 65;
	circle.raza = 10.0;
	//cout << circle.x <<" "<< circle.y << endl;
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

bool checkCollision(cerc circle, patrat sq, glm::vec2 coord)
{
	glm::vec2 center(circle.x, circle.y);
	glm::vec2 aabb_half_extents(sq.lungime / 2, sq.inaltime / 2);
	glm::vec2 aabb_center(coord.x + aabb_half_extents.x, coord.y + aabb_half_extents.y);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	return glm::length(difference) < circle.raza;
}

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	int best_match = -1;
	for (int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}
	
typedef std::tuple<bool, Direction, glm::vec2> Collision;

Collision CheckCollision2(cerc circle, patrat sq, glm::vec2 coord)
{
	glm::vec2 center(circle.x, circle.y);
	glm::vec2 aabb_half_extents(sq.lungime / 2, sq.inaltime / 2);
	glm::vec2 aabb_center(coord.x + aabb_half_extents.x, coord.y + aabb_half_extents.y);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	if (glm::length(difference) <= circle.raza) 
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}


glm::vec2 velocity(0, 1);

void Laborator3::Update(float deltaTimeSeconds)
{
	
	//cout << circle.x << " " << circle.y << endl;
	int k = 0;
	while (k < 3)
	{
		modelMatrix *= Transform2D::Translate(30, 0);
		if (circle.x > 1280 || circle.x < 0 || circle.y < 0)
		{
			k++;
			//blocat = 1;
		}
			RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
			k++;
	

	}
	
	

	if (blocat == 1)
	{
		RenderMesh2D(meshes["circle1"], shaders["VertexColor"], bila);
		
	}

	
	for (int i = 0; i < 7; i++)
	{
		
		for (int j = 0; j < 10; j++)
		{
			brick = glm::mat3(1);
			brick *= Transform2D::Translate((j + 1) * sq.lungime, (i + 1) * sq.inaltime);
			glm::vec2 coord((j + 1) * sq.lungime + sq.x, (i + 1) * sq.inaltime + sq.y);
			Collision collision = CheckCollision2(circle, sq, coord);
			if (std::get<0>(collision) && showBrick[i][j])
			{
				//brick *= Transform2D::Scale(0.5, 0.5);
				//RenderMesh2D(meshes["square1"], shaders["VertexColor"], brick);
				showBrick[i][j] = false;
				
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision); 
				if (dir == LEFT || dir == RIGHT)
				{
					velocity.x = -velocity.x;
					float lovitura = circle.raza - std::abs(diff_vector.x);
					if (dir == LEFT)
						circle.x += lovitura;
					else
						circle.x -= lovitura;
				}
				else
				{
					velocity.y = -velocity.y;
					float lovitura = circle.raza - std::abs(diff_vector.y);
					if (dir == UP)
					{
						circle.y -= lovitura;
					}
					else
						circle.y += lovitura;
				}
			}
			if (showBrick[i][j])
			{ 
				RenderMesh2D(meshes["square1"], shaders["VertexColor"], brick);
			}
			

		}

	}
	if (blocat == 0)
	{
		_y = 360 * deltaTimeSeconds;
		_x = 360 * deltaTimeSeconds;
		circle.x += _x * velocity.x;
		circle.y += _y * velocity.y;
		bila *= Transform2D::Translate(_x * velocity.x, _y * velocity.y);

		RenderMesh2D(meshes["circle1"], shaders["VertexColor"], bila);

	}
		
	modelMatrix = glm::mat3(1);
	
	RenderMesh2D(meshes["square2"], shaders["VertexColor"], platforma);

	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

	RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);

	glm::vec2 coord2(sq2.x, sq2.y);
	
	  Collision collision2 = CheckCollision2(circle, sq2, coord2);
	if ( std::get<0>(collision2))
	{
		float board = sq2.x + sq2.lungime / 2;
		float distance = (circle.x - board + circle.raza) / (sq2.lungime / 2);
		velocity = glm::vec2(distance, 1 - std::abs(distance));
		velocity = glm::normalize(velocity);
		
		
	}

	glm::vec2 coord3(sq3.x, sq3.y);

	Collision collision3 = CheckCollision2(circle, sq3, coord3);
	if (std::get<0>(collision3))
	{

		Direction dir = std::get<1>(collision3);
		glm::vec2 diff_vector = std::get<2>(collision3);
		if (dir == LEFT || dir == RIGHT)
		{
			velocity.x = -velocity.x;
			float lovitura = circle.raza - std::abs(diff_vector.x);
			if (dir == LEFT)
				circle.x += lovitura;
			else
				circle.x -= lovitura;
		}
		else
		{
			velocity.y = -velocity.y;
			float lovitura = circle.raza - std::abs(diff_vector.y);
			if (dir == UP)
			{
				circle.y -= lovitura;
			}
			else
				circle.y += lovitura;
		}
	}
	
	glm::vec2 coord4(sq4.x, sq4.y);

	Collision collision4 = CheckCollision2(circle, sq4, coord4);
	if (std::get<0>(collision4))
	{
		Direction dir = std::get<1>(collision4);
		glm::vec2 diff_vector = std::get<2>(collision4);
		if (dir == LEFT || dir == RIGHT)
		{
			velocity.x = -velocity.x;
			float lovitura = circle.raza - std::abs(diff_vector.x);
			if (dir == LEFT)
				circle.x += lovitura;
			else
				circle.x -= lovitura;
		}
		else
		{
			velocity.y = -velocity.y;
			float lovitura = circle.raza - std::abs(diff_vector.y);
			if (dir == UP)
			{
				circle.y -= lovitura;
			}
			else
				circle.y += lovitura;
		}
	}

	glm::vec2 coord5(sq5.x, sq5.y);

	Collision collision5 = CheckCollision2(circle, sq5, coord5);
	if (std::get<0>(collision5))
	{
		Direction dir = std::get<1>(collision5);
		glm::vec2 diff_vector = std::get<2>(collision5);
		if (dir == LEFT || dir == RIGHT)
		{
			velocity.x = -velocity.x;
			float lovitura = circle.raza - std::abs(diff_vector.x);
			if (dir == LEFT)
				circle.x += lovitura;
			else
				circle.x -= lovitura;
		}
		else
		{
			velocity.y = -velocity.y;
			float lovitura = circle.raza - std::abs(diff_vector.y);
			if (dir == UP)
			{
				circle.y -= lovitura;
			}
			else
				circle.y += lovitura;
		}
	}
	
	

}
void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	sq2.x += deltaX;
	platforma *= Transform2D::Translate(deltaX, 0);
	if (blocat == 1)
	{
		bila *= Transform2D::Translate(deltaX, 0);
		circle.x += deltaX;
	}
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (button-1 == GLFW_MOUSE_BUTTON_LEFT)
		{
		blocat = 0;
		
		}
	

	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
