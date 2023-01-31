#include "pch.h"
#include "Entity.h"

Entity::Entity()
	:
	_id(kInvalidId),
	_pending_perish(false)
{}

Entity::~Entity()
{
}

bool Entity::Persist(DBConnectionPtr& db_conn)
{
	if (_pending_perish == true) {
		return Remove(db_conn);
	}
	else {
		return Create(db_conn);
	}
}
