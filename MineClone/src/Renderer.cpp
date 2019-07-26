#include "Renderer.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Graphics/Shader.hpp"
#include "Graphics/ShaderProgram.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	if (_window != nullptr)
	{
		glfwTerminate();
	}
}

bool Renderer::init()
{
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(Renderer::ScreenWidth, Renderer::ScreenHeight, "Hello World", nullptr, nullptr);

	if (!_window)
	{
		std::cout << "Cannot create window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glfwSetCursorPos(_window, Renderer::ScreenWidth / 2.f, Renderer::ScreenHeight / 2.f);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	auto vertexShader = Shader(ShaderType::Vertex, "chunk.vert");
	auto fragmentShader = Shader(ShaderType::Fragment, "chunk.frag");

	if (vertexShader.isValid() == false || fragmentShader.isValid() == false)
	{
		puts(vertexShader.getInfoLog().c_str());
		puts(fragmentShader.getInfoLog().c_str());

		puts("Cannot create shaders!");
		return false;
	}

	_chunkShader.create();
	_chunkShader.linkShaders(vertexShader, fragmentShader);

	if (!_chunkShader.isValid())
	{
		puts("Cannot create shader program!");
		return false;
	}

	return true;
}

void Renderer::draw()
{
}
