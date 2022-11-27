﻿#pragma once

#include "ComponentRegistry.h"
namespace Engine
{
	using EntityID = uint64_t;
	constexpr EntityID InvalidEntity = 0;

	class Entity
	{
	public:
		explicit Entity(EntityID id,
		                StringView name,
		                ComponentRegistry* componentRegistry);

		virtual ~Entity();

		[[nodiscard]]
		EntityID GetID() const;

		[[nodiscard]]
		const String& GetName() const;

		template <typename ComponentType, typename... Args>
		SharedPtr<ComponentType> AttachComponent(Args&&... args);

		// template <typename T>
		// void DetachComponent();

		template <class ComponentType>
		SharedPtr<ComponentType> GetComponent();

		bool operator==(const Entity& other) const;
		bool operator!=(const Entity& other) const;

		Entity(const Entity& other)                = delete;
		Entity& operator=(const Entity& other)     = delete;
		Entity(Entity&& other) noexcept            = delete;
		Entity& operator=(Entity&& other) noexcept = delete;

		bool Active{};

	private:
		EntityID m_ID;
		String m_Name;
		ComponentRegistry* m_ComponentRegistry;
	};

	template <typename ComponentType, typename ... Args>
	SharedPtr<ComponentType> Entity::AttachComponent(Args&&... args)
	{
		SharedPtr<ComponentType> component = CreateSharedPtr<ComponentType>(m_ID,
		                                                                    std::forward<Args>(args)...);
		
		return m_ComponentRegistry->RegisterComponent<ComponentType>(m_ID, component);
	}
	
	template <class ComponentType>
	SharedPtr<ComponentType> Entity::GetComponent()
	{
		return m_ComponentRegistry->GetComponent<ComponentType>(m_ID);
	}

	// template <typename T>
	// void Entity::DetachComponent()
	// {
	// 	if (!m_ComponentTable.contains(T::GetStaticName()))
	// 	{
	// 		return;
	// 	}
	//
	// 	T* component = m_ComponentTable[T::GetStaticName()];
	// 	m_ComponentTable.erase(T::GetStaticName());
	// 	delete component;
	// }
	//
	// template <class T>
	// T* Entity::GetComponent()
	// {
	// 	auto foundComponent = m_ComponentTable.find(T::GetStaticName());
	// 	return (foundComponent != m_ComponentTable.end()) ?
	// 		       (T*)foundComponent->second :
	// 		       nullptr;
	// }
}
