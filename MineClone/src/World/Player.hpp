#pragma once

struct GLFWwindow;

class Camera;
class World;

class Player
{
public:
	static constexpr float PlayerSpeed = 0.1f;

private:
	World& _world;
	Camera& _camera;

public:
	Player(World& world, Camera& camera);

	void init();

	void update(GLFWwindow* window);
};