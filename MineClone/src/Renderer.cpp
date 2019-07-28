#include "Renderer.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Graphics/Shader.hpp"
#include "Graphics/ShaderProgram.hpp"

Renderer::Renderer()
{
	if (!glfwInit())
	{
		throw std::exception("Cannot init glfw!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(Renderer::ScreenWidth, Renderer::ScreenHeight, "Hello World", nullptr, nullptr);

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

	glfwSetCursorPos(_window, Renderer::ScreenWidth / 2.f, Renderer::ScreenHeight / 2.f);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	loadShader("chunk", _chunkShader);
	loadShader("hud", _hudShader);
	loadShader("grid", _gridShader);
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
