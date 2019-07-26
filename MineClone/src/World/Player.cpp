#include "Player.hpp"

#include "Game.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Camera.hpp"
#include "Ray.hpp"

Player::Player(World& world, Camera& camera)
	: _world(world), _camera(camera)
{
}

void Player::init()
{
	glfwSetCursorPosCallback(Game::get()->getRenderer().getWindow(), [](GLFWwindow* window, double x, double y) {
		auto game = Game::get();
		auto& camera = game->getRenderer().getCamera();

		constexpr float sensitivity = 0.1f;

		auto offset = game->getCursorOffset({ x, y }) * sensitivity;

		camera.rotate(offset);
	});
}

void Player::update(GLFWwindow* window)
{
	auto rotation = glm::radians(_camera.getRotation());
	auto _cos = cos(rotation.x) * PlayerSpeed;
	auto _tan = tan(rotation.y) * PlayerSpeed;
	auto _sin = sin(rotation.x) * PlayerSpeed;

	static bool clicked = false;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		if (!clicked)
		{
			Ray ray(_camera.getPosition(), _camera.getRotation());

			while (ray.length() < 6)
			{
				ray.step(0.1f);

				auto pos = glm::ivec3(ray.getEnd());

				auto block = _world.getBlock(pos);

				if (block != nullptr)
				{
					_world.removeBlock(block->getWorldPosition());
					printf("End %d %d %d\n", pos.x, pos.y, pos.z);
					break;
				}

			}

			printf("\n");

			clicked = true;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
	{
		if (clicked)
		{
			clicked = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		_camera.move({  _cos, _tan,  _sin });
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		_camera.move({ -_cos, -_tan, -_sin });
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		_camera.move({  _sin, 0.f, -_cos });
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		_camera.move({ -_sin, 0.f,  _cos });

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		_camera.move({ 0.f,  PlayerSpeed, 0.f });
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		_camera.move({ 0.f, -PlayerSpeed, 0.f });
}
