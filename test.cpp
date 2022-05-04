#include "pch.h"
#include "interval_map.h"



TEST(example_from_task, interval_map_test)
{
    interval_map m = interval_map<int, char>('A');
    m.m_map[1] = 'B';
    m.m_map[3]='A';
    //Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    EXPECT_EQ(m[-1], B<char>('A'));
    EXPECT_EQ(m[2], B<char>('B'));
    EXPECT_EQ(m[3], B<char>('A'));
    m.assign(3, 5, 'A');
    //Print(m);
    EXPECT_EQ(m[3], B<char>('A'));
    m.assign(8, 11, 'A');
    EXPECT_EQ(m[10], B<char>('A'));
    //Print(m);
}
TEST(not_insert_mval_in_the_begining_or_in_the_end, interval_map_test)
{
    interval_map m = interval_map<int, char>('A');
    m.assign(2, 5, 'A');
    EXPECT_EQ(m.m_map.size(), 0);
    EXPECT_EQ(m[7], 'A');
    //Print(m);
    m.assign(2, 5, 'B');
    EXPECT_EQ(m.m_map.size(), 2);
    m.assign(-2, 1, 'A');
    EXPECT_EQ(m.m_map.size(), 2);
    //Print(m);
}
TEST(insert_merge_left_right_mval, interval_map_test)
{
    interval_map m = interval_map<int, char>('A');
    m.assign(2, 5, 'B');
    //Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    m.assign(-2, 3, 'A');
    //Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    m.assign(4, 5, 'A');
    //Print(m);
    EXPECT_EQ(m[3], 'B');
}
TEST(just_different_intervals, interval_map_test)
{
    interval_map m = interval_map<int, char>('A');
    m.assign(-2, 8, 'B');
    EXPECT_EQ(m[1], 'B');
    //Print(m);
    m.assign(2, 3, 'C');
    EXPECT_EQ(m[2], 'C');
    //Print(m);
    m.assign(3, 4, 'D');
    EXPECT_EQ(m[3], 'D');
    //Print(m);
    m.assign(4, 5, 'F');
    EXPECT_EQ(m[4], 'F');
    //Print(m);
    m.assign(7, 12, 'T');
    //Print(m);
    EXPECT_EQ(m[5], 'B');
    EXPECT_EQ(m[14], 'A');
    EXPECT_EQ(m[7], 'T');
    EXPECT_EQ(m.m_map.size(), 7);
}

TEST(general, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    EXPECT_EQ(m[100], B<char>('A'));
    m.assign(A<int>(3), A<int>(10), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m[-4], B<char>('A'));
    m.assign(A<int>(1), A<int>(6), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m[2], B<char>('B'));
    EXPECT_EQ(m[8], B<char>('B'));
    m.assign(A<int>(15), A<int>(17), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m[16], B<char>('B'));
    EXPECT_EQ(m[18], B<char>('A'));
    m.assign(A<int>(0), A<int>(20), B<char>('A'));
    // Print(m);
    EXPECT_EQ(m[19], B<char>('A'));
    m.assign(A<int>(7), A<int>(12), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m[10], B<char>('B'));
    m.assign(A<int>(12), A<int>(15), B<char>('x'));
    // Print(m);
    EXPECT_EQ(m[13], B<char>('x'));
}
//
TEST(union_from_left_in_beginig, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    m.assign(A<int>(3), A<int>(10), B<char>('B'));
    // Print(m);
    m.assign(A<int>(1), A<int>(5), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m[0], B<char>('A'));
    EXPECT_EQ(m[2], B<char>('B'));
    EXPECT_EQ(m[5], B<char>('B'));
    EXPECT_EQ(m[100], B<char>('A'));
}

TEST(union_two_intervals_of_three, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(3), B<char>('B'));
    // Print(m);
    m.assign(A<int>(4), A<int>(6), B<char>('B'));
    // Print(m);
    m.assign(A<int>(7), A<int>(10), B<char>('B'));
    // Print(m);
    m.assign(A<int>(2), A<int>(5), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 4);
    EXPECT_EQ(m[3], B<char>('B'));
    EXPECT_EQ(m[5], B<char>('B'));
    EXPECT_EQ(m[6], B<char>('A'));
    EXPECT_EQ(m[7], B<char>('B'));

}

TEST(union_two_intervals_in_the_middle, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(3), B<char>('B'));
    // Print(m);
    m.assign(A<int>(4), A<int>(6), B<char>('B'));
    // Print(m);
    m.assign(A<int>(7), A<int>(10), B<char>('B'));
    // Print(m);
    m.assign(A<int>(11), A<int>(15), B<char>('B'));
    // Print(m);
    m.assign(A<int>(5), A<int>(10), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 6);
    EXPECT_EQ(m[0], B<char>('A'));
    EXPECT_EQ(m[6], B<char>('B'));
    EXPECT_EQ(m[10], B<char>('A'));
    EXPECT_EQ(m[14], B<char>('B'));
}

