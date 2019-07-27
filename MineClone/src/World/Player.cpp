#include "Player.hpp"

#include "Game.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Camera.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Blocks/BlockMesh.hpp"
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

	auto blockMesh = getBlockMesh<
		BlockSide::North, 
		BlockSide::East,
		BlockSide::South,
		BlockSide::West,
		BlockSide::Top,
		BlockSide::Bottom>(glm::vec3 { 0.f }, TextureId::None, _world.getTextureAtlas());

	auto mat = _highlighter.getMatrix();
	mat = glm::translate(mat, _highlighterPos);
	_highlighter.setMatrix(mat);

	_highlighter.resize(blockMesh.size());

	_highlighter.setTexture(_world.getTextureAtlas().getTexture());
	_highlighter.setVertices(0, blockMesh.data(), blockMesh.size());
	_highlighter.update();
}

void Player::update(GLFWwindow* window)
{
	_drawHighlighter = false;

	Ray ray(_camera.getPosition(), _camera.getRotation());

	while (ray.length() < 6)
	{
		ray.step(0.1f);

		auto pos = glm::ivec3(glm::round(ray.getEnd()));

		auto block = _world.getBlock(pos);

		if (block != nullptr)
		{
			auto offset = glm::vec3(pos) - _highlighterPos;

			auto mat = _highlighter.getMatrix();
			mat = glm::translate(mat, offset);
			_highlighter.setMatrix(mat);

			_highlighterPos = pos;

			_drawHighlighter = true;

			break;
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

void Player::draw(ShaderProgram& shaderProgram)
{
	if (_drawHighlighter)
	{
		_highlighter.draw(shaderProgram);
	}
}
