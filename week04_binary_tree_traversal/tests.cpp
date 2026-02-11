#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/BinaryTree.hpp"
#include <cstddef>

TEST_CASE("BinaryTree starts empty") {
    dsa::BinaryTree<int> t;
    CHECK(t.empty());
    CHECK(t.size() == 0);
    CHECK(t.height() == 0);
    CHECK(t.contains(10) == false);
}

TEST_CASE("Build small tree and test traversals") {
    // Tree shape:
    //       1
    //     /   \
    //    2     3
    //   / \     \
    //  4   5     6
    dsa::BinaryTree<int> t;
    t.set_root(1);
    t.add_left(1, 2);
    t.add_right(1, 3);
    t.add_left(2, 4);
    t.add_right(2, 5);
    t.add_right(3, 6);

    CHECK_FALSE(t.empty());
    CHECK(t.size() == 6);
    CHECK(t.height() == 3);

    CHECK(t.contains(5));
    CHECK(t.contains(42) == false);

    int out[6];

    t.preorder(out);
    CHECK(out[0] == 1);
    CHECK(out[1] == 2);
    CHECK(out[2] == 4);
    CHECK(out[3] == 5);
    CHECK(out[4] == 3);
    CHECK(out[5] == 6);

    t.inorder(out);
    CHECK(out[0] == 4);
    CHECK(out[1] == 2);
    CHECK(out[2] == 5);
    CHECK(out[3] == 1);
    CHECK(out[4] == 3);
    CHECK(out[5] == 6);

    t.postorder(out);
    CHECK(out[0] == 4);
    CHECK(out[1] == 5);
    CHECK(out[2] == 2);
    CHECK(out[3] == 6);
    CHECK(out[4] == 3);
    CHECK(out[5] == 1);
}

TEST_CASE("clear makes tree empty again") {
    dsa::BinaryTree<int> t;
    t.set_root(10);
    t.add_left(10, 5);
    t.add_right(10, 20);

    CHECK(t.size() == 3);
    t.clear();
    CHECK(t.size() == 0);
    CHECK(t.empty());
    CHECK(t.height() == 0);
}
