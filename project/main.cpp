// Algorithm Playground - main.cpp
// A menu-driven console application demonstrating DSA implementations.

#include <iostream>
#include <stdexcept>
#include <cstddef>

#include "dsa/DynamicArray.hpp"
#include "dsa/Stack.hpp"
#include "dsa/Queue.hpp"
#include "dsa/Deque.hpp"
#include "dsa/SinglyLinkedList.hpp"
#include "dsa/BST.hpp"
#include "dsa/BinaryTree.hpp"
#include "dsa/HashTable.hpp"
#include "dsa/Graph.hpp"
#include "dsa/Sorting.hpp"

// ─── Helpers ────────────────────────────────────────────────────────────────

static void print_separator() {
    std::cout << "\n" << std::string(50, '-') << "\n";
}

static void wait_for_enter() {
    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore(1000, '\n');
    std::cin.get();
}

// Read a valid integer from stdin, re-prompting on bad input.
static int read_int(const char* prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) return v;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "  Invalid input, please enter an integer.\n";
    }
}

// ─── Demo functions ──────────────────────────────────────────────────────────

void demo_dynamic_array() {
    print_separator();
    std::cout << "=== Dynamic Array Demo ===\n\n";

    dsa::DynamicArray<int> arr;
    std::cout << "Pushing 1..5 with push_back:\n  ";
    for (int i = 1; i <= 5; ++i) {
        arr.push_back(i);
        std::cout << i << " ";
    }
    std::cout << "\nSize: " << arr.size() << "  Capacity: " << arr.capacity() << "\n";

    std::cout << "\nInserting 99 at index 2:\n  ";
    arr.insert(2, 99);
    for (std::size_t i = 0; i < arr.size(); ++i) std::cout << arr[i] << " ";

    std::cout << "\n\nErasing index 2:\n  ";
    arr.erase(2);
    for (std::size_t i = 0; i < arr.size(); ++i) std::cout << arr[i] << " ";

    std::cout << "\n\nUsing at() with out-of-range index (6):\n  ";
    try {
        arr.at(6);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    wait_for_enter();
}

void demo_stack() {
    print_separator();
    std::cout << "=== Stack Demo ===\n";
    std::cout << "(Classic use-case: balanced parentheses checker)\n\n";

    auto check_parens = [](const char* expr) {
        dsa::Stack<char> stk;
        bool ok = true;
        for (int i = 0; expr[i] != '\0'; ++i) {
            char c = expr[i];
            if (c == '(' || c == '[' || c == '{') {
                stk.push(c);
            } else if (c == ')' || c == ']' || c == '}') {
                if (stk.empty()) { ok = false; break; }
                char top = stk.top(); stk.pop();
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) { ok = false; break; }
            }
        }
        if (!stk.empty()) ok = false;
        std::cout << "  \"" << expr << "\"  -->  " << (ok ? "BALANCED" : "UNBALANCED") << "\n";
    };

    check_parens("({[]})");
    check_parens("((a + b) * [c - d])");
    check_parens("({)}");
    check_parens("((()");

    std::cout << "\nInteractive push/pop:\n";
    dsa::Stack<int> s;
    for (int v : {10, 20, 30}) { s.push(v); std::cout << "  push(" << v << ")\n"; }
    while (!s.empty()) { std::cout << "  pop() -> " << s.top() << "\n"; s.pop(); }

    wait_for_enter();
}

void demo_queue() {
    print_separator();
    std::cout << "=== Queue Demo ===\n";
    std::cout << "(Simulating a simple task queue)\n\n";

    dsa::Queue<int> q;
    std::cout << "Enqueueing tasks 1..5:\n  ";
    for (int i = 1; i <= 5; ++i) { q.enqueue(i); std::cout << i << " "; }

    std::cout << "\n\nProcessing tasks (FIFO):\n";
    while (!q.empty()) {
        std::cout << "  Processing task #" << q.front() << "\n";
        q.dequeue();
    }

    wait_for_enter();
}

void demo_deque() {
    print_separator();
    std::cout << "=== Deque Demo ===\n\n";

    dsa::Deque<int> dq;
    std::cout << "push_back(1), push_back(2), push_front(0), push_front(-1):\n";
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_front(-1);

    std::cout << "  Front: " << dq.front() << "  Back: " << dq.back() << "  Size: " << dq.size() << "\n";

    std::cout << "\nPopping from both ends:\n";
    std::cout << "  pop_front() -> front was " << dq.front(); dq.pop_front();
    std::cout << "\n  pop_back()  -> back was  " << dq.back();  dq.pop_back();
    std::cout << "\n  Remaining size: " << dq.size() << "\n";

    wait_for_enter();
}

