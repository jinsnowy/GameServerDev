#pragma once

#include "../../Database/DBConnection.h"
#include "Repository.h"
#include "Entity.h"

template<typename T>
requires std::is_base_of_v<Entity, T>
class PersistentRepository : public Repository
{
protected:
	using EntityType = std::shared_ptr<T>;

public:
	template <typename ...Args>
	std::shared_ptr<T> Create(DBConnectionSourcePtr& db_conn, Args&&... args) 
	{
		auto entity = std::make_shared<T>(std::forward<Args>(args)...);
		entity->persist(db_conn);
		Repository::Create(entity);
		return entity;
	}

	std::shared_ptr<T> Add(std::shared_ptr<T> entity)
	{
		entity->force_valid();
		Repository::Create(entity);
		return entity;
	}

	void Remove(DBConnectionSourcePtr& db_conn, shared_ptr<T> entity) 
	{
		Repository::Remove(entity);
		entity->persist(db_conn);
	}

	std::shared_ptr<T> Find(int id) 
	{
		return static_pointer_cast<T>(Repository::Find(id));
	}

	std::shared_ptr<T> Fetch(int id) 
	{
		std::shared_ptr<T> entity;
		if (entity = Find(id); entity != nullptr) {
			return entity;
		}

		if (entity = T::Select(id); entity != nullptr) {
			Repository::Add(entity);
			return entity;
		}

		return nullptr;
	}

	void Initialize(DBConnectionSourcePtr& db_conn) override
	{
		auto entities = T::SelectAll(db_conn);
		for (auto& entity : entities) 
		{
			Repository::Create(entity);
		}
	}

private:
	virtual void OnCreate(std::shared_ptr<Entity> entity)
	{
		PersistentRepository<T>::OnCreate(static_pointer_cast<T>(entity));
	}

	virtual void OnDestroy(std::shared_ptr<Entity> entity)
	{
		PersistentRepository<T>::OnDestroy(static_pointer_cast<T>(entity));
	}

protected:
	virtual void OnCreate(const std::shared_ptr<T>& entity) {}

	virtual void OnDestroy(const std::shared_ptr<T>& entity) {}
};
