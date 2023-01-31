#pragma once

class DBConnectionPtr;

#define DEFINE_ENTITY_API(entity,repository)\
protected:\
	virtual bool Create(DBConnectionPtr& db_conn) override;\
	virtual bool Remove(DBConnectionPtr& db_conn) override;\
\
	friend class repository;\
	static std::shared_ptr<##entity> Select(int id, DBConnectionPtr& db_conn);\
	static std::vector<std::shared_ptr<##entity>> SelectAll(DBConnectionPtr& db_conn);

#define SELECT_API(entity) std::shared_ptr<##entity> entity::Select(int id, DBConnectionPtr& db_conn)
#define SELECT_ALL_API(entity) std::vector<std::shared_ptr<##entity>> entity::SelectAll(DBConnectionPtr& db_conn)

class Entity : public enable_shared_from_this<Entity>
{
	static constexpr int kInvalidId = -1;
public:
	Entity();
	virtual ~Entity();

	int id() { return _id; }

	bool valid() { return _id != kInvalidId; }

	bool Persist(DBConnectionPtr& db_conn);

	template <typename T>
	std::shared_ptr<T> Cast() {
		return static_pointer_cast<T>(shared_from_this());
	}

protected:
	friend class Repository;
	atomic<int> _id;
	atomic<bool> _pending_perish;

protected:
	virtual bool Create(DBConnectionPtr& db_conn) abstract;
	virtual bool Remove(DBConnectionPtr& db_conn) abstract;
};

using EntityPtr = std::shared_ptr<Entity>;