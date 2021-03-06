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
	_world(_renderer.getCamera()),
	_lastCursorPos{ _renderer.getCanvasSize() / 2u }
{
	_inst = this;
}

Game::~Game()
{
}

bool Game::init()
{
	_renderer.getCamera().setPosition({ -3.f, 0.f, 3.f });

	_world.init();
	_player.init();

	initHud();

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

		auto& camera = _renderer.getCamera();
		auto& viewMatrix = camera.getViewMatrix();
		auto& projectionMatrix = camera.getProjectionMatrix();


		drawChunks(viewMatrix, projectionMatrix);
		drawHud(projectionMatrix);
		drawGrid(viewMatrix, projectionMatrix);

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
	_world.update();
}

void Game::initHud()
{
	_cursor.init();

	_hudViewMatrix = glm::mat4(1.0f);
	_hudViewMatrix = glm::translate(_hudViewMatrix, glm::vec3(0.0f, 0.0f, -0.1f));
}

void Game::drawChunks(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	auto& chunkShader = _renderer.getChunkShader();
	auto& camera = _renderer.getCamera();

	chunkShader.use();

	chunkShader.setUniform("view", viewMatrix);
	chunkShader.setUniform("projection", projectionMatrix);

	_world.drawChunks(chunkShader);
}

void Game::drawHud(const glm::mat4& projectionMatrix)
{
	auto& hudShader = _renderer.getHudShader();
	auto& camera = _renderer.getCamera();

	hudShader.use();

	hudShader.setUniform("view", _hudViewMatrix);
	hudShader.setUniform("projection", projectionMatrix);

	_cursor.drawHud(hudShader);
}

void Game::drawGrid(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	auto& gridShader = _renderer.getGridShader();
	auto& camera = _renderer.getCamera();

	gridShader.use();

	gridShader.setUniform("view", viewMatrix);
	gridShader.setUniform("projection", projectionMatrix);

	_player.drawGrid(gridShader);

	glLineWidth(1.f);
	_world.drawGrid(gridShader);
}
