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

void Repository::Add(std::shared_ptr<Entity> entity)
{
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

	StdWriteLock lk(_mtx);

	auto iter = _entities.find(id);
	if (iter == _entities.end()) {
		throw repositoy_exception("entity was not in repository");
	}

	_entities.erase(iter);
}

std::shared_ptr<Entity> Repository::Find(int id)
{
	if (auto iter = _entities.find(id); iter != _entities.end()) {
		return iter->second;
	}

	return nullptr;
}

bool Repository::Exists(int id)
{
	return _entities.find(id) != _entities.end();
}

void Repository::Clear()
{
	_entities.clear();
}
