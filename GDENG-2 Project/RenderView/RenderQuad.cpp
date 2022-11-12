#include "RenderQuad.h"

#include "Vector2Da.h"
#include "Vector3D.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderData.h"
#include "ShaderLibrary.h"


struct RenderQuadVertex
{
	Vector3D Position;

	Vector2Da TextureCoordinates;
};

RenderQuad::RenderQuad() :
	renderData{nullptr},
	vertexShader{nullptr},
	pixelShader{nullptr},
	vertexBuffer{nullptr},
	indexBuffer{nullptr},
	textureSampler{nullptr}
{
	RenderQuadVertex* vertices = new RenderQuadVertex[4]
	{
		{Vector3D{-1.0f, -1.0f, 0.0f}, Vector2Da{0.0f, 1.0f}},
		{Vector3D{-1.0f, 1.0f, 0.0f}, Vector2Da{0.0f, 0.0f}},
		{Vector3D{1.0f, 1.0f, 0.0f}, Vector2Da{1.0f, 0.0f}},
		{Vector3D{1.0f, -1.0f, 0.0f}, Vector2Da{1.0f, 1.0f}},
	};

	// TODO: Revamp VertexLayout
	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	uint32_t* indices = new uint32_t[6]
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
	renderData->VertexCount              = sizeof(*vertices);
	renderData->VertexSize               = sizeof(RenderQuadVertex);
	renderData->VertexLayout             = layout;
	renderData->VertexLayoutElementCount = 2U;
	renderData->Indices                  = indices;
	renderData->IndexCount               = sizeof(indices);
	renderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	ShaderLibrary::add<VertexShader>("GDENG-2 Project/Assets/RenderQuadShader.hlsl");
	ShaderLibrary::add<PixelShader>("GDENG-2 Project/Assets/RenderQuadShader.hlsl");

	vertexShader = &ShaderLibrary::getShader<VertexShader>("RenderQuadShader");

	pixelShader = &ShaderLibrary::getShader<PixelShader>("RenderQuadShader");

	vertexBuffer = new VertexBuffer(*renderData, *vertexShader);

	indexBuffer = new IndexBuffer(*renderData);

	D3D11_SAMPLER_DESC frameTextureSampler = {};
	frameTextureSampler.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
	frameTextureSampler.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
	frameTextureSampler.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
	frameTextureSampler.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;

	GraphicsEngine::getInstance()->getDevice().CreateSamplerState(&frameTextureSampler,
	                                                              &textureSampler);
}

RenderQuad::~RenderQuad()
{
	delete renderData;

	delete vertexBuffer;

	delete indexBuffer;

	delete textureSampler;
}

void RenderQuad::draw(ID3D11ShaderResourceView& renderTargetFrame) const
{
	GraphicsEngine::getInstance()->getDeviceContext().setVertexShader(*vertexShader);
	GraphicsEngine::getInstance()->getDeviceContext().setPixelShader(*pixelShader);

	std::vector<ID3D11ShaderResourceView*> frameReferenceViews = {};
	frameReferenceViews.push_back(&renderTargetFrame);

	GraphicsEngine::getInstance()->getDeviceContext().getContext()->PSSetShaderResources(0,
	                                                                                     1,
	                                                                                     frameReferenceViews.data());
	GraphicsEngine::getInstance()->getDeviceContext().getContext()->PSSetSamplers(0,
	                                                                              1,
	                                                                              &textureSampler);

	GraphicsEngine::getInstance()->getDeviceContext().setVertexBuffer(*vertexBuffer);
	GraphicsEngine::getInstance()->getDeviceContext().setIndexBuffer(*indexBuffer);

	GraphicsEngine::getInstance()->getDeviceContext().setTopology(renderData->Topology);

	GraphicsEngine::getInstance()->getDeviceContext().drawIndexed(indexBuffer->getElementCount(),
	                                                              0,
	                                                              0);
}
