#pragma once

#include "Engine/Database/DBConnection.h"
#include "Repository.h"
#include "Entity.h"

template<typename T, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
class PersistentRepository : public Repository
{
public:
	template <typename ...Args>
	std::shared_ptr<T> Create(DBConnectionSourcePtr& db_conn, Args&&... args) {
		auto entity = std::make_shared<T>(std::forward<Args>(args)...);
		entity->persist(db_conn);
		Repository::Add(entity);
		return entity;
	}
	
	void Remove(DBConnectionSourcePtr& db_conn, shared_ptr<T> entity) {
		Repository::Remove(entity);
		entity->persist(db_conn);
	}

	std::shared_ptr<T> Find(int id) {
		return static_pointer_cast<T>(Repository::Find(id));
	}

	std::shared_ptr<T> Fetch(int id) {
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

	void Initialize() {
		auto entities = T::SelectAll();
		for (auto& entity : entities) {
			Repository::Add(entity);
		}
	}
};