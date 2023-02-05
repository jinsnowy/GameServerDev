#include "pch.h"
#include "Entity.h"
#include "EntityException.h"
#include "../../Database/DBUtils.h"

Entity::Entity()
	:
	_id(kInvalidId),
	_pending_perish(false)
{}

Entity::~Entity()
{
}

void Entity::force_valid(PERSIST_ACTION action)
{
	if (valid() == false) {
		throw entity_persist_exception(action, shared_from_this(), L"invalid id not db object");
	}
}

void Entity::persist(DBConnectionSourcePtr& db_conn)
{
	if (_pending_perish == true) {
		if (Remove(db_conn) == false) {
			throw entity_persist_exception(PERSIST_ACTION::REMOVE, shared_from_this(), db_conn->Get()->last_error_message());
		}
	}
	else if (_id == kInvalidId) {
		if (Create(db_conn) == false) {
			throw entity_persist_exception(PERSIST_ACTION::CREATE, shared_from_this(), db_conn->Get()->last_error_message());
		}
	}
	else {
		if (Update(db_conn) == false) {
			throw entity_persist_exception(PERSIST_ACTION::UPDATE, shared_from_this(), db_conn->Get()->last_error_message());
		}
	}
}
