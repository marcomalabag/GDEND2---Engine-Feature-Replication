#include "CameraRenderComponent.h"

#include "GameObject/Camera.h"
#include "Debug.h"

#include "Component/TransformComponent.h"

#include "GameObject/AGameObject.h"

_declspec(align(16))
struct RenderObjectData
{
	Matrix4x4 Model;

	Matrix4x4 ViewProjection;

	Color SolidColor;
};

CameraRenderComponent::CameraRenderComponent(AGameObject& owner, RenderData* renderData, VertexShader* vertexShader, PixelShader* pixelShader) : AComponent{ owner },
renderData{ renderData },
vertexShader{ vertexShader },
pixelShader{ pixelShader },
vertexBuffer{ nullptr },
indexBuffer{ nullptr },
constantBuffer{ nullptr }
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
}

CameraRenderComponent::~CameraRenderComponent()
{
	delete constantBuffer;
	delete indexBuffer;
	delete vertexBuffer;
	delete pixelShader;
	delete vertexBuffer;
	delete renderData;
}

void CameraRenderComponent::draw(const Matrix4x4& viewProjMatrix) const
{
	RenderObjectData* constant = new RenderObjectData();
	constant->Model = ownerRef.transform().getLocalMatrix();
	constant->ViewProjection = viewProjMatrix;
	constant->SolidColor = AlbedoColor;

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


