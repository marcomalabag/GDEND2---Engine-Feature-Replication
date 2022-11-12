#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "AGameObject.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Sphere.h"
#include "GameCamera.h"



typedef std::string String;
typedef std::vector<AGameObject*> ObjectList;
typedef std::unordered_map<String, AGameObject*> HashTable;

class GameObjectManager
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

	AGameObject* findObjectByName(string name);
	ObjectList getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(string name);
	void setSelectedObject(string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();
	GameCamera* createGameCamera();
	
private:
	static GameObjectManager* sharedInstance;

	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	AGameObject* SelectedObject;
	ObjectList GameObjectList;
	HashTable GameObjectTable;

	int cubeCounter = 0;
	int sphereCounter = 0;
	int cylinderCounter = 0;
	int planeCounter = 0;

	VertexShader* vertexShader;
	PixelShader* PixelShader;
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
};

