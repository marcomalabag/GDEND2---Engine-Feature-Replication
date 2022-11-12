#pragma once
#include "GameObject/CameraMovement.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void init(unsigned int screenWidth,
									   unsigned int screenHeight);
	static void destroy();

	void update();

	Framebuffer* getFramebuffer() const;

	Matrix4x4 getSceneCameraViewMatrix();

	SceneCameraHandler(const SceneCameraHandler&)                = delete;
	SceneCameraHandler& operator=(const SceneCameraHandler&)     = delete;
	SceneCameraHandler(SceneCameraHandler&&) noexcept            = delete;
	SceneCameraHandler& operator=(SceneCameraHandler&&) noexcept = delete;

private:
	SceneCameraHandler(unsigned int screenWidth,
	                   unsigned int screenHeight);
	~SceneCameraHandler();

	CameraMovement* editorCamera   = nullptr;
	Framebuffer* cameraFramebuffer = nullptr;

	static SceneCameraHandler* instance;
};
