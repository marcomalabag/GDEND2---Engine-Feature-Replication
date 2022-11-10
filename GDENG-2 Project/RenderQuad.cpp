#include "RenderQuad.h"

#include <array>

#include "ShaderLibrary.h"
#include "Vector3D.h"

struct RenderQuadVertex
{
	Vector3D Position;

	std::array<float, 2> TextureCoordinates;
};

RenderQuad::RenderQuad() :
	renderData{nullptr},
	vertexShader{ShaderLibrary::getShader<VertexShader>("RenderQuad_VS")},
	pixelShader{ShaderLibrary::getShader<PixelShader>("RenderQuad_PS")},
	vertexBuffer{nullptr},
	indexBuffer{nullptr},
	textureSampler{nullptr}
{
	RenderQuadVertex* vertices = new RenderQuadVertex[4]
	{
		{{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
		{{-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
	};

	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
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
	renderData->vertices                 = vertices;
	renderData->vertexCount              = sizeof(*vertices);
	renderData->vertexSize               = sizeof(RenderQuadVertex);
	renderData->vertexLayout             = layout;
	renderData->vertexLayoutElementCount = 2U;
	renderData->indices                  = indices;
	renderData->indexCount               = sizeof(indices);
	renderData->topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

RenderQuad::~RenderQuad()
{
	delete renderData;
	delete textureSampler;
}

void RenderQuad::draw(ID3D11ShaderResourceView& frameTexture) const
{
	GraphicsEngine::getInstance()->getDeviceContext()->setVertexShader(&vertexShader);
	GraphicsEngine::getInstance()->getDeviceContext()->setPixelShader(&pixelShader);

	std::vector<ID3D11ShaderResourceView*> frameReferenceViews = {};
	frameReferenceViews.push_back(&frameTexture);

	GraphicsEngine::getInstance()->getDeviceContext()->getContext()
	                             ->PSSetShaderResources(0,
	                                                    1,
	                                                    frameReferenceViews.data());

	GraphicsEngine::getInstance()->getDeviceContext()->getContext()
	                             ->PSSetSamplers(0,
	                                             1,
	                                             &textureSampler);
	
	GraphicsEngine::getInstance()->getDeviceContext()->setVertexBuffer(vertexBuffer);
	GraphicsEngine::getInstance()->getDeviceContext()->setIndexBuffer(indexBuffer);

	GraphicsEngine::getInstance()->getDeviceContext()->drawIndexedTriangleList(indexBuffer->elementCount(), 0);
	
	Renderer::GetDeviceContext().SetTopology(m_RenderData->Topology);

	Renderer::GetDeviceContext().DrawIndexed(m_IndexBuffer->ElementCount(),
	                                         0);
}
