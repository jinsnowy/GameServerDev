#pragma once

class Entity;
class Repository
{
private:
	std::unordered_map<int, std::shared_ptr<Entity>> _entities;

protected:
	Repository();

	virtual ~Repository();

	bool Add(std::shared_ptr<Entity> entity);

	bool Remove(std::shared_ptr<Entity> entity);

	std::shared_ptr<Entity> Find(int id);

public:
	size_t Count() { return _entities.size(); }

	bool Exists(int id);

	void _Clear();
};