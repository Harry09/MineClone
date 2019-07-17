#include "Player.hpp"

#include "Game.hpp"

#include <GLFW/glfw3.h>

Player::Player(Camera& camera)
	: _camera(camera)
{


}

void Player::init()
{
	glfwSetCursorPosCallback(Game::get()->getWindow(), [](GLFWwindow* window, double x, double y) {
		auto game = Game::get();
		auto& camera = game->getCamera();

		constexpr float sensitivity = 0.1f;

		auto offset = game->getCursorOffset({ x, y }) * sensitivity;

		camera.rotate(offset);
	});

}

void Player::update(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		_camera.move({ 0.f, 0.f, -PlayerSpeed });
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		_camera.move({ 0.f, 0.f, PlayerSpeed });
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		_camera.move({ -PlayerSpeed, 0.f, 0.f });
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		_camera.move({ PlayerSpeed, 0.f, 0.f });
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		_camera.move({ 0.f, PlayerSpeed, 0.f });
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		_camera.move({ 0.f, -PlayerSpeed, 0.f });
}
