#pragma once

#include <memory>

#include "Graphics/Camera.hpp"
#include "Graphics/ShaderProgram.hpp"

struct GLFWwindow;
class ShaderProgram;

class Renderer
{
public:
	static constexpr unsigned ScreenWidth = 1024;
	static constexpr unsigned ScreenHeight = 768;

private:
	GLFWwindow* _window = nullptr;

	Camera _camera;

	ShaderProgram _chunkShader;
	ShaderProgram _hudShader;
	ShaderProgram _gridShader;

public:
	Renderer();
	~Renderer();

	GLFWwindow* getWindow() { return _window; }
	Camera& getCamera() { return _camera; }

	void draw();

	ShaderProgram& getChunkShader() { return _chunkShader; }
	ShaderProgram& getHudShader() { return _hudShader; }
	ShaderProgram& getGridShader() { return _gridShader; }

private:
	void loadShader(const std::string& shaderName, ShaderProgram& shaderProgram);
};