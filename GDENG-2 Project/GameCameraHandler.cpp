#include "GameCameraHandler.h"

#include "EngineTime.h"
#include "GameObject/GameObjectManager.h"

GameCameraHandler* GameCameraHandler::instance = nullptr;

GameCameraHandler::GameCameraHandler(unsigned int screenWidth,
                                     unsigned int screenHeight)
{
	FramebufferProfile cameraFramebufferProfile;
	cameraFramebufferProfile.Width  = screenWidth;
	cameraFramebufferProfile.Height = screenHeight;
	this->cameraFramebuffer         = new Framebuffer(cameraFramebufferProfile,
	                                                  &GraphicsEngine::getInstance()->getDevice());
	this->gameCamera = new CameraMovement("GameCamera");
}

GameCameraHandler* GameCameraHandler::getInstance()
{
	return instance;
}

void GameCameraHandler::initialize(unsigned int screenWidth,
                                   unsigned int screenHeight)
{
	instance = new GameCameraHandler(screenWidth,
	                                 screenHeight);
}

void GameCameraHandler::destroy()
{
	delete instance;
}

void GameCameraHandler::update()
{
	this->gameCamera->update(EngineTime::getDeltaTime());
}

Framebuffer* GameCameraHandler::getFramebuffer() const
{
	return this->cameraFramebuffer;
}

Matrix4x4 GameCameraHandler::getGameCameraViewMatrix()
{
	return this->gameCamera->getViewMatrix();
}

void GameCameraHandler::initializeGameCamera()
{
	this->gameCamera = GameObjectManager::getInstance()->createGameCamera();
}

Camera* GameCameraHandler::getGameCameraInstance()
{
	return this->gameCamera;
}

GameCameraHandler::~GameCameraHandler()
{
}
