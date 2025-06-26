#pragma once
#include <string>
#include <cstdint>   // for uint16_t

class KVStore {
public:
    KVStore();
    ~KVStore();

    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool remove(const std::string& key);

    bool exists(const std::string& key);
    void clear();

private:
    char** keys;
    char** values;
    uint16_t  capacity;
    uint16_t  count;     
};

// BUG 19: using unseeded rand()
int getRandomInt();

// BUG 20: dropping constness via const_cast
void* badCast(const std::string& s);

