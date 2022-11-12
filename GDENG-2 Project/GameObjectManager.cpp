#include "GameObjectManager.h"
#include "EngineTime.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
	this->SelectedObject = NULL;
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

AGameObject* GameObjectManager::findObjectByName(String name)
{
	return this->GameObjectTable.at(name);
}

ObjectList GameObjectManager::getAllObjects()
{
	return this->GameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->GameObjectList.size();
}

void GameObjectManager::updateAll()
{
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->update(EngineTime::getDeltaTime());
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		this->GameObjectList[i]->draw(viewportWidth, viewportHeight, this->vertexShader, this->PixelShader);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	this->GameObjectTable[gameObject->Name] = gameObject;
	this->GameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	// GraphicsEngine::getInstance()->compileVertexShader(L"Assets/VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	// this->vertexShader = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	// if(type == PrimitiveType::CUBE)
	// {
	// 	String cubename;
	// 	if(this->cubeCounter == 0)
	// 	{
	// 		cubename = "Cube";
	// 	}
	// 	else
	// 	{
	// 		String number = "(" + std::to_string(this->cubeCounter) + ")";
	// 		cubename = "Cube" + number;
	// 	}
	// 	Cube* cube = new Cube(cubename, shader_byte_code, size_shader);
	// 	cube->setPosition(0.0f, 1.0f, 0.0f);
	// 	cube->setScale(1.0f, 1.0f, 1.0f);
	// 	this->addObject(cube);
	// 	this->cubeCounter++;
	// }
	// else if (type == PrimitiveType::PLANE)
	// {
	// 	String planename;
	// 	if (this->planeCounter == 0)
	// 	{
	// 		planename = "Plane";
	// 	}
	// 	else
	// 	{
	// 		String number = "(" + std::to_string(this->planeCounter) + ")";
	// 		planename = "Plane" + number;
	// 	}
	// 	Plane* plane = new Plane(planename, shader_byte_code, size_shader);
	// 	plane->setPosition(0.0f, 1.0f, 0.0f);
	// 	plane->setScale(1.0f, 1.0f, 1.0f);
	// 	this->addObject(plane);
	// 	this->planeCounter++;
	// }
	// else if (type == PrimitiveType::CYLINDER)
	// {
	// 	String cylindername;
	// 	if (this->cylinderCounter == 0)
	// 	{
	// 		cylindername = "Cylinder";
	// 	}
	// 	else
	// 	{
	// 		String number = "(" + std::to_string(this->cylinderCounter) + ")";
	// 		cylindername = "Cylinder" + number;
	// 	}
	// 	Cylinder* cylinder = new Cylinder(cylindername, shader_byte_code, size_shader);
	// 	cylinder->setPosition(0.0f, 1.0f, 0.0f);
	// 	cylinder->setScale(1.0f, 1.0f, 1.0f);
	// 	this->addObject(cylinder);
	// 	this->cylinderCounter++;
	// }
	// else if (type == PrimitiveType::SPHERE)
	// {
	// 	String spherename;
	// 	if (this->sphereCounter == 0)
	// 	{
	// 		spherename = "Sphere";
	// 	}
	// 	else
	// 	{
	// 		String number = "(" + std::to_string(this->sphereCounter) + ")";
	// 		spherename = "Sphere" + number;
	// 	}
	// 	Sphere* sphere = new Sphere(spherename, shader_byte_code, size_shader);
	// 	sphere->setPosition(0.0f, 1.0f, 0.0f);
	// 	sphere->setScale(1.0f, 1.0f, 1.0f);
	// 	this->addObject(sphere);
	// 	this->sphereCounter++;
	// }
	//
	// GraphicsEngine::getInstance()->releaseCompiledShader();
	// GraphicsEngine::getInstance()->compilePixelShader(L"Assets/PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	// this->PixelShader = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	//
	//
	// GraphicsEngine::getInstance()->releaseCompiledShader();
	
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->GameObjectTable.erase(gameObject->Name);
	int index = -1;
	for(int i = 0; i < this->GameObjectList.size(); i++)
	{
		if(this->GameObjectList[i]->Name == gameObject->Name)
		{
			index = i;
			this->GameObjectList.erase(this->GameObjectList.begin() + index);
			break;
		}
	}
}

void GameObjectManager::deleteObjectByName(String name)
{
	this->deleteObject(this->GameObjectTable.at(name));
}

void GameObjectManager::setSelectedObject(String name)
{
	this->setSelectedObject(this->GameObjectTable.at(name));
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->SelectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->SelectedObject;
}

Camera* GameObjectManager::createGameCamera()
{
	Camera* GameCamera = new Camera("GameCamera");
	GameCamera->setPosition(0.0f, 1.0f, -2.0f);
	this->addObject(GameCamera);
	return GameCamera;
}

GameObjectManager::~GameObjectManager()
{
	delete this->SelectedObject;
	
}

