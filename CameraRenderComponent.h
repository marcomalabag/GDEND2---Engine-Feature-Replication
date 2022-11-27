#pragma once

#include "Debug.h"
#include "Math/Color.h"
#include "Math/Matrix4x4.h"
#include "Component/AComponent.h"

#include "RenderData.h"

#include "Graphics/VertexShader.h"
#include "Graphics/PixelShader.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ConstantBuffer.h"

class Camera;

class CameraRenderComponent : public AComponent
{
public:
	CameraRenderComponent(AGameObject& owner,
		RenderData* renderData,
		VertexShader* vertexShader,
		PixelShader* pixelShader);

	~CameraRenderComponent() override;

	MAKE_COMPONENT(Render)

		CameraRenderComponent(const CameraRenderComponent&) = delete;

	CameraRenderComponent& operator=(const CameraRenderComponent&) = delete;

	CameraRenderComponent(CameraRenderComponent&&) noexcept = delete;

	CameraRenderComponent& operator=(CameraRenderComponent&&) noexcept = delete;

	Color AlbedoColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

	// Functionality for now, issue when it needs to sort for transparency
	void draw(const Matrix4x4& viewProjMatrix) const;

private:

	RenderData* renderData;

	VertexShader* vertexShader;

	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;

	IndexBuffer* indexBuffer;

	ConstantBuffer* constantBuffer;
};

