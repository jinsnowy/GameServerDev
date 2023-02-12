#include "pch.h"
#include "Repository.h"
#include "Entity.h"
#include "RepositoryException.h"

Repository::Repository()
{
}

Repository::~Repository()
{
}

void Repository::Initialize(DBConnection* db_conn)
{
}

void Repository::Create(std::shared_ptr<Entity> entity)
{
	int id = entity->_id;
	if (id == Entity::kInvalidId) {
		throw repositoy_exception("entity has invalid id");
	}

	OnCreate(entity);

	StdWriteLock lk(_mtx);

	_entities[entity->id()] = entity;
}

void Repository::Remove(std::shared_ptr<Entity> entity)
{
	int id = entity->_id;
	if (id == Entity::kInvalidId) {
		throw repositoy_exception("entity has invalid id");
	}

	entity->_pending_perish = true;
	entity->_id = Entity::kInvalidId;

	OnDestroy(entity);

	StdWriteLock lk(_mtx);

	auto iter = _entities.find(id);
	if (iter == _entities.end()) {
		throw repositoy_exception("entity was not in repository");
	}

	_entities.erase(iter);
}

std::shared_ptr<Entity> Repository::Find(int id)
{
	StdReadLock lk(_mtx);

	if (auto iter = _entities.find(id); iter != _entities.end()) {
		return iter->second;
	}

	return nullptr;
}

void Repository::OnCreate(std::shared_ptr<Entity> entity)
{
}

void Repository::OnDestroy(std::shared_ptr<Entity> entity)
{
}

bool Repository::Exists(int id)
{
	StdReadLock lk(_mtx);
	return _entities.find(id) != _entities.end();
}

void Repository::Clear()
{
	StdWriteLock lk(_mtx);
	_entities.clear();
}
