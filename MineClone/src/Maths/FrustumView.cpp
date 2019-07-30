#include "FrustumView.hpp"

#include <glm/trigonometric.hpp>

#include "Graphics/Camera.hpp"

#include "Game.hpp"

FrustumView::FrustumView(Camera& camera)
	: _camera(camera)
{
}

void FrustumView::update()
{
	auto& cameraPos = _camera.getPosition();
	auto& cameraDir = glm::radians(_camera.getRotation());

	auto distance = ((Game::MaxChunkDrawDistance * Chunk::Size) / 2.f) * 0.8f;

	_spherePos.x = cameraPos.x + cos(cameraDir.x) * distance;
	_spherePos.y = cameraPos.z + sin(cameraDir.x) * distance;

}

bool FrustumView::isPointInFOV(const glm::ivec3& pos) const
{
	if (glm::distance(glm::vec2{ pos.x, pos.z }, _spherePos) < (Game::MaxChunkDrawDistance * Chunk::Size) / 2.f)
		return true;

	return false;
}

bool FrustumView::isBoxInFOV(const glm::ivec3& start, const glm::ivec3& size) const
{
	if (isPointInFOV(start))
		return true;

	if (isPointInFOV({ start.x + size.x, start.y, start.z }))
		return true;

	if (isPointInFOV({ start.x, start.y, start.z + size.z }))
		return true;

	if (isPointInFOV(start + size))
		return true;
	
	return false;
}
