#include "pch.h"
#include "Repository.h"
#include "Entity.h"

Repository::Repository()
{
}

Repository::~Repository()
{
}

bool Repository::Add(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr) {
		return false;
	}

	int id = entity->id();
	_entities[id] = entity;

	return true;
}

bool Repository::Remove(std::shared_ptr<Entity> entity)
{
	if (entity == nullptr) {
		return false;
	}

	int id = entity->_id;
	entity->_pending_perish = true;
	entity->_id = Entity::kInvalidId;
	if (auto iter = _entities.find(id); iter != _entities.end()) {
		_entities.erase(iter);
		return true;
	}

	return false;
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

void Repository::_Clear()
{
	_entities.clear();
}
