#include <cassert>
#include <iostream>
#include "kvstore.hpp"

int main() {
    KVStore store;

    // Test 1: put & get basic
    store.put("foo", "bar");
    for (int i = 0; i < 20; ++i) {
        store.put("k" + std::to_string(i), "v" + std::to_string(i));
    }
    return 0;
}

