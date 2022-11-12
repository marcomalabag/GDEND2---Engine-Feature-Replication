#pragma once
#include "GameObject/CameraMovement.h"

class GameCameraHandler final
{
public:
	static GameCameraHandler* getInstance();
	static void initialize(unsigned int screenWidth,
	                       unsigned int screenHeight);
	static void destroy();

	void update();

	Framebuffer* getFramebuffer() const;

	Matrix4x4 getGameCameraViewMatrix();
	void initializeGameCamera();
	Camera* getGameCameraInstance();

	GameCameraHandler(const GameCameraHandler&)                = delete;
	GameCameraHandler& operator=(const GameCameraHandler&)     = delete;
	GameCameraHandler(GameCameraHandler&&) noexcept            = delete;
	GameCameraHandler& operator=(GameCameraHandler&&) noexcept = delete;

private:
	GameCameraHandler(unsigned int screenWidth,
	                  unsigned int screenHeight);
	~GameCameraHandler();

	Camera* gameCamera             = nullptr;
	Framebuffer* cameraFramebuffer = nullptr;

	static GameCameraHandler* instance;
};
