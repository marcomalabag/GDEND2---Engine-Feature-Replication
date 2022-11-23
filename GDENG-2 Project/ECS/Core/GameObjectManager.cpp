#include "GameObjectManager.h"

#include "Camera.h"
#include "EngineTime.h"

#include "Component/TransformComponent.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager::GameObjectManager()
{
	this->SelectedObject = nullptr;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::destroy()
{
	delete sharedInstance;
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	this->gameObjectTable[gameObject->Name] = gameObject;
	this->gameObjectList.push_back(gameObject);
}

void GameObjectManager::destroyObject(const AGameObject* gameObject)
{
	if (!hasObject(gameObject->Name))
	{
		return;
	}

	this->gameObjectTable.erase(gameObject->Name);
	
	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++)
	{
		if (this->gameObjectList[i]->Name == gameObject->Name)
		{
			index = i;
			break;
		}
	}
	this->gameObjectList.erase(this->gameObjectList.begin() + index);
	this->gameObjectList.shrink_to_fit();

	// TODO: Detach all components of this game object

	delete gameObject;
}

void GameObjectManager::destroyObjectByName(String name)
{
	AGameObject* gameObject = findObjectByName(name);

	if (gameObject == nullptr)
	{
		return;
	}
	
	this->gameObjectTable.erase(name);
	
	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++)
	{
		if (this->gameObjectList[i]->Name == name)
		{
			index = i;
			break;
		}
	}
	this->gameObjectList.erase(this->gameObjectList.begin() + index);
	this->gameObjectList.shrink_to_fit();

	// TODO: Detach all components of this game object

	delete gameObject;
}

bool GameObjectManager::hasObject(const std::string_view name) const
{
	return this->gameObjectTable.contains(name.data());
}

AGameObject* GameObjectManager::findObjectByName(const std::string_view name) const
{
	if (!this->hasObject(name))
	{
		return nullptr;
	}
	
	return this->gameObjectTable.at(name.data());
}

ObjectList GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects() const
{
	return this->gameObjectList.size();
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

GameObjectManager::~GameObjectManager()
{
	// delete this->SelectedObject;
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
