#include "kvstore.hpp"
#include <cstring>
#include <cstdlib>

// Simple KV store mapping strings to strings
// (contains 20 bugs, all commented)

KVStore::KVStore() {
    // BUG 1: `capacity` is uninitialized, so new[] uses garbage size
    keys = new char*[capacity];
    values = new char*[capacity];
    count = 0;
}

KVStore::~KVStore() {
    for (int i = 0; i < count; ++i) {
        // BUG 2: using delete[] on pointers that might not have been allocated
        delete[] keys[i];
        delete[] values[i];
    }
    delete[] keys;
    // BUG 3: double delete of keys
    delete[] keys;
    delete[] values;
}

void KVStore::put(const std::string& key, const std::string& value) {
    // BUG 4: no check for `capacity > 0` before using keys/value arrays
    const char* k = key.c_str();
    // BUG 5: strcpy without checking `key.size()+1` fits allocated buffer
    char* nk = new char[key.size() + 1];
    strcpy(nk, k);

    const char* v = value.c_str();
    // BUG 6: mismatched new[] / delete (should match delete[])
    char* nv = (char*)malloc(value.size() + 1);
    strcpy(nv, v);

    if (count >= capacity) {
        // BUG 7: off-by-one in resize: should be capacity * 2, not +1
        char** newKeys = new char*[capacity + 1];
        char** newValues = new char*[capacity + 1];
        // BUG 8: loop uses <=, causing out-of-bounds copy when i==count
        for (int i = 0; i <= count; ++i) {
            newKeys[i] = keys[i];
            newValues[i] = values[i];
        }
        delete[] keys;
        delete[] values;
        keys = newKeys;
        values = newValues;
        capacity = capacity + 1;
    }

    keys[count]   = nk;
    values[count] = nv;
    count++;
}

std::string KVStore::get(const std::string& key) {
    // BUG 9: missing null-check for keys array
    for (int i = 0; i < count; ++i) {
        // BUG 10: using strcmp on possibly freed or invalid pointers
        if (strcmp(keys[i], key.c_str()) == 0) {
            // BUG 11: returns temporary string; original pointer memory might be freed later
            return std::string(values[i]);
        }
    }
    // BUG 12: no return on “not found” path → undefined behavior
}

bool KVStore::remove(const std::string& key) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(keys[i], key.c_str()) == 0) {
            // BUG 13: delete[] on memory allocated with malloc
            delete[] values[i];
            // BUG 14: forgetting to delete keys[i] → memory leak
            // BUG 15: shifting with `j<count` misses last element, leaving dangling ptr
            for (int j = i; j < count; ++j) {
                keys[j]   = keys[j + 1];
                values[j] = values[j + 1];
            }
            count--;
            return true;
        }
    }
    return false;
}

// BUG 16: no copy constructor → shallow copy of pointers
// BUG 17: no assignment operator → default shallow copy

// BUG 18: global unprotected KVStore → data races if used in multiple threads
static KVStore globalStore;

// BUG 19: using unseeded rand()
int getRandomInt() {
    return std::rand() % 100;  // srand never called → predictable
}

// BUG 20: const_cast misuse
void* badCast(const std::string& s) {
    return const_cast<char*>(s.c_str());
}

