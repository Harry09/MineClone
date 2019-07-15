#include "Game.hpp"

#include <iostream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Vertex.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/Texture.hpp"

#include "Block.hpp"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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

	glfwSetWindowUserPointer(_window, this);

	glfwSetCursorPos(_window, Game::ScreenWidth / 2.f, Game::ScreenHeight / 2.f);

	_lastCursorPos = { Game::ScreenWidth / 2.f, Game::ScreenHeight / 2.f };

	glfwSetFramebufferSizeCallback(_window, frameBufferSizeCallback);
	glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y) {
		auto game = static_cast<Game*>(glfwGetWindowUserPointer(window));
		auto& camera = game->getCamera();

		constexpr float sensitivity = 0.1f;

		auto offset = game->getCursorOffset({ x, y }) * sensitivity;

		camera.rotate(offset);
	});

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	auto vertexShader = Shader(ShaderType::Vertex, "vertex_shader.glsl");
	auto fragmentShader = Shader(ShaderType::Fragment, "fragment_shader.glsl");

	if (vertexShader.isValid() == false || fragmentShader.isValid() == false)
	{
		puts("Cannot create shaders!");
		return false;
	}

	_shaderProgram = std::make_unique<ShaderProgram>(vertexShader, fragmentShader);


	_block = std::make_unique<Block>();

	_camera.setPosition({0.f, 0.f, 3.f});

	return true;
}

void Game::run()
{
	using namespace std::chrono_literals;

	while (!glfwWindowShouldClose(_window))
	{
		update();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
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

	float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_camera.move({ 0.f, 0.f, -cameraSpeed });
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_camera.move({ 0.f, 0.f, cameraSpeed });
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_camera.move({ -cameraSpeed, 0.f, 0.f });
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_camera.move({ cameraSpeed, 0.f, 0.f });
}

void Game::render()
{
	_block->draw(*_shaderProgram);
}
