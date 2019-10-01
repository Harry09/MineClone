#pragma once
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/Texture.hpp"

class ShaderProgram;

class Cursor
{
private:
	Texture _cursorTex;
	VertexBuffer _cursor{ 4, PrimitiveType::Lines };
    
public:
    Cursor();
	~Cursor() = default;

	void init();

    void drawHud(ShaderProgram& hudShader);
};
