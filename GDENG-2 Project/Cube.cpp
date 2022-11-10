#include "Cube.h"

#include "RenderComponent.h"

struct CubeVertex
{
	Vector3D position;
};

Cube::Cube(std::string name, void* shaderByteCode, size_t sizeShader):AGameObject(name)
{
	CubeVertex* vertex_list = new CubeVertex[]
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    },
		{Vector3D(-0.5f,0.5f,-0.5f),    },
		{ Vector3D(0.5f,0.5f,-0.5f),   },
		{ Vector3D(0.5f,-0.5f,-0.5f),      },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),     },
		{ Vector3D(0.5f,0.5f,0.5f),     },
		{ Vector3D(-0.5f,0.5f,0.5f),    },
		{ Vector3D(-0.5f,-0.5f,0.5f),      }
	};

	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[3] {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	RenderData* renderData = new RenderData();
	renderData->vertices = vertex_list;
	renderData->vertexCount = sizeof(vertex_list);
	renderData->vertexSize = sizeof(vertex);
	renderData->vertexLayout = layout;
	renderData->vertexLayoutElementCount = 1ULL;
	renderData->indices = nullptr;
	renderData->indexCount = 0;
	
	this->attachComponent<RenderComponent>(*this, );
	
	this->verterbuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	this->verterbuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	UINT size_list = ARRAYSIZE(vertex_list);

	this->indexbuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->indexbuffer->load(index_list, size_index_list);
	constant cc;
	cc.time = 0;
	this->constantbuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	this->constantbuffer->load(&cc, sizeof(constant));
	
}

void Cube::update(float deltaTime)
{
	
	
}


void Cube::draw(int width, int height, VertexShader* vertexshader, PixelShader* pixelshader)
{
	constant cc;
	Matrix4x4 temp;
	
	this->Summation.setIdentity();
	this->translate.setIdentity();
	this->Scale.setIdentity();

	translate.setTranslation(this->getLocalPosition());
	Scale.setScale(this->getLocalScale());
	rotation = Vector3D(this->getLocalRotation());

	this->RotationZ.setIdentity();
	this->RotationZ.setRotationZ(rotation.z);

	this->RotationF.setIdentity();
	this->RotationF.setRotationX(rotation.x);

	this->RotationGl.setIdentity();
	this->RotationGl.setRotationY(rotation.y);

	this->RotationTotal.setIdentity();
	this->RotationTotal = this->RotationTotal.mulMatrix(RotationF.mulMatrix(RotationGl.mulMatrix(RotationZ)));
	this->Summation = this->Summation.mulMatrix(Scale.mulMatrix(this->RotationTotal));
	this->Summation = this->Summation.mulMatrix(this->translate);
	cc.world = this->Summation;

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.view = cameraMatrix;

	/*
	cc.projection.setOrthoLH
	(
		width / 300.0f,
		height / 300.0f,
		-4.0f,
		4.0f
	);
	*/
	float aspectRatio = (float)width / (float)height;

	cc.projection.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	this->constantbuffer->update(GraphicsEngine::getInstance()->getDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getDeviceContext()->setConstantBuffer(vertexshader, this->constantbuffer);
	GraphicsEngine::getInstance()->getDeviceContext()->setConstantBuffer(pixelshader, this->constantbuffer);

	GraphicsEngine::getInstance()->getDeviceContext()->setVertexShader(vertexshader);
	GraphicsEngine::getInstance()->getDeviceContext()->setPixelShader(pixelshader);

	GraphicsEngine::getInstance()->getDeviceContext()->setVertexBuffer(this->verterbuffer);
	GraphicsEngine::getInstance()->getDeviceContext()->setIndexBuffer(this->indexbuffer);

	GraphicsEngine::getInstance()->getDeviceContext()->drawIndexedTriangleList(this->indexbuffer->getSizeIndexList(), 0, 0);

	this->oldDelta = this->newDelta;
	this->newDelta += this->ticks;

	this->deltaTime = (oldDelta) ? ((newDelta - oldDelta) / 1000.0f) : 0;
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

Cube::~Cube()
{
	this->constantbuffer->release();
	this->indexbuffer->release();
	this->verterbuffer->release();
	
	AGameObject::~AGameObject();
}
