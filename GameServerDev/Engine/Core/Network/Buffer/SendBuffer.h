#pragma once

namespace Core {
	namespace Network {
		namespace Buffer {
			struct WriteData
			{
				std::vector<WSABUF> buffers;
				std::vector<BufferSegment> segments;

				void Append(const BufferSegment& segment) { segments.push_back(segment); buffers.push_back(segment.AsBufffer()); }

				bool IsEmpty() { return segments.empty(); }

				void Clear() { buffers.clear(); segments.clear(); }
			};

			class SendBuffer
			{
			private:
				WriteData				_writeData;

			public:
				SendBuffer();

				~SendBuffer();

				bool IsEmpty() { return _writeData.IsEmpty(); }

				void Pend(const BufferSegment& segment);

				WriteData Flush();

				void Clear();

				NO_COPY_AND_ASSIGN(SendBuffer);
			};
		}
	}
}