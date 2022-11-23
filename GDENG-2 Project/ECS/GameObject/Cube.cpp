#include "Cube.h"

#include "Math/Vector3D.h"
#include "Component/RenderComponent.h"
#include "Graphics/ShaderLibrary.h"

#include "RenderData.h"

struct CubeVertex
{
	Vector3D position;
};

Cube::Cube(const std::string_view name) :
	AGameObject(name)
{
	std::vector<CubeVertex>* vertexList = new std::vector<CubeVertex>{
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f)},
		{Vector3D(-0.5f, 0.5f, -0.5f)},
		{Vector3D(0.5f, 0.5f, -0.5f)},
		{Vector3D(0.5f, -0.5f, -0.5f)},

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f)},
		{Vector3D(0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f, -0.5f, 0.5f)}
	};

	std::vector<D3D11_INPUT_ELEMENT_DESC>* layout = new std::vector<D3D11_INPUT_ELEMENT_DESC>{
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

	std::vector<unsigned int>* indices = new std::vector<unsigned int>{
		//FRONT SIDE
		0,
		1,
		2,
		//FIRST TRIANGLE
		2,
		3,
		0,
		//SECOND TRIANGLE
		//BACK SIDE
		4,
		5,
		6,
		6,
		7,
		4,
		//TOP SIDE
		1,
		6,
		5,
		5,
		2,
		1,
		//BOTTOM SIDE
		7,
		0,
		3,
		3,
		4,
		7,
		//RIGHT SIDE
		3,
		2,
		5,
		5,
		4,
		3,
		//LEFT SIDE
		7,
		6,
		1,
		1,
		0,
		7
	};

	RenderData* renderData               = new RenderData();
	renderData->Vertices                 = vertexList->data();
	renderData->VertexCount              = vertexList->size();
	renderData->VertexSize               = sizeof(CubeVertex);
	renderData->VertexLayout             = layout->data();
	renderData->VertexLayoutElementCount = layout->size();
	renderData->Indices                  = indices->data();
	renderData->IndexCount               = indices->size();

	VertexShader* vertexShader = &ShaderLibrary::getShader<VertexShader>("SolidColor_VS");
	PixelShader* pixelShader   = &ShaderLibrary::getShader<PixelShader>("SolidColor_PS");

	this->attachComponent<RenderComponent>(*this,
	                                       renderData,
	                                       vertexShader,
	                                       pixelShader);
}

Cube::~Cube() = default;
