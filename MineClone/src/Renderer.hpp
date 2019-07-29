#pragma once

#include <memory>

#include "Graphics/Camera.hpp"
#include "Graphics/ShaderProgram.hpp"

struct GLFWwindow;
class ShaderProgram;

class Renderer
{
public:
private:
	GLFWwindow* _window = nullptr;

	Camera _camera;

	ShaderProgram _chunkShader;
	ShaderProgram _hudShader;
	ShaderProgram _gridShader;

	glm::uvec2 _canvasSize = { 1024, 768 };

public:
	Renderer();
	~Renderer();

	GLFWwindow* getWindow() { return _window; }
	Camera& getCamera() { return _camera; }

	void draw();

	ShaderProgram& getChunkShader() { return _chunkShader; }
	ShaderProgram& getHudShader() { return _hudShader; }
	ShaderProgram& getGridShader() { return _gridShader; }

	const glm::uvec2& getCanvasSize() const { return _canvasSize; }

	void updateCanvasSize(const glm::uvec2& size);

private:
	void loadShader(const std::string& shaderName, ShaderProgram& shaderProgram);
};