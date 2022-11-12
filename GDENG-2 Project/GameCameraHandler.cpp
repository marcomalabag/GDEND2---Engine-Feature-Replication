#include "GameCameraHandler.h"

GameCameraHandler* GameCameraHandler::sharedInstance = NULL;

GameCameraHandler::GameCameraHandler()
{

}


GameCameraHandler* GameCameraHandler::getInstance()
{
	return sharedInstance;
}

void GameCameraHandler::initialize()
{
	sharedInstance = new GameCameraHandler();
}

void GameCameraHandler::destroy()
{
	delete sharedInstance;
}

void GameCameraHandler::update()
{
	this->gameCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 GameCameraHandler::getSceneCameraViewMatrix()
{
	return this->gameCamera->getViewMatrix();
}

void GameCameraHandler::initializeGameCamera()
{
	this->gameCamera = GameObjectManager::getInstance()->createGameCamera();
}

GameCamera* GameCameraHandler::getGameCameraInstance()
{
	return this->gameCamera;
}

GameCameraHandler::~GameCameraHandler()
{
}


