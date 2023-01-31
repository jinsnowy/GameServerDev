#include "pch.h"
#include "EntityException.h"
#include "Entity.h"

const char* action_str(PERSIST_ACTION action)
{
	switch (action)
	{
	case PERSIST_ACTION::CREATE:
		return "[CREATE]";
	case PERSIST_ACTION::UPDATE:
		return "[UPDATE]";
	case PERSIST_ACTION::REMOVE:
		return "[REMOVE]";
	}

	return "NONE";
}


entity_persist_exception::entity_persist_exception(PERSIST_ACTION action, const shared_ptr<Entity>& entity)
	:
	_action(action)
{
	const char* type_str = typeid(entity.get()).name();
	_buffer = String::Format("%s type : %s, id : %d", action_str(action), type_str, entity->id());
	_buffer_w = String::ToWide(_buffer);
}
