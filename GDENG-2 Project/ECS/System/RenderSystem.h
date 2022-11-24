#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Graphics/Framebuffer.h"

#include "Math/Matrix4x4.h"

#include "ECS/Component/RenderComponent.h"

// RenderSystem has ownership of all RenderComponents

// Constant Buffers (TODO)
// Slot 0:

class AGameObject;

class RenderSystem final
{
public:
	RenderSystem();
	~RenderSystem();

	RenderComponent* createRenderComponent(AGameObject& owner,
	                                       RenderData* renderData,
	                                       VertexShader* vertexShaderRef,
	                                       PixelShader* pixelShaderRef,
	                                       TransformComponent& transformComponent);

	void destroyRenderComponent(AGameObject& gameObject);

	RenderComponent* getComponent(AGameObject& gameObject);

	// Actual functionality of this system

	void draw(const Matrix4x4& viewProj,
	          const Framebuffer* framebuffer) const;

	RenderSystem(const RenderSystem&)                = delete;
	RenderSystem& operator=(const RenderSystem&)     = delete;
	RenderSystem(RenderSystem&&) noexcept            = delete;
	RenderSystem& operator=(RenderSystem&&) noexcept = delete;

private:
	std::vector<RenderComponent*> componentList;

	// Callback list of OnRenderComponentCreate();
	// Callback list of OnRenderComponentDestroy();
};
