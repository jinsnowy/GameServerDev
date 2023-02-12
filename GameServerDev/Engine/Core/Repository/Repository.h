#pragma once

class Entity;
class DBConnection;
class Repository
{
private:
	StdMutex _mtx;
	std::unordered_map<int, std::shared_ptr<Entity>> _entities;

protected:
	Repository();

	void Create(std::shared_ptr<Entity> entity);

	void Remove(std::shared_ptr<Entity> entity);

	std::shared_ptr<Entity> Find(int id);

	virtual void OnCreate(std::shared_ptr<Entity> entity);

	virtual void OnDestroy(std::shared_ptr<Entity> entity);

public:
	virtual ~Repository();

	virtual void Initialize(DBConnection* db_conn);

	size_t Count() { return _entities.size(); }

	bool Exists(int id);

	void Clear();
};