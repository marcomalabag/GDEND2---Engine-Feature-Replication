#pragma once
#include <string>
#include <unordered_map>

#include <vector>
#include "GameObject/AGameObject.h"


typedef std::string String;
typedef std::vector<AGameObject*> ObjectList;
typedef std::unordered_map<String, AGameObject*> HashTable;
class Camera;
class GameObjectManager final
{
public:
	enum PrimitiveType
	{
		CUBE,
		PLANE,
		SPHERE,
		CYLINDER
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	ObjectList getAllObjects();
	int activeObjects();
	// void updateAll();
	// void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(String name);
	void setSelectedObject(String name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();
	Camera* createGameCamera();

	GameObjectManager(const GameObjectManager&) = delete;

	GameObjectManager& operator=(const GameObjectManager&) = delete;

	GameObjectManager(GameObjectManager&&) noexcept = delete;

	GameObjectManager& operator=(GameObjectManager&&) noexcept = delete;
	
private:
	static GameObjectManager* sharedInstance;

	GameObjectManager();
	~GameObjectManager();
	
	AGameObject* SelectedObject;
	ObjectList GameObjectList;
	HashTable GameObjectTable;

	int cubeCounter = 0;
	int sphereCounter = 0;
	int cylinderCounter = 0;
	int planeCounter = 0;
};

