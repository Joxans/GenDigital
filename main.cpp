#include <iostream>
#include "LRUCache.h"
using namespace std;

void printResult(optional<string>& result)
{
    if (result)
        cout << "Cache hit: " << *result << endl;
    else
        cout << "Cache miss" << endl;
}

int main()
{
    LRUCache<int, string> cache(3);

    cache.put(1, "item1");
    cache.put(2, "item2");
    cache.put(3, "item3");

    optional<string> result = cache.get(1);
    printResult(result);

    cache.put(4, "item4");

    result = cache.get(2);
    printResult(result);

    return 0;
}
