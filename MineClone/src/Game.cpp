#include "Game.hpp"

#include <iostream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Vertex.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/Texture.hpp"

Game* Game::_inst;

Game::Game()
	: 
	_player(_camera),
	_lastCursorPos{ Game::ScreenWidth / 2.f, Game::ScreenHeight / 2.f }
{
	_inst = this;
}

Game::~Game()
{
	if (_window != nullptr)
	{
		glfwTerminate();
	}
}

bool Game::init()
{
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Hello World", nullptr, nullptr);

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

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	glfwSetCursorPos(_window, Game::ScreenWidth / 2.f, Game::ScreenHeight / 2.f);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	auto vertexShader = Shader(ShaderType::Vertex, "vertex_shader.glsl");
	auto fragmentShader = Shader(ShaderType::Fragment, "fragment_shader.glsl");

	if (vertexShader.isValid() == false || fragmentShader.isValid() == false)
	{
		puts("Cannot create shaders!");
		return false;
	}

	_shaderProgram = std::make_unique<ShaderProgram>(vertexShader, fragmentShader);
	
	if (!_shaderProgram->isValid())
	{
		puts("Cannot create shader program!");
		return false;
	}

	_camera.setPosition({0.f, 0.f, 3.f});


	_player.init();

	_chunk.init();

	return true;
}

void Game::run()
{
	using namespace std::chrono_literals;

	while (!glfwWindowShouldClose(_window))
	{
		update();

		glClearColor(0.49f, 0.67f, 0.98f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		_shaderProgram->use();

		_shaderProgram->setUniform("view", _camera.getViewMatrix());
		_shaderProgram->setUniform("projection", _camera.getProjectionMatrix({ ScreenWidth, ScreenHeight }));

		render();

		glfwSwapBuffers(_window);
		glfwPollEvents();

		std::this_thread::sleep_for(10ms);
	}
}

void Game::update()
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, true);
	}

	_player.update(_window);
}

void Game::render()
{
	_chunk.draw(*_shaderProgram);
}
