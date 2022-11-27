#include "GameObjectManager.h"
#include "AGameObject.h"

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager::GameObjectManager() :
	gameObjectList{ObjectList()},
	gameObjectTable{ObjectTable()} {}

GameObjectManager::~GameObjectManager()
{
	for (size_t i = 0; i < this->gameObjectList.size(); i++)
	{
		this->destroyObject(this->gameObjectList[i]);
	}
}

void GameObjectManager::initialize()
{
	if (instance == nullptr)
	{
		instance = new GameObjectManager();
	}
}

void GameObjectManager::terminate()
{
	delete instance;
}

GameObjectManager* GameObjectManager::getInstance()
{
	return instance;
}

void GameObjectManager::destroyObject(AGameObject* gameObject)
{
	const AGameObject* gameObjectToDestroy = this->removeObject(gameObject);

	if (gameObjectToDestroy == nullptr)
	{
		return;
	}

	// TODO: Detach all components of this game object

	delete gameObjectToDestroy;
}

void GameObjectManager::destroyObjectByName(const std::string_view name)
{
	AGameObject* gameObjectToDestroy = findObjectByName(name);
	gameObjectToDestroy              = this->removeObject(gameObjectToDestroy);

	if (gameObjectToDestroy == nullptr)
	{
		return;
	}

	// TODO: Detach all components of this game object

	delete gameObjectToDestroy;
}

AGameObject* GameObjectManager::findObjectByName(const std::string_view name) const
{
	if (!this->hasObject(name.data()))
	{
		return nullptr;
	}

	return this->gameObjectTable.at(name.data());
}

ObjectList GameObjectManager::getAllObjects()
{
	return this->gameObjectList; // Assume this copies the list. May refactor if not.
}

ComponentList GameObjectManager::getGameObjectComponentList(const AGameObject* gameObject)
{
	ComponentList foundComponentList = ComponentList();
	if (this->gameObjectComponentMap.contains(gameObject->Name))
	{
		for (size_t i = 0; i < this->gameObjectComponentMap[gameObject->Name].size(); i++)
		{
			foundComponentList.push_back(this->gameObjectComponentMap[gameObject->Name][i]);
		}
	}

	return foundComponentList;
}

bool GameObjectManager::hasObject(const std::string_view name) const
{
	return this->gameObjectTable.contains(name.data());
}

bool GameObjectManager::hasComponent(const AGameObject* gameObject,
                                     std::string_view componentTypeName)
{
	if (!this->gameObjectComponentMap.contains(gameObject->Name))
	{
		return false;
	}

	if (!this->componentMap.contains(componentTypeName.data()))
	{
		return false;
	}

	for (const auto* c : gameObjectComponentMap[gameObject->Name])
	{
		if (c->getName() == componentTypeName.data())
		{
			return true;
		}
	}
	return false;
}

AComponent* GameObjectManager::getComponent(const AGameObject* gameObject,
                                            std::string_view componentTypeName)
{
	if (!this->hasComponent(gameObject, componentTypeName))
	{
		return nullptr;
	}

	int foundIndex = -1;
	for (size_t i = 0; i < this->gameObjectComponentMap[gameObject->Name].size(); i++)
	{
		if (this->gameObjectComponentMap[gameObject->Name][i]->getName() == componentTypeName.data())
		{
			foundIndex = (int)i;
		}
	}

	if (foundIndex == -1)
	{
		return nullptr;
	}

	return this->gameObjectComponentMap[gameObject->Name][foundIndex];
}

AComponent* GameObjectManager::attachComponent(const AGameObject* gameObject,
                                               AComponent** component)
{
	AComponent* newComponent = this->getComponent(gameObject, (*component)->getName());

	if (newComponent != nullptr)
	{
		return newComponent;
	}

	newComponent = *component;

	if (!this->gameObjectComponentMap.contains(gameObject->Name))
	{
		this->gameObjectComponentMap[gameObject->Name] = ComponentList();
	}

	this->gameObjectComponentMap[gameObject->Name].push_back(newComponent);

	if (!this->componentMap.contains((*component)->getName()))
	{
		this->componentMap[(*component)->getName()] = ComponentList();
	}

	this->componentMap[(*component)->getName()].emplace_back(newComponent);

	return newComponent;
}

