#pragma once
#include <unordered_map>
#include <vector>

#include "Debug.h"

#include "Component/AComponent.h"

// Entity ID is a name (May change to int id if need be)
// Issue with name as ID is no entity must have the same name

template <typename EntityID, typename ComponentType>
class ComponentStorage
{
public:
	void add(const EntityID& entityID,
	         ComponentType* component);

	void remove(const EntityID& entityID);

	void clear();

	void processComponentsInList(void (*function)(ComponentType*)) const;

private:
	std::unordered_map<EntityID, ComponentType*> componentMap;
	std::vector<ComponentType*> componentList;
};

template <typename EntityID, typename ComponentType>
void ComponentStorage<EntityID, ComponentType>::add(const EntityID& entityID,
                                                    ComponentType* component)
{
	Debug::Assert(component != nullptr,
	              "Attempting to add a null {0} component in ComponentStorage!",
	              ComponentType::getStaticName());

	if (componentMap.contains(entityID))
	{
		Debug::Log("Attempting to store an existing {0} component in ComponentStorage.",
		           ComponentType::getStaticName());
		return;
	}

	componentMap[entityID] = component;
	componentList.emplace_back(component);
}

template <typename EntityID, typename ComponentType>
void ComponentStorage<EntityID, ComponentType>::remove(const EntityID& entityID)
{
	if (!componentMap.contains(entityID))
	{
		Debug::Log("Attempting to remove a non-existing {0} component in ComponentStorage.",
		           ComponentType::getStaticName());
		return;
	}

	auto findComponentFunction = [entityID](ComponentType* other) -> bool
	{
		return entityID == other->getOwner().Name;
	};

	const auto foundComponentInList = std::ranges::remove_if(componentList,
	                                                         findComponentFunction);

	componentList.erase(foundComponentInList);
	componentList.shrink_to_fit();
	componentMap.erase(entityID);
}

template <typename EntityID, typename ComponentType>
void ComponentStorage<EntityID, ComponentType>::clear()
{
	// Detach this component from their owner
	
}

template <typename EntityID, typename ComponentType>
void ComponentStorage<EntityID, ComponentType>::processComponentsInList(void (* function)(ComponentType*)) const
{
	for (AComponent* component : componentList)
	{
		function(component);
	}
}
