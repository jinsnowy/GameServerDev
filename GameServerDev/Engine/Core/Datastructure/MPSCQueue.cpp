#include "pch.h"
#include "MPSCQueue.h"

MPSCQueue::MPSCQueue()
{
	InitializeSListHead(&_slist_header);
}

MPSCQueue::~MPSCQueue()
{
}

void MPSCQueue::Push(SLIST_ENTRY* item_ptr)
{
	InterlockedPushEntrySList(&_slist_header, reinterpret_cast<PSLIST_ENTRY>(item_ptr));
}

SLIST_ENTRY* MPSCQueue::Pop() {
	return InterlockedPopEntrySList(&_slist_header);
}
