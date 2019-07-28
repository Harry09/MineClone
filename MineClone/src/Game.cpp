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
	_lastCursorPos{ Renderer::ScreenWidth / 2.f, Renderer::ScreenHeight / 2.f },
	_cursorTex("cursor.png", true)
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

	_world.init();
	_player.init();

	initCursor();

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
		auto& projectionMatrix = camera.getProjectionMatrix({ Renderer::ScreenWidth, Renderer::ScreenHeight });


		drawChunks(viewMatrix, projectionMatrix);
		drawHud(projectionMatrix);
		drawGrid(viewMatrix, projectionMatrix);

		glfwSwapBuffers(_renderer.getWindow());
		glfwPollEvents();

		std::this_thread::sleep_for(10ms);
	}
}

void Game::initCursor()
{
	_cursor.setTexture(_cursorTex);

	auto mat = _cursor.getMatrix();
	mat = glm::scale(mat, glm::vec3{ 0.005f });
	_cursor.setMatrix(mat);

	_cursor[0] = Vertex{ glm::vec3 { -0.5f, -0.5f, 0.f }, glm::vec3 { 1.f }, glm::vec2 { 0.f, 0.f } };
	_cursor[1] = Vertex{ glm::vec3 { -0.5f,  0.5f, 0.f }, glm::vec3 { 1.f }, glm::vec2 { 0.f, 1.f } };
	_cursor[2] = Vertex{ glm::vec3 {  0.5f,  0.5f, 0.f }, glm::vec3 { 1.f }, glm::vec2 { 1.f, 1.f } };
	_cursor[3] = Vertex{ glm::vec3 {  0.5f, -0.5f, 0.f }, glm::vec3 { 1.f }, glm::vec2 { 1.f, 0.f } };

	_hudViewMatrix = glm::mat4(1.0f);
	_hudViewMatrix = glm::translate(_hudViewMatrix, glm::vec3(0.0f, 0.0f, -0.1f));
}

void Game::update()
{
	if (glfwGetKey(_renderer.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_renderer.getWindow(), true);
	}

	_player.update(_renderer.getWindow());
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

	_cursor.draw(hudShader);
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
