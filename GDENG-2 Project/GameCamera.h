#pragma once
#include "Camera.h"
#include <string>

class GameCamera: public Camera
{
public:
	GameCamera(string name);
	void draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader) override;
	void update(float deltaTime) override;
	~GameCamera();
};

