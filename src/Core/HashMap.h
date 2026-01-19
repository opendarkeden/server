#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

// Cross-platform hash_map/unordered_map compatibility layer
#if defined(__APPLE__)
#include <unordered_map>
namespace std {
template <typename Key, typename Value> using hash_map = unordered_map<Key, Value>;
}
#elif defined(__LINUX__)
#include <ext/hash_map>
using __gnu_cxx::hash_map;
#elif defined(__WINDOWS__)
#include <hash_map>
using stdext::hash_map;
#endif

#endif // __HASH_MAP_H__
