#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
		
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
	public:
		glm::mat3 platforma;
		glm::mat3 bila;
		glm::mat3 brick;
		float time_from_start, flag_coborare;
		int sq1_to_x, sq1_to_y, flag_top_corner;

		float sq2_scale, aux_sq2_time;
		int flag_scale;

		int sq3_rads;
		float _x = 0;
		float _y = 0;
		//glm::mat3 _y;
		float _z = 0;
		int blocat = 1;
		int PI;
};
