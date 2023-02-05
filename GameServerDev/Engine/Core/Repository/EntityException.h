#pragma once

enum class PERSIST_ACTION
{
	CREATE,
	UPDATE,
	REMOVE,
};

class Entity;
class entity_persist_exception : public std::exception
{
public:
	entity_persist_exception(PERSIST_ACTION action, const shared_ptr<Entity>& entity, wstring error_message);

	const char* what() const override { return _buffer.c_str(); }

	const wchar_t* what_t() const { return _buffer_w.c_str(); }

private:
	PERSIST_ACTION _action;
	string _buffer;
	wstring _buffer_w;
	wstring _error_message;
};