#pragma once

#include <Engine/StdMutex.h>

class Entity;
class Repository
{
private:
	StdMutex _mtx;
	std::unordered_map<int, std::shared_ptr<Entity>> _entities;

protected:
	Repository();

	virtual ~Repository();

	void Add(std::shared_ptr<Entity> entity);

	void Remove(std::shared_ptr<Entity> entity);

	std::shared_ptr<Entity> Find(int id);

public:
	size_t Count() { return _entities.size(); }

	bool Exists(int id);

	void Clear();
};