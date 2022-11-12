#include "HalfRenderQuad.h"

#include "RenderData.h"
#include "ShaderLibrary.h"

#include "Math/Color.h"
#include "Math/Vector3D.h"

struct HalfRenderQuadVertex
{
	Vector3D Position;
	Color Color;
};

HalfRenderQuad::HalfRenderQuad() :
	renderData{nullptr},
	vertexShader{nullptr},
	pixelShader{nullptr},
	vertexBuffer{nullptr},
	indexBuffer{nullptr}
{
	HalfRenderQuadVertex* vertices = new HalfRenderQuadVertex[4]
	{
		{Vector3D{-0.5f, -0.5f, 0.0f}, Color(1.0f, 1.0f, 1.0f, 1.0f)},
		{Vector3D{-0.5f, 0.5f, 0.0f}, Color(1.0f, 1.0f, 1.0f, 1.0f)},
		{Vector3D{0.5f, 0.5f, 0.0f}, Color(1.0f, 1.0f, 1.0f, 1.0f)},
		{Vector3D{0.5f, -0.5f, 0.0f}, Color(1.0f, 1.0f, 1.0f, 1.0f)},
	};

	// TODO: Revamp VertexLayout
	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	unsigned int* indices = new unsigned int[6]
	{
		2,
		3,
		0,
		0,
		1,
		2
	};

	renderData                           = new RenderData{};
	renderData->Vertices                 = vertices;
	renderData->VertexCount              = 4;
	renderData->VertexSize               = sizeof(HalfRenderQuadVertex);
	renderData->VertexLayout             = layout;
	renderData->VertexLayoutElementCount = 2U;
	renderData->Indices                  = indices;
	renderData->IndexCount               = 6;
	renderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	ShaderLibrary::add<VertexShader>("GDENG-2 Project/Assets/HalfRenderQuadShader.hlsl");
	ShaderLibrary::add<PixelShader>("GDENG-2 Project/Assets/HalfRenderQuadShader.hlsl");

	vertexShader = &ShaderLibrary::getShader<VertexShader>("HalfRenderQuadShader");

	pixelShader = &ShaderLibrary::getShader<PixelShader>("HalfRenderQuadShader");

	vertexBuffer = new VertexBuffer(*renderData, *vertexShader);

	indexBuffer = new IndexBuffer(*renderData);
}
HalfRenderQuad::~HalfRenderQuad()
{
	delete renderData;

	delete vertexBuffer;

	delete indexBuffer;
}
void HalfRenderQuad::draw() const
{
	GraphicsEngine::getInstance()->getDeviceContext().setVertexShader(*vertexShader);
	GraphicsEngine::getInstance()->getDeviceContext().setPixelShader(*pixelShader);

	GraphicsEngine::getInstance()->getDeviceContext().setVertexBuffer(*vertexBuffer);
	GraphicsEngine::getInstance()->getDeviceContext().setIndexBuffer(*indexBuffer);

	GraphicsEngine::getInstance()->getDeviceContext().setTopology(renderData->Topology);

	GraphicsEngine::getInstance()->getDeviceContext().drawIndexed(indexBuffer->getElementCount(),
																  0,
																  0);
}
