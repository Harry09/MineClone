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
	_player(_world, _renderer.getCamera()),
	_lastCursorPos{ Renderer::ScreenWidth / 2.f, Renderer::ScreenHeight / 2.f }
{
	_inst = this;
}

Game::~Game()
{
}

bool Game::init()
{
	glfwSetFramebufferSizeCallback(_renderer.getWindow(), [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});

	_renderer.getCamera().setPosition({ -3.f, 0.f, 3.f });

	_player.init();
	_world.init();

	return true;
}

void Game::run()
{
	using namespace std::chrono_literals;

	while (!glfwWindowShouldClose(_renderer.getWindow()))
	{
		update();

		glClearColor(0.49f, 0.67f, 0.98f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		drawChunks();

		glfwSwapBuffers(_renderer.getWindow());
		glfwPollEvents();

		std::this_thread::sleep_for(10ms);
	}
}

void Game::update()
{
	if (glfwGetKey(_renderer.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_renderer.getWindow(), true);
	}

	_player.update(_renderer.getWindow());
}

void Game::drawChunks()
{
	auto& chunkShader = _renderer.getChunkShader();
	auto& camera = _renderer.getCamera();

	chunkShader.use();

	chunkShader.setUniform("view", camera.getViewMatrix());
	chunkShader.setUniform("projection", camera.getProjectionMatrix({ Renderer::ScreenWidth, Renderer::ScreenHeight }));

	_world.draw(chunkShader);
}
