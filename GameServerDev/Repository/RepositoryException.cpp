#include "pch.h"
#include "RepositoryException.h"

repositoy_exception::repositoy_exception(const char* reason)
	:
	_buffer(reason),
	_buffer_w(StringUtils::ToWide(reason))
{
}