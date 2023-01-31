#pragma once

#include "DBConnection.h"
#include "Repository.h"
#include "Entity.h"

template<typename T, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
class PersistentRepository : public Repository
{
public:
	template <typename ...Args>
	std::shared_ptr<T> Create(DBConnectionPtr& db_conn, Args&&... args) {
		auto entity = std::make_shared<T>(std::forward<Args>(args)...);
		if (entity->Persist(db_conn) == true && Repository::Add(entity)) {
			return entity;
		}

		return nullptr;
	}
	
	bool Remove(DBConnectionPtr& db_conn, shared_ptr<T> entity) {
		if (Repository::Remove(entity) && entity->Persist(db_conn)) {
			return true;
		}

		return false;
	}

	std::shared_ptr<T> Find(int id) {
		std::shared_ptr<T> entity;
		if (entity = Repository::Find(id); entity != nullptr) {
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