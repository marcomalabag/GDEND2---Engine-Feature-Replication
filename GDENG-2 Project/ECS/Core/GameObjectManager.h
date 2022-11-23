#pragma once
#include <string>
#include <unordered_map>

#include <vector>
#include "AGameObject.h"
#include "AComponent.h"


using String =  std::string;
using EntityID = String;

using ObjectList = std::vector<AGameObject*>;
using ObjectTable = std::unordered_map<String, AGameObject*>;

using ComponentList = std::vector<AComponent*>;
using ComponentTable = std::unordered_map<String, AComponent*>;

class Camera;
class GameObjectManager final
{
public:
	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	void addObject(AGameObject* gameObject);

	template <typename GameObjectType, typename... Args>
	GameObjectType* createObject(std::string_view name = "GameObject", Args&&...args);

	void destroyObject(const AGameObject* gameObject);
	void destroyObjectByName(String name);

	bool hasObject(std::string_view name) const;
	AGameObject* findObjectByName(std::string_view name) const;

	ObjectList getAllObjects();

	// This works if there is no flag for gameObjects for active or inactiveness
	int activeObjects() const;
	
	// Not sure if this should be here
	// void setSelectedObject(String name);
	// void setSelectedObject(AGameObject* gameObject);
	// AGameObject* getSelectedObject();

	GameObjectManager(const GameObjectManager&)                = delete;
	GameObjectManager& operator=(const GameObjectManager&)     = delete;
	GameObjectManager(GameObjectManager&&) noexcept            = delete;
	GameObjectManager& operator=(GameObjectManager&&) noexcept = delete;

private:
	static GameObjectManager* sharedInstance;

	GameObjectManager();
	~GameObjectManager();

	String getNewGameObjectName(std::string_view name) const;

	// Not sure if this should be here
	// AGameObject* SelectedObject;

	ObjectList gameObjectList;
	ObjectTable gameObjectTable;

	std::unordered_map<EntityID, RenderComponent*> componentMap;
	std::vector<RenderComponent*> componentList;
};

template <typename GameObjectType, typename ... Args>
GameObjectType* GameObjectManager::createObject(const std::string_view name, Args&&... args)
{
	String newGameObjectName = getNewGameObjectName(name);

	GameObjectType* newGameObject = new GameObjectType(newGameObjectName,
	                                               std::forward<Args>(args)...);

	this->addObject((AGameObject*)newGameObject);

	return newGameObject;
}
