#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Camera;

class FrustumView
{
private:
	Camera& _camera;
	glm::vec2 _spherePos{ 0.f };

public:
	FrustumView(Camera& camera);

	void update();

	bool isPointInFOV(const glm::ivec3& pos) const;
	bool isBoxInFOV(const glm::ivec3& start, const glm::ivec3& size) const;
};