void demo_linked_list() {
    print_separator();
    std::cout << "=== Singly Linked List Demo ===\n\n";

    dsa::SinglyLinkedList<int> list;
    std::cout << "push_back(1..4), then push_front(0):\n  ";
    for (int i = 1; i <= 4; ++i) list.push_back(i);
    list.push_front(0);

    // Print by popping front
    dsa::SinglyLinkedList<int> copy;
    for (int i = 0; i <= 4; ++i) copy.push_back(i);
    while (!copy.empty()) { std::cout << copy.front() << " "; copy.pop_front(); }

    std::cout << "\n\nfront()=" << list.front() << "  back()=" << list.back()
              << "  size=" << list.size() << "\n";

    std::cout << "\npop_front() twice:\n";
    list.pop_front(); list.pop_front();
    std::cout << "  new front=" << list.front() << "  size=" << list.size() << "\n";

    wait_for_enter();
}

void demo_bst() {
    print_separator();
    std::cout << "=== Binary Search Tree Demo ===\n\n";

    dsa::BST<int> bst;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    std::cout << "Inserting: ";
    for (int v : values) { bst.insert(v); std::cout << v << " "; }

    std::cout << "\n\nIn-order traversal (should be sorted):\n  ";
    int out[7];
    bst.inorder(out);
    for (int i = 0; i < 7; ++i) std::cout << out[i] << " ";

    std::cout << "\n\nMin=" << bst.min() << "  Max=" << bst.max()
              << "  Height=" << bst.height() << "\n";

    std::cout << "\ncontains(40)=" << (bst.contains(40) ? "true" : "false")
              << "  contains(99)=" << (bst.contains(99) ? "true" : "false") << "\n";

    std::cout << "\nRemoving 30 (node with two children):\n  ";
    bst.remove(30);
    int out2[6];
    bst.inorder(out2);
    for (int i = 0; i < 6; ++i) std::cout << out2[i] << " ";
    std::cout << "\n";

    wait_for_enter();
}

void demo_hash_table() {
    print_separator();
    std::cout << "=== Hash Table Demo ===\n\n";

    dsa::HashTable ht(8);
    std::cout << "Inserting key-value pairs:\n";
    int keys[]   = {1, 5, 13, 21, 9, -3};
    int vals[]   = {10, 50, 130, 210, 90, -30};
    for (int i = 0; i < 6; ++i) {
        ht.put(keys[i], vals[i]);
        std::cout << "  put(" << keys[i] << ", " << vals[i] << ")\n";
    }

    std::cout << "\nLookups:\n";
    for (int k : {5, 21, 7}) {
        int* v = ht.get(k);
        if (v) std::cout << "  get(" << k << ") = " << *v << "\n";
        else   std::cout << "  get(" << k << ") = NOT FOUND\n";
    }

    std::cout << "\nUpdate: put(5, 999)\n";
    ht.put(5, 999);
    std::cout << "  get(5) = " << *ht.get(5) << "\n";

    std::cout << "\nRemove key 13: " << (ht.remove(13) ? "ok" : "not found") << "\n";
    std::cout << "  contains(13) = " << (ht.contains(13) ? "true" : "false") << "\n";
    std::cout << "  size = " << ht.size() << "\n";

    wait_for_enter();
}

void demo_sorting() {
    print_separator();
    std::cout << "=== Sorting Demo ===\n\n";

    auto print_arr = [](int* a, int n) {
        for (int i = 0; i < n; ++i) std::cout << a[i] << " ";
        std::cout << "\n";
    };

    int src[] = {64, 34, 25, 12, 22, 11, 90};
    const int N = 7;

    {
        int a[7]; for (int i = 0; i < N; ++i) a[i] = src[i];
        std::cout << "Original:   "; print_arr(a, N);
        dsa::SortStats st = dsa::bubble_sort(a, N);
        std::cout << "Bubble sort: "; print_arr(a, N);
        std::cout << "  Comparisons: " << st.comparisons << "  Swaps: " << st.swaps << "\n";
    }

    {
        int a[7]; for (int i = 0; i < N; ++i) a[i] = src[i];
        std::cout << "\nOriginal:   "; print_arr(a, N);
        dsa::SortStats st = dsa::shell_sort(a, N);
        std::cout << "Shell sort:  "; print_arr(a, N);
        std::cout << "  Comparisons: " << st.comparisons << "  Swaps: " << st.swaps << "\n";
    }

    // Interactive: let user enter numbers to sort
    std::cout << "\n--- Sort your own numbers ---\n";
    int n = read_int("How many numbers? ");
    if (n > 0 && n <= 100) {
        dsa::DynamicArray<int> user_arr;
        for (int i = 0; i < n; ++i) {
            char buf[32];
            std::snprintf(buf, sizeof(buf), "  Enter number %d: ", i + 1);
            user_arr.push_back(read_int(buf));
        }
        int* raw = new int[n];
        for (int i = 0; i < n; ++i) raw[i] = user_arr[i];
        dsa::SortStats st = dsa::shell_sort(raw, n);
        std::cout << "Sorted: ";
        for (int i = 0; i < n; ++i) std::cout << raw[i] << " ";
        std::cout << "\nComparisons: " << st.comparisons << "  Swaps: " << st.swaps << "\n";
        delete[] raw;
    }

    wait_for_enter();
}

// Callback for graph traversal (uses a simple counter to avoid extra state)
static dsa::DynamicArray<int> g_visited_order;
static void graph_visit(int v) {
    g_visited_order.push_back(v);
}