void GameObjectManager::detachComponent(const AGameObject* gameObject,
                                        const AComponent* component)
{
	AComponent* componentToDelete = this->getComponent(gameObject, component->getName());

	if (componentToDelete == nullptr)
	{
		return;
	}

	// Delete in GameObjectComponentList
	ComponentList& gameObjectComponentList = this->gameObjectComponentMap[gameObject->Name];
	int foundComponentIndex                = -1;
	for (size_t i = 0; i < gameObjectComponentList.size(); i++)
	{
		if (gameObjectComponentList[i]->getName() == component->getName())
		{
			foundComponentIndex = i;
		}
	}
	gameObjectComponentList.erase(gameObjectComponentList.begin() + foundComponentIndex);
	gameObjectComponentList.shrink_to_fit();
	if (gameObjectComponentList.empty())
	{
		this->gameObjectComponentMap.erase(gameObject->Name);
	}

	// Delete in ComponentList
	ComponentList& componentList = this->componentMap[componentToDelete->getName()];
	foundComponentIndex          = -1;
	for (size_t i = 0; i < componentList.size(); i++)
	{
		if (componentList[i]->getOwner().Name == gameObject->Name)
		{
			foundComponentIndex = (int)i;
		}
	}

	componentList.erase(componentList.begin() + foundComponentIndex);
	componentList.shrink_to_fit();
	if (componentList.empty())
	{
		this->componentMap.erase(componentToDelete->getName());
	}

	delete componentToDelete;
}

AGameObject* GameObjectManager::addObject(AGameObject* gameObject)
{
	if (this->hasObject(gameObject->Name))
	{
		return this->gameObjectTable[gameObject->Name];
	}

	AGameObject* gameObjectToAdd                 = gameObject;
	this->gameObjectTable[gameObjectToAdd->Name] = gameObjectToAdd;
	this->gameObjectList.push_back(gameObjectToAdd);
	return gameObjectToAdd;
}

AGameObject* GameObjectManager::removeObject(AGameObject* gameObject)
{
	if (!this->hasObject(gameObject->Name))
	{
		return nullptr;
	}

	AGameObject* gameObjectToRemove = gameObject;

	this->gameObjectTable.erase(gameObjectToRemove->Name);

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++)
	{
		if (this->gameObjectList[i]->Name == gameObjectToRemove->Name)
		{
			index = i;
			break;
		}
	}
	this->gameObjectList.erase(this->gameObjectList.begin() + index);
	this->gameObjectList.shrink_to_fit();

	return gameObjectToRemove;
}

String GameObjectManager::getNewGameObjectName(std::string_view name) const
{
	int counter = 0;
	for (const auto* gameObject : this->gameObjectList)
	{
		if (gameObject->Name == name)
		{
			counter++;
		}
	}

	String newName = name.data();
	if (counter > 0)
	{
		newName = std::vformat("{0}_{1}", std::make_format_args(name.data(), counter));
	}
	return newName;
}

// void GameObjectManager::updateAll()
// {
// 	for(int i = 0; i < this->GameObjectList.size(); i++)
// 	{
// 		this->GameObjectList[i]->update(EngineTime::getDeltaTime());
// 	}
// }
//
// void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
// {
// 	for(int i = 0; i < this->GameObjectList.size(); i++)
// 	{
// 		this->GameObjectList[i]->draw(viewportWidth, viewportHeight, this->vertexShader, this->PixelShader);
// 	}
// }

// void GameObjectManager::setSelectedObject(String name)
// {
// 	this->setSelectedObject(this->GameObjectTable.at(name));
// }
//
// void GameObjectManager::setSelectedObject(AGameObject* gameObject)
// {
// 	this->SelectedObject = gameObject;
// }
//
// AGameObject* GameObjectManager::getSelectedObject()
// {
// 	return this->SelectedObject;
// }

// Camera* GameObjectManager::createGameCamera()
// {
// 	Camera* GameCamera               = new Camera("GameCamera");
// 	GameCamera->transform().Position = Vector3D(0.0f, 1.0f, -2.0f);
// 	this->addObject(GameCamera);
// 	return GameCamera;
// }

// int GameObjectManager::activeObjects() const
// {
// 	return this->gameObjectList.size();
// }
