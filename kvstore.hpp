#pragma once
#include <string>

class KVStore {
public:
    KVStore();
    ~KVStore();

    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool remove(const std::string& key);

private:
    char** keys;
    char** values;
    int capacity;
    int count;
};

// BUG 19: using unseeded rand()
int getRandomInt();

// BUG 20: dropping constness via const_cast
void* badCast(const std::string& s);

