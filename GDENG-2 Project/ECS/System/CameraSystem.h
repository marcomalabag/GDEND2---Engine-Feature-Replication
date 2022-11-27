#pragma once
#include <string>
#include <vector>

class AGameObject;
class CameraComponent;

class CameraSystem final
{
public:
	CameraSystem();
	~CameraSystem();

	void registerComponent(CameraComponent* component);

	void deregisterComponent(const AGameObject& gameObject);

	//=====ACTUAL FUNCTIONALITY=====//

	void editorCameraUpdate();

	void gameCameraUpdate();

	CameraSystem(const CameraSystem&)                = delete;
	CameraSystem& operator=(const CameraSystem&)     = delete;
	CameraSystem(CameraSystem&&) noexcept            = delete;
	CameraSystem& operator=(CameraSystem&&) noexcept = delete;

private:
	std::vector<CameraComponent*> componentList;
}; 