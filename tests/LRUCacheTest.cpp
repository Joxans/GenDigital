#include "gtest/gtest.h"
#include "../src/LRUCache.h"

class LRUCacheTest : public ::testing::Test {
protected:
    LRUCache<int, std::string> cache{3};
};

// check cache capacity
TEST_F(LRUCacheTest, CapacityTest) {
    EXPECT_EQ(cache.getCapacity(), 3);
}

// check cache item count
TEST_F(LRUCacheTest, ItemCountTest) {
    EXPECT_EQ(cache.getItemCount(), 0);
}

// check cache put and get
TEST_F(LRUCacheTest, PutAndGetTest) {
    cache.put(1, "item1");
    cache.put(2, "item2");
    cache.put(3, "item3");

    EXPECT_EQ(cache.getItemCount(), 3);
    EXPECT_EQ(cache.get(1), "item1");
    EXPECT_EQ(cache.get(2), "item2");
    EXPECT_EQ(cache.get(3), "item3");

    cache.get(1);
    cache.put(4, "item4");

    EXPECT_EQ(cache.getItemCount(), 3);
    EXPECT_EQ(cache.get(2), std::nullopt);
}

// check cache clear
TEST_F(LRUCacheTest, ClearTest) {
    cache.put(1, "item1");
    cache.put(2, "item2");

    EXPECT_EQ(cache.getItemCount(), 2);

    cache.clear();

    EXPECT_EQ(cache.getItemCount(), 0);
    EXPECT_EQ(cache.get(1), std::nullopt);
}

// check removing items
TEST_F(LRUCacheTest, ChangeCapacityTest) {
    cache.put(1, "item1");
    cache.put(2, "item2");
    cache.put(3, "item3");
    cache.put(4, "item4");

    EXPECT_EQ(cache.getItemCount(), 3);

    cache.setCapacity(4);
    cache.put(1, "item1");

    EXPECT_EQ(cache.getItemCount(), 4);

    cache.setCapacity(2);

    EXPECT_EQ(cache.getItemCount(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}