void demo_graph() {
    print_separator();
    std::cout << "=== Graph Traversal Demo (BFS & DFS) ===\n\n";

    //  0 -- 1 -- 3
    //  |    |
    //  2    4
    //       |
    //       5 -- 6

    dsa::Graph g(7, false);
    int edges[][2] = {{0,1},{0,2},{1,3},{1,4},{4,5},{5,6}};
    std::cout << "Undirected graph edges:\n";
    for (auto& e : edges) {
        std::cout << "  " << e[0] << " -- " << e[1] << "\n";
        g.add_edge(e[0], e[1]);
    }

    std::cout << "\nBFS from vertex 0: ";
    g_visited_order.clear();
    g.bfs(0, graph_visit);
    for (std::size_t i = 0; i < g_visited_order.size(); ++i)
        std::cout << g_visited_order[i] << (i+1 < g_visited_order.size() ? " -> " : "\n");

    std::cout << "DFS from vertex 0: ";
    g_visited_order.clear();
    g.dfs(0, graph_visit);
    for (std::size_t i = 0; i < g_visited_order.size(); ++i)
        std::cout << g_visited_order[i] << (i+1 < g_visited_order.size() ? " -> " : "\n");

    // Directed graph demo
    std::cout << "\nDirected graph (cycle detection hint):\n";
    //  0 -> 1 -> 2 -> 3
    //            ^
    //            |
    //            4
    dsa::Graph dg(5, true);
    int dedges[][2] = {{0,1},{1,2},{2,3},{4,2}};
    for (auto& e : dedges) {
        std::cout << "  " << e[0] << " -> " << e[1] << "\n";
        dg.add_edge(e[0], e[1]);
    }
    std::cout << "\nBFS all components: ";
    g_visited_order.clear();
    dg.bfs_all(graph_visit);
    for (std::size_t i = 0; i < g_visited_order.size(); ++i)
        std::cout << g_visited_order[i] << (i+1 < g_visited_order.size() ? " -> " : "\n");

    wait_for_enter();
}

void demo_binary_tree() {
    print_separator();
    std::cout << "=== Binary Tree Demo ===\n\n";

    dsa::BinaryTree<int> bt;
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    bt.set_root(1);
    bt.add_left(1, 2); bt.add_right(1, 3);
    bt.add_left(2, 4); bt.add_right(2, 5);
    bt.add_right(3, 6);

    std::cout << "Tree structure:\n"
              << "       1\n"
              << "      / \\\n"
              << "     2   3\n"
              << "    / \\   \\\n"
              << "   4   5   6\n\n";

    int out[6];

    bt.preorder(out);
    std::cout << "Pre-order  (root-left-right): ";
    for (int i = 0; i < 6; ++i) std::cout << out[i] << " ";

    bt.inorder(out);
    std::cout << "\nIn-order   (left-root-right): ";
    for (int i = 0; i < 6; ++i) std::cout << out[i] << " ";

    bt.postorder(out);
    std::cout << "\nPost-order (left-right-root): ";
    for (int i = 0; i < 6; ++i) std::cout << out[i] << " ";

    std::cout << "\n\nHeight: " << bt.height()
              << "  Size: " << bt.size() << "\n";
    std::cout << "contains(5)=" << (bt.contains(5) ? "true" : "false")
              << "  contains(9)=" << (bt.contains(9) ? "true" : "false") << "\n";

    wait_for_enter();
}

// ─── Main menu ───────────────────────────────────────────────────────────────

void print_menu() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║       Algorithm Playground           ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << "║  1.  Dynamic Array                   ║\n";
    std::cout << "║  2.  Stack  (parentheses checker)    ║\n";
    std::cout << "║  3.  Queue  (task simulation)        ║\n";
    std::cout << "║  4.  Deque                           ║\n";
    std::cout << "║  5.  Singly Linked List              ║\n";
    std::cout << "║  6.  Binary Search Tree              ║\n";
    std::cout << "║  7.  Hash Table                      ║\n";
    std::cout << "║  8.  Sorting (Bubble & Shell)        ║\n";
    std::cout << "║  9.  Graph  (BFS & DFS)              ║\n";
    std::cout << "║  10. Binary Tree  (traversals)       ║\n";
    std::cout << "║  0.  Exit                            ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    std::cout << "Choose: ";
}

int main() {
    std::cout << "\nWelcome to Algorithm Playground!\n";
    std::cout << "All data structures are custom implementations (no STL containers).\n";

    while (true) {
        print_menu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        switch (choice) {
            case 1:  demo_dynamic_array(); break;
            case 2:  demo_stack();         break;
            case 3:  demo_queue();         break;
            case 4:  demo_deque();         break;
            case 5:  demo_linked_list();   break;
            case 6:  demo_bst();           break;
            case 7:  demo_hash_table();    break;
            case 8:  demo_sorting();       break;
            case 9:  demo_graph();         break;
            case 10: demo_binary_tree();   break;
            case 0:
                std::cout << "\nGoodbye!\n";
                return 0;
            default:
                std::cout << "Invalid option, try again.\n";
        }
    }
}
