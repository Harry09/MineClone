#include "Player.hpp"

#include "Game.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Camera.hpp"
#include "Graphics/ShaderProgram.hpp"
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

	// top
	_highlighter[0] =  Vertex{ { -0.501f, 0.501f, -0.501f } };
	_highlighter[1] =  Vertex{ {  0.501f, 0.501f, -0.501f } };

	_highlighter[2] =  Vertex{ {  0.501f, 0.501f, -0.501f } };
	_highlighter[3] =  Vertex{ {  0.501f, 0.501f,  0.501f } };

	_highlighter[4] =  Vertex{ {  0.501f, 0.501f,  0.501f } };
	_highlighter[5] =  Vertex{ { -0.501f, 0.501f,  0.501f } };

	_highlighter[6] =  Vertex{ { -0.501f, 0.501f,  0.501f } };
	_highlighter[7] =  Vertex{ { -0.501f, 0.501f, -0.501f } };

	// bottom
	_highlighter[8] =  Vertex{ { -0.501f, -0.501f, -0.501f } };
	_highlighter[9] =  Vertex{ {  0.501f, -0.501f, -0.501f } };

	_highlighter[10] = Vertex{ {  0.501f, -0.501f, -0.501f } };
	_highlighter[11] = Vertex{ {  0.501f, -0.501f,  0.501f } };

	_highlighter[12] = Vertex{ {  0.501f, -0.501f,  0.501f } };
	_highlighter[13] = Vertex{ { -0.501f, -0.501f,  0.501f } };

	_highlighter[14] = Vertex{ { -0.501f, -0.501f,  0.501f } };
	_highlighter[15] = Vertex{ { -0.501f, -0.501f, -0.501f } };

	// poles
	_highlighter[16] = Vertex{ { -0.501f, -0.501f, -0.501f } };
	_highlighter[17] = Vertex{ { -0.501f,  0.501f, -0.501f } };

	_highlighter[18] = Vertex{ {  0.501f, -0.501f, -0.501f } };
	_highlighter[19] = Vertex{ {  0.501f,  0.501f, -0.501f } };

	_highlighter[20] = Vertex{ {  0.501f, -0.501f,  0.501f } };
	_highlighter[21] = Vertex{ {  0.501f,  0.501f,  0.501f } };

	_highlighter[22] = Vertex{ { -0.501f, -0.501f,  0.501f } };
	_highlighter[23] = Vertex{ { -0.501f,  0.501f,  0.501f } };
}

void Player::update(GLFWwindow* window)
{
	_drawHighlighter = false;

	Ray ray(_camera.getPosition(), _camera.getRotation());

	static bool mouseClicked = false;

	while (ray.length() < 6)
	{
		ray.step(0.1f);

		auto pos = glm::ivec3(glm::round(ray.getEnd()));

		auto block = _world.getBlock(pos);

		if (block != nullptr)
		{
			_highlighter.setPos(pos);

			_drawHighlighter = true;

			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			{
				if (_blockRemoving == false)
				{
					_blockRemoving = true;
					_world.removeBlock(pos);
				}
			}

			break;
		}
	}

	if (_blockRemoving == true)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
		{
			_blockRemoving = false;
		}
	}

	auto rotation = glm::radians(_camera.getRotation());
	auto _cos = cos(rotation.x) * PlayerSpeed;
	auto _tan = tan(rotation.y) * PlayerSpeed;
	auto _sin = sin(rotation.x) * PlayerSpeed;

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

void Player::drawGrid(ShaderProgram& shaderProgram)
{
	if (_drawHighlighter)
	{
		glLineWidth(2.f);
		_highlighter.draw(shaderProgram);
	}
}
