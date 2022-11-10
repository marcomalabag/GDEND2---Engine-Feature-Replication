#pragma once
#include <unordered_map>
#include <vector>

#include "AComponent.h"
#include "Debug.h"
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AComponent;

class AGameObject
{
public:
	struct vertex
	{
		Vector3D position;

		Vector3D color;

		Vector3D color1;
	};

	_declspec(align(16))
	struct constant
	{
		Matrix4x4 world;

		Matrix4x4 view;

		Matrix4x4 projection;

		unsigned int time;
	};

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
	// To be moved to render component
	// VertexShader* vertex_shader;
	//
	// PixelShader* pixel_shader;

	Vector3D Position;

	Vector3D Scale;

	Vector3D Rotation;

private:
	std::unordered_map<std::string, AComponent*> m_ComponentTable{};

	std::vector<AComponent*> m_ComponentList{};
};

template <typename T, typename ... Args>
T& AGameObject::attachComponent(Args&&... args)
{
	T* component = nullptr;
	if (m_ComponentTable.contains(T::getStaticName()))
	{
		Debug::Log("Attempting to Attach {0} that is already attached to {1}!",
		           T::getStaticName(),
		           Name.c_str());
		component = (T*)m_ComponentTable[T::getStaticName()];
		return *component;
	}

	component = new T(std::forward<Args>(args)...);

	m_ComponentTable[T::getStaticName()] = component;
	m_ComponentList.push_back(component);

	return *component;
}

// There may be issues with components that are dependent on other components
// If that ever occurs
template <typename T>
void AGameObject::detachComponent()
{
	if (!m_ComponentTable.contains(T::getStaticName()))
	{
		return;
	}

	T* component = m_ComponentTable[T::getStaticName()];
	
	m_ComponentTable.erase(T::getStaticName());

	for (size_t i = 0ULL; i < m_ComponentList.size(); ++i)
	{
		if (m_ComponentList[i]->getName() == T::getStaticName())
		{
			m_ComponentList.erase(m_ComponentList.begin() + i);
		}
	}
	
	delete component;
}

template <class T>
T* AGameObject::getComponent()
{
	auto foundComponent = m_ComponentTable.find(T::getStaticName());
	return (foundComponent != m_ComponentTable.end()) ?
		       (T*)foundComponent->second :
		       nullptr;
}
