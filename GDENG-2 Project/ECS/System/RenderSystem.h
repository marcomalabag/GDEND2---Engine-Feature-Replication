#pragma once
#include <string>
#include <vector>

#include "Graphics/Framebuffer.h"

#include "Math/Matrix4x4.h"

#include "ECS/Component/RenderComponent.h"

// Constant Buffers (TODO)
// Slot 0:

class AGameObject;

class RenderSystem final
{
public:
	RenderSystem();
	~RenderSystem();

	void registerComponent(RenderComponent* component);

	void deregisterComponent(const AGameObject& gameObject);

	//=====ACTUAL FUNCTIONALITY=====//

	void draw(const Matrix4x4& viewProj,
	          const Framebuffer* framebuffer) const;

	RenderSystem(const RenderSystem&)                = delete;
	RenderSystem& operator=(const RenderSystem&)     = delete;
	RenderSystem(RenderSystem&&) noexcept            = delete;
	RenderSystem& operator=(RenderSystem&&) noexcept = delete;

private:
	std::vector<RenderComponent*> componentList;
};
