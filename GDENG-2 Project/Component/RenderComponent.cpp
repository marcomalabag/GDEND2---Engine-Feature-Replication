#include "RenderComponent.h"

#include "Debug.h"

#include "GameObject/AGameObject.h"

__declspec(align(16))
struct RenderObjectData
{
	Matrix4x4 Model;

	Matrix4x4 ViewProjection;

	Color SolidColor;
};

RenderComponent::RenderComponent(AGameObject& owner,
                                 RenderData* renderData,
                                 VertexShader* vertexShader,
                                 PixelShader* pixelShader) :
	AComponent{owner},
	renderData{renderData},
	vertexShader{vertexShader},
	pixelShader{pixelShader},
	vertexBuffer{nullptr},
	indexBuffer{nullptr},
	constantBuffer{nullptr}
{
	if (renderData == nullptr)
	{
		Debug::Log("Attempting to Attach a RenderComponent to {0} with null RenderData!",
		           owner.Name.c_str());
		return;
	}

	const RenderObjectData* renderObjectData = new RenderObjectData();

	this->vertexBuffer = new VertexBuffer(*this->renderData,
	                                      *this->vertexShader);

	this->indexBuffer = new IndexBuffer(*this->renderData);

	this->constantBuffer = new ConstantBuffer(renderObjectData,
	                                          sizeof(RenderObjectData));

	// RenderSystem::register();
}

RenderComponent::~RenderComponent()
{
	delete constantBuffer;
	delete indexBuffer;
	delete vertexBuffer;
	delete pixelShader;
	delete vertexBuffer;
	delete renderData;
}
// Draw is delegated to RenderSystem
// void RenderComponent::draw(Camera& camera) const
// {
// 	RenderObjectData* constant = new RenderObjectData();
// 	// constant->Model            = ownerRef.Transform().LocalMatrix();
// 	constant->ViewProjection = camera.getViewMatrix();
// 	constant->SolidColor     = AlbedoColor;
//
// 	// GraphicsEngine::getDeviceContext().updateBufferResource(*constantBuffer, constant);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().setVertexShader(*vertexShader);
// 	GraphicsEngine::getInstance()->getDeviceContext().setPixelShader(*pixelShader);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().uploadShaderData<VertexShader>(*constantBuffer);
// 	GraphicsEngine::getInstance()->getDeviceContext().uploadShaderData<PixelShader>(*constantBuffer);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().setVertexBuffer(*vertexBuffer);
// 	GraphicsEngine::getInstance()->getDeviceContext().setIndexBuffer(*indexBuffer);
// 	GraphicsEngine::getInstance()->getDeviceContext().setTopology(renderData->Topology);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().drawIndexed(indexBuffer->getElementCount(),
// 	                                                              0,
// 	                                                              0);
// }
//
// void RenderComponent::draw(Matrix4x4 viewProjMatrix) const
// {
// 	RenderObjectData* constant = new RenderObjectData();
// 	// constant->Model            = ownerRef().LocalMatrix();
// 	constant->ViewProjection = viewProjMatrix;
// 	constant->SolidColor     = AlbedoColor;
//
// 	// GraphicsEngine::getDeviceContext().updateBufferResource(*constantBuffer, constant);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().setVertexShader(*vertexShader);
// 	GraphicsEngine::getInstance()->getDeviceContext().setPixelShader(*pixelShader);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().uploadShaderData<VertexShader>(*constantBuffer);
// 	GraphicsEngine::getInstance()->getDeviceContext().uploadShaderData<PixelShader>(*constantBuffer);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().setVertexBuffer(*vertexBuffer);
// 	GraphicsEngine::getInstance()->getDeviceContext().setIndexBuffer(*indexBuffer);
// 	GraphicsEngine::getInstance()->getDeviceContext().setTopology(renderData->Topology);
//
// 	GraphicsEngine::getInstance()->getDeviceContext().drawIndexed(indexBuffer->getElementCount(),
// 	                                                              0,
// 	                                                              0);
// }
