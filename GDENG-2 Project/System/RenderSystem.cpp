#include "RenderSystem.h"
#include "Debug.h"
#include "Graphics/SwapChain.h"

#include "Component/RenderComponent.h"

#include "GameObject/AGameObject.h"
#include "GameObject/Camera.h"

RenderSystem::RenderSystem() :
	componentMap{},
	componentList{}
{
}

RenderSystem::~RenderSystem()
{
	componentMap.clear();

	for (int i = 0; i < componentList.size(); i++)
	{
		delete componentList[i];
	}

	componentList.erase(componentList.begin(),
	                    componentList.end());
	componentList.clear();
	componentList.shrink_to_fit();
}

RenderComponent& RenderSystem::registerComponent(AGameObject& gameObjRef,
                                                 RenderComponent& renderComponent)
{
	// Check if this component is already added in the map and/or list
	if (componentMap.contains(gameObjRef.Name))
	{
		Debug::Log("RenderComponent is already attached to game object {0}!", gameObjRef.Name);
		return *componentMap[gameObjRef.Name];
	}

	componentList.emplace_back(&renderComponent);
	componentMap[gameObjRef.Name] = &renderComponent;
	return renderComponent;
}

void RenderSystem::deregisterComponent(AGameObject& gameObjRef)
{
	// Check if this component is already added in the map and/or list
	if (!componentMap.contains(gameObjRef.Name))
	{
		Debug::Log("RenderComponent is not attached to game object {0}!", gameObjRef.Name);
		return;
	}

	// TODO: Implement later (if this occurs)
	// (if there are any dependencies, remove them from the components still attached)
	int index = -1;
	for (int i = 0; i < componentList.size(); i++)
	{
		if (componentList[i]->getName() == gameObjRef.Name)
		{
			index = i;
		}
	}

	componentList.erase(componentList.begin() + index);
	componentList.shrink_to_fit();
	componentMap.erase(gameObjRef.Name);
}

RenderComponent* RenderSystem::getComponent(AGameObject& gameObjRef)
{
	if (!componentMap.contains(gameObjRef.Name))
	{
		Debug::Log("RenderComponent is not attached to game object {0}!", gameObjRef.Name);
		return nullptr;
	}
	return componentMap[gameObjRef.Name];
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
