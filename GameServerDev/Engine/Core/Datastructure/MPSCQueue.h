#pragma once

DECLSPEC_ALIGN(16)
class MPSCQueue final
{
private:
	SLIST_HEADER _slist_header;
public:
	MPSCQueue();

	~MPSCQueue();

	void Push(SLIST_ENTRY* item_ptr);

	SLIST_ENTRY* Pop();
};