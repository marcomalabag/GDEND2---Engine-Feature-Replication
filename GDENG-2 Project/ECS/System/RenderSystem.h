#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Graphics/Framebuffer.h"

#include "Math/Matrix4x4.h"

class AGameObject;
class RenderComponent;
class Camera;

class RenderSystem final
{
	using EntityID = std::string;
public:
	RenderSystem();
	~RenderSystem();

	RenderComponent& registerComponent(AGameObject& gameObjRef,
	                                   RenderComponent& renderComponent);
	void deregisterComponent(AGameObject& gameObjRef);
	RenderComponent* getComponent(AGameObject& gameObjRef);

	// Control render targets?

	void draw(const Matrix4x4& viewProj,
	          const Framebuffer* framebuffer) const;

	RenderSystem(const RenderSystem&)                = delete;
	RenderSystem& operator=(const RenderSystem&)     = delete;
	RenderSystem(RenderSystem&&) noexcept            = delete;
	RenderSystem& operator=(RenderSystem&&) noexcept = delete;

private:
	std::unordered_map<EntityID, RenderComponent*> componentMap;
	std::vector<RenderComponent*> componentList;
};
