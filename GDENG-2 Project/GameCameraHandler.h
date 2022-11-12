#pragma once
#include "GameObject/Camera.h"

class GameCameraHandler final
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

