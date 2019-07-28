#pragma once

#include "Graphics/VertexBuffer.hpp"

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

	glm::vec3 _highlighterPos{ 0.f };

	bool _drawHighlighter = false;
	VertexBuffer _highlighter{ 24, PrimitiveType::Lines };

	bool _blockRemoving = false;

public:
	Player(World& world, Camera& camera);

	void init();

	void update(GLFWwindow* window);

	void draw(ShaderProgram& shaderProgram);
};