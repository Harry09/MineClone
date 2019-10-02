#include "Cursor.hpp"

void Cursor::init()
{
	_cursor.scale(glm::vec3{ 0.005f });

	_cursor[0] = Vertex{ glm::vec3 { -0.5f, 0.f,  0.f } };
	_cursor[1] = Vertex{ glm::vec3 {  0.5f, 0.f,  0.f } };
	_cursor[2] = Vertex{ glm::vec3 {  0.f,  0.5f, 0.f } };
	_cursor[3] = Vertex{ glm::vec3 {  0.f, -0.5f, 0.f } };
}

void Cursor::drawHud(ShaderProgram& hudShader)
{
	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	glLineWidth(3.f);
	_cursor.draw(hudShader);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

