#pragma once

#include "Types.hpp"

class Camera;

class FrustumView
{
private:
	Camera& _camera;
	glm::vec2 _spherePos{ 0.f };

public:
	FrustumView(Camera& camera);

	void update();

	bool isPointInFOV(const coords::WorldPos& worldPos) const;
	bool isBoxInFOV(const coords::WorldPos& start, const glm::ivec3& size) const;
};