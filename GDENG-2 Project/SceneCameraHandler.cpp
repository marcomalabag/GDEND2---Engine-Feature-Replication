#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::instance = nullptr;

SceneCameraHandler::SceneCameraHandler(unsigned int screenWidth,
                                       unsigned int screenHeight)
{
	FramebufferProfile cameraFramebufferProfile;
	cameraFramebufferProfile.Width  = screenWidth;
	cameraFramebufferProfile.Height = screenHeight;
	this->cameraFramebuffer         = new Framebuffer(cameraFramebufferProfile,
	                                                  &GraphicsEngine::getInstance()->getDevice());
	this->editorCamera = new CameraMovement("EditorCamera");
}

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return instance;
}

void SceneCameraHandler::init(unsigned int screenWidth,
                              unsigned int screenHeight)
{
	instance = new SceneCameraHandler(screenWidth,
	                                  screenHeight);
}

void SceneCameraHandler::destroy()
{
	delete instance;
}

void SceneCameraHandler::update()
{
	this->editorCamera->update(EngineTime::getDeltaTime());
}

Framebuffer* SceneCameraHandler::getFramebuffer() const
{
	return this->cameraFramebuffer;
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return this->editorCamera->getViewMatrix();
}

SceneCameraHandler::~SceneCameraHandler()
{
	delete this->editorCamera;
}
