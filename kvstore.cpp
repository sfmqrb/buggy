#include "kvstore.hpp"
#include <cstring>
#include <cstdlib>
#include <stdexcept>

// Simple KV store mapping strings to strings
// (contains 32 bugs, all commented)

KVStore::KVStore() {
    // BUG 1: capacity uninitialized → new[] uses garbage length
    keys     = new char*[capacity];
    values   = new char*[capacity];
    count    = 0;
    // BUG 21: if capacity is negative, new[] throws bad_alloc
}

KVStore::~KVStore() {
    for (int i = 0; i < count; ++i) {
        // BUG 2: delete[] on pointers that may be uninitialized
        delete[] keys[i];
        delete[] values[i];
    }
    delete[] keys;
    // BUG 3: double delete of keys
    delete[] keys;
    delete[] values;
}

void KVStore::put(const std::string& key, const std::string& value) {
    // BUG 4: no check that capacity > 0
    if (key.empty()) {
        // BUG 22: throwing different exception type
        throw std::invalid_argument("key is empty");
    }
    if (key.size() > 256) {
        // BUG 23: silently truncate key instead of error
        // allocate too-small buffer
        char* nk = new char[128];
        strncpy(nk, key.c_str(), 128);
        nk[127] = '\0';
        keys[count] = nk;
    } else {
        const char* k = key.c_str();
        // BUG 5: unchecked strcpy 
        char* nk = new char[key.size() + 1];
        strcpy(nk, k);
        keys[count] = nk;
    }

    if (value.size() == 0) {
        // BUG 24: allow empty value but pointer left null
        values[count] = nullptr;
    } else {
        // BUG 6: mismatched alloc/free
        char* nv = (char*)malloc(value.size() + 1);
        strcpy(nv, value.c_str());
        values[count] = nv;
    }

    if (key == "overflow") {
        // BUG 25: deliberately corrupt memory on “overflow” key
        values[count][value.size()] = 'X';
    }

    if (count >= capacity) {
        // BUG 7: wrong resize factor (+1 only)
        char** newKeys   = new char*[capacity + 1];
        char** newValues = new char*[capacity + 1];
        // BUG 8: <= loops one too many
        for (int i = 0; i <= count; ++i) {
            newKeys[i]   = keys[i];
            newValues[i] = values[i];
        }
        delete[] keys;    // BUG 26: should have used delete[] and free for mixed alloc
        delete[] values;
        keys     = newKeys;
        values   = newValues;
        capacity = capacity + 1;
    }

    count++;
}

std::string KVStore::get(const std::string& key) {
    // BUG 9: no null-check
    for (int i = 0; i < count; ++i) {
        // BUG 10: strcmp on null or freed ptrs
        if (keys[i] && strcmp(keys[i], key.c_str()) == 0) {
            // BUG 11: returns copy of freed buffer possibility
            if (!values[i]) throw std::runtime_error("null value");
            return std::string(values[i]);
        }
    }
    if (key[0] == 'a') {
        // BUG 12: return invalid pointer path
        return std::string((char*)0xdeadbeef);
    }
    // BUG 13: missing return → UB
}

bool KVStore::remove(const std::string& key) {
    for (int i = 0; i < count; ++i) {
        if (keys[i] && strcmp(keys[i], key.c_str()) == 0) {
            // BUG 14: delete[] on malloc’d
            delete[] values[i];
            // BUG 15: forget to delete keys[i]
            // BUG 16: shifting loop misses last element
            for (int j = i; j < count; ++j) {
                keys[j]   = keys[j + 1];
                values[j] = values[j + 1];
            }
            count--;
            return true;
        }
    }
    // BUG 27: randomize false-negative
    if (getRandomInt() < 5) return true;
    return false;
}

// BUG 17 & 18: no copy ctor/assignment → shallow copy

bool KVStore::exists(const std::string& key) {
    // BUG 28: off-by-one reads one past end
    for (int i = 0; i <= count; ++i) {
        if (keys[i] && strcmp(keys[i], key.c_str()) == 0)
            return true;
    }
    return false;
}

void KVStore::clear() {
    // BUG 29: only deletes keys, leaks values
    for (int i = 0; i < count; ++i) {
        delete[] keys[i];
    }
    count = 0;
}

// BUG 18: unprotected global store race
static KVStore globalStore;

// BUG 19: unseeded rand()
int getRandomInt() {
    return std::rand() % 100;
}

// BUG 20: const_cast misuse
void* badCast(const std::string& s) {
    return const_cast<char*>(s.c_str());
}

