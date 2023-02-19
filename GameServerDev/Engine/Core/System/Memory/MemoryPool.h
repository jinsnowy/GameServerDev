#pragma once

namespace Core {
	namespace System {
		namespace Memory {
			DECLSPEC_ALIGN(16)
			struct MemoryHeader : SLIST_ENTRY
			{
				size_t _alloc_size;

				static MemoryHeader* attach(void* ptr)
				{
					MemoryHeader* header = static_cast<MemoryHeader*>(ptr);
					return --header;
				}

				static void* detach(MemoryHeader* header, size_t alloc_size)
				{
					header->_alloc_size = alloc_size;
					return ++header;
				}
			};

			DECLSPEC_ALIGN(16)
			class MemoryPool final
			{
				enum
				{
					LARGEST_MEMORY_SIZE = 4096
				};
			private:
				SLIST_HEADER _header;
				size_t		 _chunk_size;
				size_t		 _base_size;

			public:
				static void Initialize();

				static void* allocate(size_t size);
				static void  deallocate(void* ptr);

			private:
				static MemoryPool* create(size_t base_size)
				{
					void* ptr = _aligned_malloc(sizeof(MemoryPool), 16);
					return new (ptr)MemoryPool(base_size);
				}

				MemoryPool(size_t base_size);
				~MemoryPool();

				void  Push(MemoryHeader* Memory);
				MemoryHeader* Pop();

				static vector<MemoryPool*> s_memoryPoolHolder;
				static MemoryPool* s_memoryPool[LARGEST_MEMORY_SIZE + 1];
			};

			template<typename T, typename ...Args>
			T* pool_new(Args&&... args) {
				void* ptr = MemoryPool::allocate(sizeof(T));
				return new (ptr)T(std::forward<Args>(args)...);
			}

			template<typename T>
			void pool_delete(T* ptr) {
				ptr->~T();
				MemoryPool::deallocate(ptr);
			}

			template<typename T>
			struct PoolSharedDeleter {
				void operator()(T* ptr) {
					pool_delete(ptr);
				}
			};

			template<typename T>
			struct PoolUniqueDeleter {
				void operator()(T* ptr) {
					pool_delete(ptr);
				}
			};

			template<typename T>
			using PoolUniquePtr = std::unique_ptr<T, PoolUniqueDeleter<T>>;

			template<typename T, typename ...Args>
			std::shared_ptr<T> pool_make_shared(Args&&... args) {
				return { new T(std::forward<Args>(args)...), PoolSharedDeleter<T>{} };
			}

			template<typename T, typename ...Args>
			PoolUniquePtr<T> pool_make_unique(Args&&... args) {
				return std::unique_ptr<T, PoolUniqueDeleter<T>>(new T(std::forward<Args>(args)...));
			}
		}
	}

#define POOL_NEW System::Memory::pool_new
}