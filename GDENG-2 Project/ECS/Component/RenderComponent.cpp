#include "RenderComponent.h"

#include "Debug.h"
#include "TransformComponent.h"

#include "ECS/GameObject/AGameObject.h"

__declspec(align(16))
struct RenderObjectData
{
	Matrix4x4 Model;
	Matrix4x4 ViewProjection;
};

RenderComponent::RenderComponent(AGameObject& owner,
                                 RenderData* renderData,
                                 Material* material) :
	AComponent{owner},
	renderData{renderData},
	material{material},
	vertexBuffer{nullptr},
	indexBuffer{nullptr},
	constantBuffer{nullptr}
{
	if (this->renderData == nullptr)
	{
		Debug::Log("Attempting to Attach a RenderComponent to {0} with null RenderData!",
		           owner.Name.c_str());
		return;
	}

	this->vertexBuffer = new VertexBuffer(*this->renderData,
	                                      *this->vertexShader);

	this->indexBuffer = new IndexBuffer(*this->renderData);

	const RenderObjectData* renderObjectData = new RenderObjectData();

	this->constantBuffer = new ConstantBuffer(renderObjectData,
	                                          sizeof(RenderObjectData));
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

void RenderComponent::draw(const Matrix4x4& viewProjMatrix) const
{
	RenderObjectData* constant = new RenderObjectData();
	constant->Model            = ownerRef.transform().getLocalMatrix();
	constant->ViewProjection   = viewProjMatrix;
	constant->SolidColor       = AlbedoColor;

	GraphicsEngine::getInstance()->getDeviceContext().updateBufferResource(&constantBuffer->getBuffer(),
	                                                                       constant);

	GraphicsEngine::getInstance()->getDeviceContext().setVertexShader(*vertexShader);
	GraphicsEngine::getInstance()->getDeviceContext().setPixelShader(*pixelShader);

	GraphicsEngine::getInstance()->getDeviceContext().uploadShaderData<VertexShader>(*constantBuffer);
	GraphicsEngine::getInstance()->getDeviceContext().uploadShaderData<PixelShader>(*constantBuffer);

	GraphicsEngine::getInstance()->getDeviceContext().setVertexBuffer(*vertexBuffer);
	GraphicsEngine::getInstance()->getDeviceContext().setIndexBuffer(*indexBuffer);

	GraphicsEngine::getInstance()->getDeviceContext().setTopology(renderData->Topology);

	GraphicsEngine::getInstance()->getDeviceContext().drawIndexed(indexBuffer->getElementCount(),
	                                                              0,
	                                                              0);
}
