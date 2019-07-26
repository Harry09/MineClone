#pragma once

struct GLFWwindow;

class Camera;
class World;

class Player
{
private:
	World& _world;
	Camera& _camera;

	static constexpr float PlayerSpeed = 0.1f;

public:
	Player(World& world, Camera& camera);

	void init();

	void update(GLFWwindow* window);
};