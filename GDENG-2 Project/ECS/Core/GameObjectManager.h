#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "AComponent.h"

class AGameObject;
class AComponent;

using String = std::string;
using EntityID = String;

using ObjectList = std::vector<AGameObject*>;
using ObjectTable = std::unordered_map<String, AGameObject*>;

using ComponentList = std::vector<AComponent*>;

template <typename ComponentType>
using ComponentTypeList = std::vector<ComponentType*>;

using ComponentTable = std::unordered_map<String, ComponentList>;
using GameObjectComponentTable = std::unordered_map<EntityID, ComponentList>;

class GameObjectManager final
{
public:
	static GameObjectManager* getInstance();
	static void initialize();
	static void terminate();

	//======GAME OBJECTS======//
	template <typename GameObjectType, typename... Args>
	GameObjectType* createObject(std::string_view name = "GameObject", Args&&...args);

	void destroyObject(AGameObject* gameObject);
	void destroyObjectByName(std::string_view name);

	AGameObject* findObjectByName(std::string_view name) const;

	ObjectList getAllObjects();

	//======COMPONENTS======//
	ComponentList getGameObjectComponentList(const AGameObject* gameObject); // Usually for UI Display

	template <typename ComponentType>
	ComponentTypeList<ComponentType> getComponentListOfType();

	GameObjectManager(const GameObjectManager&)                = delete;
	GameObjectManager& operator=(const GameObjectManager&)     = delete;
	GameObjectManager(GameObjectManager&&) noexcept            = delete;
	GameObjectManager& operator=(GameObjectManager&&) noexcept = delete;

private:
	static GameObjectManager* instance;

	GameObjectManager();
	~GameObjectManager();

	//======GAME OBJECTS======//
	bool hasObject(std::string_view name) const;
	AGameObject* addObject(AGameObject* gameObject); // may need to modify stuff
	AGameObject* removeObject(AGameObject* gameObject); // Other code is responsible for destructors

	String getNewGameObjectName(std::string_view name) const;

	//======COMPONENTS======//
	bool hasComponent(const AGameObject* gameObject, std::string_view componentTypeName);

	AComponent* getComponent(const AGameObject* gameObject, std::string_view componentTypeName);

	AComponent* attachComponent(const AGameObject* gameObject,
	                            AComponent** component);

	void detachComponent(const AGameObject* gameObject,
	                     const AComponent* component);

	// Not sure if this should be here
	// AGameObject* SelectedObject;

	ObjectList gameObjectList;
	ObjectTable gameObjectTable;

	GameObjectComponentTable gameObjectComponentMap;
	ComponentTable componentMap;

	friend class AGameObject;
};

template <typename GameObjectType, typename ... Args>
GameObjectType* GameObjectManager::createObject(const std::string_view name, Args&&... args)
{
	String newGameObjectName = getNewGameObjectName(name);

	GameObjectType* newGameObject = new GameObjectType(newGameObjectName,
	                                                   std::forward<Args>(args)...);

	return this->addObject((AGameObject*)newGameObject);
}

template <typename ComponentType>
ComponentTypeList<ComponentType> GameObjectManager::getComponentListOfType()
{
	ComponentTypeList<ComponentType> foundComponentList = ComponentTypeList<ComponentType>();

	if (this->componentMap.contains(ComponentType::getStaticName()))
	{
		for (size_t i = 0; i < this->componentMap[ComponentType::getStaticName()].size(); i++)
		{
			foundComponentList.push_back(this->componentMap[ComponentType::getStaticName()][i]);
		}
	}

	return foundComponentList;
}