TEST(union_from_right, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(3), A<int>(10), B<char>('B'));
    // Print(m);
    m.assign(A<int>(9), A<int>(12), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    EXPECT_EQ(m[2], B<char>('A'));
    EXPECT_EQ(m[5], B<char>('B'));
    EXPECT_EQ(m[11], B<char>('B'));
}

TEST(union_two_intervals, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(10), B<char>('B'));
    // Print(m);
    m.assign(A<int>(3), A<int>(5), B<char>('B'));
    // Print(m);
    m.assign(A<int>(7), A<int>(10), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    EXPECT_EQ(m[0], B<char>('A'));
    EXPECT_EQ(m[5], B<char>('B'));
    EXPECT_EQ(m[10], B<char>('A'));
    EXPECT_EQ(m[6], B<char>('B'));
}

TEST(union_two_negative_intervals, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(-1), A<int>(0), B<char>('B'));
    // Print(m);
    m.assign(A<int>(-3), A<int>(-1), B<char>('B'));
    // Print(m);
    m.assign(A<int>(7), A<int>(10), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 4);
    EXPECT_EQ(m[0], B<char>('A'));
    EXPECT_EQ(m[7], B<char>('B'));
    EXPECT_EQ(m[10], B<char>('A'));
    EXPECT_EQ(m[8], B<char>('B'));
}

TEST(union_three_different_intervals, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(11), B<char>('B'));
    // Print(m);
    m.assign(A<int>(3), A<int>(9), B<char>('C'));
    // Print(m);
    m.assign(A<int>(5), A<int>(7), B<char>('D'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 6);
    EXPECT_EQ(m[0], B<char>('A'));
    EXPECT_EQ(m[10], B<char>('B'));
    EXPECT_EQ(m[11], B<char>('A'));
    EXPECT_EQ(m[8], B<char>('C'));
    EXPECT_EQ(m[6], B<char>('D'));
}
TEST(limit_intervals, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(11), B<char>('B'));
    // Print(m);
    m.assign(A<int>(3), A<int>(9), B<char>('C'));
    // Print(m);
    m.assign(A<int>(0), A<int>(3), B<char>('A'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 3);
    EXPECT_EQ(m[2], B<char>('A'));
    EXPECT_EQ(m[10], B<char>('B'));
    EXPECT_EQ(m[11], B<char>('A'));
    EXPECT_EQ(m[8], B<char>('C'));
}

TEST(empty, interval_map_test) {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(11), B<char>('B'));
    // Print(m);
    m.assign(A<int>(0), A<int>(100), B<char>('A'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 0);
    EXPECT_EQ(m[0], B<char>('A'));
    EXPECT_EQ(m[10], B<char>('A'));;
}
TEST(insert_dot, interval_map_test)
{
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(2), B<char>('B'));
    // Print(m);
    m.assign(A<int>(3), A<int>(4), B<char>('B'));
    EXPECT_EQ(m[3], B<char>('B'));
    // Print(m);
    m.assign(A<int>(1), A<int>(2), B<char>('C'));
    // Print(m);
    m.assign(A<int>(0), A<int>(0), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 4);
    EXPECT_EQ(m[3], B<char>('B'));
    EXPECT_EQ(m[-1], B<char>('A'));
    EXPECT_EQ(m[1], B<char>('C'));
    EXPECT_EQ(m[10], B<char>('A'));;
}

TEST(insert_init_left, interval_map_test)
{
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(2), B<char>('B'));
    // Print(m);
    m.assign(A<int>(-1), A<int>(1), B<char>('A'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    EXPECT_EQ(m[1], B<char>('B'));
    EXPECT_EQ(m[-1], B<char>('A'));

}

TEST(insert_merge_right, interval_map_test)
{
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(6), B<char>('B'));
    // Print(m);
    m.assign(A<int>(7), A<int>(10), B<char>('B'));
    // Print(m);
    m.assign(A<int>(0), A<int>(9), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    EXPECT_EQ(m[1], B<char>('B'));
    EXPECT_EQ(m[-1], B<char>('A'));
    EXPECT_EQ(m[6], B<char>('B'));

}

TEST(insert_merge_right_2, interval_map_test)
{
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(6), B<char>('B'));
    // Print(m);
    m.assign(A<int>(7), A<int>(11), B<char>('C'));
    // Print(m);
    m.assign(A<int>(0), A<int>(9), B<char>('B'));
    // Print(m);
    EXPECT_EQ(m.m_map.size(), 3);
    EXPECT_EQ(m[1], B<char>('B'));
    EXPECT_EQ(m[-1], B<char>('A'));
    EXPECT_EQ(m[6], B<char>('B'));
    EXPECT_EQ(m[10], B<char>('C'));

}
TEST(reset_with_something_else, interval_map_test)
{
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    // Print(m);
    m.assign(A<int>(1), A<int>(6), B<char>('B'));
    Print(m);
    m.assign(A<int>(0), A<int>(9), B<char>('C'));
    Print(m);
    EXPECT_EQ(m.m_map.size(), 2);
    EXPECT_EQ(m[6], B<char>('C'));
    EXPECT_EQ(m[8], B<char>('C'));

}
