#pragma once

namespace Core {
	namespace Network {
		namespace Packet {
			class Serializer;
		}
		namespace Buffer {
			class BufferSource
			{
				enum
				{
					BUFFER_SIZE = 4096,
				};

				friend class Packet::Serializer;
			private:
				static BufferSourcePtr Make() { return make_shared<BufferSource>(); }

				CHAR* copy(CHAR* buf, int32 len)
				{
					CHAR* front = &_buffer[_cursor];
					memcpy(front, buf, len);

					_capacity -= len;
					_cursor += len;
					ASSERT_CRASH(_capacity >= 0);

					return front;
				}

				CHAR* lend(int32 len)
				{
					CHAR* front = &_buffer[_cursor];

					_capacity -= len;
					_cursor += len;
					ASSERT_CRASH(_capacity >= 0);

					return front;
				}

				bool enough(int32 len) { return _capacity >= len; }

				int32 _cursor;
				int32 _capacity;
				CHAR  _buffer[BUFFER_SIZE];

			public:
				BufferSource() { ZeroMemory(_buffer, BUFFER_SIZE); _cursor = 0; _capacity = BUFFER_SIZE; }

			private:
				static BufferSourcePtr GetBuffer(int32 len);
			};
		}
	}
}