#pragma once

#include "Graphics/Camera.hpp"

struct GLFWwindow;

class Player
{
private:
	Camera& _camera;

	static constexpr float PlayerSpeed = 0.05f;

public:
	Player(Camera& camera);

	void init();

	void update(GLFWwindow* window);
};