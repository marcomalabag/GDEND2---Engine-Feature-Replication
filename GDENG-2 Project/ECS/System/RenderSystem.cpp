#include "RenderSystem.h"
#include "Debug.h"
#include "Graphics/SwapChain.h"

#include "ECS/Component/RenderComponent.h"

#include "ECS/Core/AGameObject.h"

RenderSystem::RenderSystem()  = default;

RenderSystem::~RenderSystem()
{
	componentList.clear();
	componentList.shrink_to_fit();
}

void RenderSystem::registerComponent(RenderComponent* component)
{
	if (component == nullptr)
	{
		return;
	}

	for (const auto* renderComponent : this->componentList)
	{
		if (renderComponent->getOwner().Name == component->getOwner().Name)
		{
			return;
		}
	}

	this->componentList.push_back(component);
}

void RenderSystem::deregisterComponent(const AGameObject& gameObject)
{
	int foundComponentIndex = -1;
	for (size_t i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getOwner().Name == gameObject.Name)
		{
			foundComponentIndex = (int)i;
		}
	}

	if (foundComponentIndex == -1)
	{
		return;
	}

	this->componentList.erase(this->componentList.begin() + foundComponentIndex);
	this->componentList.shrink_to_fit();
}

void RenderSystem::draw(const Matrix4x4& viewProj,
                        const Framebuffer* framebuffer) const
{
	const FramebufferProfile info = framebuffer->getInfo();

	GraphicsEngine::getInstance()->getDeviceContext().setViewportSize((float)info.Width,
	                                                                  (float)info.Height);

	GraphicsEngine::getInstance()->getDeviceContext().setRenderTargetTo(&framebuffer->getRenderTarget(),
	                                                                    &framebuffer->getDepthStencil());

	GraphicsEngine::getInstance()->getDeviceContext().clearRenderTargetView(framebuffer->getRenderTarget(),
	                                                                        Color(0.8f, 0.4f, 0.7f, 1.0f));

	GraphicsEngine::getInstance()->getDeviceContext().clearDepthStencilView(framebuffer->getDepthStencil());

	for (const RenderComponent* component : componentList)
	{
		component->draw(viewProj);
	}
}
