#pragma once

#define DEFINE_ENTITY_API(entity,repository)\
protected:\
	virtual bool Create(DBConnectionSourcePtr& db_conn) override;\
	virtual bool Update(DBConnectionSourcePtr& db_conn) override;\
	virtual bool Remove(DBConnectionSourcePtr& db_conn) override;\
\
	friend class repository;\
	static std::shared_ptr<##entity> Select(int id, DBConnectionSourcePtr& db_conn);\
	static std::vector<std::shared_ptr<##entity>> SelectAll(DBConnectionSourcePtr& db_conn);

#define CREATE_API(entity) bool entity::Create(DBConnectionSourcePtr& db_conn)
#define UPDATE_API(entity) bool entity::Update(DBConnectionSourcePtr& db_conn)
#define REMOVE_API(entity) bool entity::Remove(DBConnectionSourcePtr& db_conn)
#define SELECT_API(entity) std::shared_ptr<##entity> entity::Select(int id, DBConnectionSourcePtr& db_conn)
#define SELECT_ALL_API(entity) std::vector<std::shared_ptr<##entity>> entity::SelectAll(DBConnectionSourcePtr& db_conn)

class Entity : public enable_shared_from_this<Entity>
{
	static constexpr int kInvalidId = -1;
public:
	Entity();

	virtual ~Entity();

	int id() { return _id; }

	bool valid() { return _id != kInvalidId; }

	void persist(DBConnectionSourcePtr& db_conn);

protected:
	friend class Repository;
	atomic<int> _id;
	atomic<bool> _pending_perish;

protected:
	virtual bool Create(DBConnectionSourcePtr& db_conn) abstract;
	virtual bool Update(DBConnectionSourcePtr& db_conn) abstract;
	virtual bool Remove(DBConnectionSourcePtr& db_conn) abstract;
};

using EntityPtr = std::shared_ptr<Entity>;