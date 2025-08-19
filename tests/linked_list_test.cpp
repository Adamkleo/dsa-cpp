#include <gtest/gtest.h>
#include "linkedlist/linked_list.h"

TEST(LinkedListTest, Size) {
    LinkedList<int> lst;
    EXPECT_EQ(true, lst.empty());
    EXPECT_EQ(0u, lst.size());

    lst.push_back(10);
    lst.push_back(20);

    EXPECT_EQ(2u, lst.size());
}

TEST(LinkedListTest, PushAndGet) {
    LinkedList<int> lst;
    EXPECT_THROW(lst.at(0), std::out_of_range);
    EXPECT_THROW(lst.at(100), std::out_of_range);

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    EXPECT_EQ(lst.at(0), 1);
    EXPECT_EQ(lst.at(2), 3);
    EXPECT_THROW(lst.at(5), std::out_of_range);
}

TEST(LinkedListTest, PushAndGetConstAccess) {
    LinkedList<int> lst;
    lst.push_back(10);
    lst.push_back(20);

    const LinkedList<int>& clst = lst;  

    EXPECT_EQ(clst.at(0), 10);
    EXPECT_EQ(clst.at(1), 20);
    EXPECT_THROW(clst.at(2), std::out_of_range);
}

TEST(LinkedListTest, FrontBackAccess) {
    LinkedList<int> lst;
    EXPECT_THROW(lst.front(), std::out_of_range);
    EXPECT_THROW(lst.back(), std::out_of_range);
    lst.push_back(10);
    EXPECT_EQ(lst.front(), 10);
    EXPECT_EQ(lst.back(), 10);
    lst.push_back(20);
    EXPECT_EQ(lst.front(), 10);
    EXPECT_EQ(lst.back(), 20);
}

TEST(LinkedListTest, PushBackAndFront) {
    LinkedList<std::string> lst;
    lst.push_back("first");
    EXPECT_EQ(lst.at(0), "first");
    lst.push_back("second");
    EXPECT_EQ(lst.at(1), "second");
    lst.push_front("new first");
    EXPECT_EQ(lst.at(0), "new first");
    lst.at(1) = "old first";
    EXPECT_EQ(lst.at(1), "old first");
}

TEST(LinkedListTest, Insert) {
    LinkedList<float> lst;
    lst.push_back(1.0);
    lst.push_back(2.0);
    lst.push_back(3.0);
    lst.push_back(4.0);
    EXPECT_EQ(lst.insert(2.5, 3), Status::Success);
    EXPECT_EQ(lst.at(3), 2.5);
    lst.insert(2.25, 3);
    EXPECT_EQ(lst.at(3), 2.25);
    EXPECT_EQ(lst.at(4), 2.5);
    lst.insert(0.5, 0);
    EXPECT_EQ(lst.at(0), 0.5);
    EXPECT_EQ(lst.insert(2.5, 20), Status::InsertionFailure);
    lst.insert(10.0, lst.size());
    EXPECT_EQ(lst.back(), 10);

}

TEST(LinkedListTest, IndexOf) {
    LinkedList<float> lst;
    lst.push_back(1.0);
    lst.push_back(2.0);
    lst.push_back(3.0);
    lst.push_back(4.0);
    lst.insert(2.5, 3);     
    EXPECT_EQ(lst.index_of(1.0), 0);
    EXPECT_EQ(lst.index_of(2.0), 1);
    EXPECT_EQ(lst.index_of(2.5), 3);
    EXPECT_EQ(lst.index_of(4.0), 4);
    lst.insert(2.25, 3);    
    EXPECT_EQ(lst.index_of(2.25), 3);
    EXPECT_EQ(lst.index_of(99.0), -1);
    lst.push_back(2.0);    
    EXPECT_EQ(lst.index_of(2.0), 1);
}

TEST(LinkedListTest, PopBackAndFront) {
    LinkedList<int> lst;
    EXPECT_THROW(lst.pop_back(), std::out_of_range);
    EXPECT_THROW(lst.pop_front(), std::out_of_range);

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);

    lst.pop_back();
    EXPECT_EQ(lst.back(), 4);   

    lst.pop_back();
    EXPECT_EQ(lst.back(), 3);   

    lst.pop_front();
    EXPECT_EQ(lst.front(), 2);  

    lst.pop_front();
    EXPECT_EQ(lst.front(), 3);  
}

TEST(LinkedListTest, Erase) {
    LinkedList<int> lst;

    // --- empty list ---
    EXPECT_THROW(lst.erase(0), std::out_of_range);
    EXPECT_THROW(lst.erase(5), std::out_of_range);

    // --- single element ---
    lst.push_back(10);
    EXPECT_NO_THROW(lst.erase(0));
    EXPECT_TRUE(lst.empty());
    EXPECT_THROW(lst.erase(0), std::out_of_range); // nothing left

    // --- multiple elements ---
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);

    // remove first
    EXPECT_NO_THROW(lst.erase(0));
    EXPECT_EQ(lst.front(), 2);
    EXPECT_EQ(lst.size(), 4u);

    // remove last
    EXPECT_NO_THROW(lst.erase(lst.size() - 1));
    EXPECT_EQ(lst.back(), 4);
    EXPECT_EQ(lst.size(), 3u);

    // remove middle
    EXPECT_NO_THROW(lst.erase(1)); // remove index 1 (was 3)
    EXPECT_EQ(lst.size(), 2u);

    // confirm remaining elements
    EXPECT_EQ(lst.front(), 2);
    EXPECT_EQ(lst.back(), 4);

    // --- invalid indices ---
    EXPECT_THROW(lst.erase(100), std::out_of_range);
    EXPECT_THROW(lst.erase(-1), std::out_of_range); // if your erase uses size_t, this may wrap
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
