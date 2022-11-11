#pragma once
#include <unordered_map>
#include <vector>

#include "Debug.h"
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "System/SystemHandler.h"

class AComponent;

//Remember:
//GameObject is an ID
//Components are Data
//Systems are DataProcessors

class AGameObject
{
public:
	AGameObject(std::string_view name);

	virtual ~AGameObject();

	template <typename T, typename... Args>
	T& attachComponent(Args&&... args);

	template <typename T>
	void detachComponent();

	template <class T>
	T* getComponent();

	virtual void update(float deltaTime) = 0;

	virtual void draw(int width,
	                  int height,
	                  VertexShader* vertexshader,
	                  PixelShader* pixelshader) = 0;

	void setPosition(float x,
	                 float y,
	                 float z);

	void setPosition(Vector3D pos);

	Vector3D getLocalPosition();

	void setScale(float x,
	              float y,
	              float z);

	void setScale(Vector3D scale);

	Vector3D getLocalScale();

	void setRotation(float x,
	                 float y,
	                 float z);

	void setRotation(Vector3D rot);

	void setRotationX(float x);

	void setRotationY(float y);

	void setRotationz(float z);

	Vector3D getLocalRotation();

	// TODO: What to do for copying
	// Idea is that all component's data will be copied
	AGameObject(const AGameObject&) = delete;

	AGameObject& operator=(const AGameObject& v) = delete;

	AGameObject(AGameObject&&) noexcept = delete;

	AGameObject& operator=(AGameObject&&) noexcept = delete;

	std::string Name;

protected:
	Vector3D Position;

	Vector3D Scale;

	Vector3D Rotation;
};

template <typename T, typename ... Args>
T& AGameObject::attachComponent(Args&&... args)
{
	T* component = new T(std::forward<Args>(args)...);
	return SystemHandler::getInstance().registerComponent<T>(*this, *component);
}

template <typename T>
void AGameObject::detachComponent()
{
	SystemHandler::getInstance().deregisterComponent<T>(*this);
}

template <class T>
T* AGameObject::getComponent()
{
	return SystemHandler::getInstance().getComponent<T>(*this);
}
