#pragma once
#include "EngineTime.h"
#include "GameObjectManager.h"
#include "GameCamera.h"

class GameCameraHandler
{
public:
	static GameCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getSceneCameraViewMatrix();
	void initializeGameCamera();
	GameCamera* getGameCameraInstance();

private:
	GameCameraHandler();
	~GameCameraHandler();
	GameCameraHandler(GameCameraHandler const&) {};
	GameCameraHandler& operator=(GameCameraHandler const&) {};
	static GameCameraHandler* sharedInstance;

	GameCamera* gameCamera = nullptr;

};

