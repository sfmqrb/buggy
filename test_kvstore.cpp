#include <cassert>
#include <iostream>
#include "kvstore.hpp"

int main() {
    KVStore store;

    // Test 1: put & get basic
    store.put("foo", "bar");
    assert(store.get("foo") == "bar");

    // Test 2: get non-existent → should be empty, but UB in code
    assert(store.get("nope").empty());

    // Test 3: remove existing
    assert(store.remove("foo") == true);

    // Test 4: remove again → should be false
    assert(store.remove("foo") == false);

    // Test 5: re-insert and update
    store.put("foo", "baz");
    assert(store.get("foo") == "baz");

    // Test 6: capacity growth
    for (int i = 0; i < 20; ++i) {
        store.put("k" + std::to_string(i), "v" + std::to_string(i));
    }
    for (int i = 0; i < 20; ++i) {
        assert(store.get("k" + std::to_string(i)) == "v" + std::to_string(i));
    }

    // Test 7: random number generator
    int r1 = getRandomInt();
    int r2 = getRandomInt();
    assert(r1 != r2);  // likely to fail since rand is unseeded

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

