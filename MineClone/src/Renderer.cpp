#include "Renderer.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Graphics/Shader.hpp"
#include "Graphics/ShaderProgram.hpp"

#include "Game.hpp"

Renderer::Renderer()
{
	if (!glfwInit())
	{
		throw std::exception("Cannot init glfw!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_canvasSize.x, _canvasSize.y, "Hello World", nullptr, nullptr);

	if (!_window)
	{
		throw std::exception("Cannot create window!");
	}

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::exception("Failed to initialize GLAD");
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		Game::get()->getRenderer().updateCanvasSize({ width, height });
	});

	updateCanvasSize(_canvasSize);

	glfwSetCursorPos(_window, _canvasSize.x / 2.0, _canvasSize.y / 2.0);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	loadShader("shaders/chunk", _chunkShader);
	loadShader("shaders/hud", _hudShader);
	loadShader("shaders/grid", _gridShader);
}

Renderer::~Renderer()
{
	if (_window != nullptr)
	{
		glfwTerminate();
	}
}

void Renderer::draw()
{
}

void Renderer::updateCanvasSize(const glm::uvec2& size)
{
	_canvasSize = size;
	_camera.setTargetSize(size);
	glViewport(0, 0, size.x, size.y);
}

void Renderer::loadShader(const std::string& shaderName, ShaderProgram& shaderProgram)
{
	auto vertexShader = Shader(ShaderType::Vertex, shaderName + ".vert");
	auto fragmentShader = Shader(ShaderType::Fragment, shaderName + ".frag");

	if (vertexShader.isValid() == false || fragmentShader.isValid() == false)
	{
		puts(vertexShader.getInfoLog().c_str());
		puts(fragmentShader.getInfoLog().c_str());

		throw std::exception("Cannot create shaders!");
	}

	shaderProgram.create();
	shaderProgram.linkShaders(vertexShader, fragmentShader);

	if (!shaderProgram.isValid())
	{
		throw std::exception("Cannot create shader program!");
	}
}
