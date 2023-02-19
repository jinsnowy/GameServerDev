#include "pch.h"
#include "Engine/Core/Datastructure/LRUCache.h"

TEST(TestUtils, LRU_Test) {
	LRUCache<int, int> cache(3);
	cache.Put(1, 2);

	int val;
	EXPECT_TRUE(cache.Get(1, val));
	EXPECT_EQ(val, 2);
	EXPECT_TRUE(cache.Empty() == false);

	cache.Put(1, 2);
	cache.Put(2, 3);
	cache.Put(3, 4);
	cache.Put(4, 5);

	EXPECT_FALSE(cache.Get(1, val));
	EXPECT_EQ(cache.Size(), 3);

	cache.Put(2, 10);
	EXPECT_TRUE(cache.Get(2, val));
	EXPECT_EQ(val, 10);
	EXPECT_TRUE(cache.Top(val));
	EXPECT_EQ(val, 10);
}
