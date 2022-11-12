#pragma once
#include "Camera.h"
#include "EngineTime.h"
#include "GameObjectManager.h"

class GameCameraHandler
{
public:
	static GameCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getSceneCameraViewMatrix();
	void initializeGameCamera();
	Camera* getGameCameraInstance();

private:
	GameCameraHandler();
	~GameCameraHandler();
	GameCameraHandler(GameCameraHandler const&) {};
	GameCameraHandler& operator=(GameCameraHandler const&) {};
	static GameCameraHandler* sharedInstance;

	Camera* gameCamera = nullptr;

};

