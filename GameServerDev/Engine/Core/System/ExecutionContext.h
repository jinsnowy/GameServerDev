#pragma once

namespace Core {
	namespace System {
		class ExecutionContext : public IThreadStaticSingleton<ExecutionContext>
		{
			friend class ThreadContext;
			friend class ServiceBase;
		public:
			ExecutionContext();
			~ExecutionContext();

		private:
			void Execute(int64& time_slice);
		};
	}
}