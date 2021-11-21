#include <string>
#include <vector>
#include <cstring>
using namespace std;

int cache[2001];
long long solution(int n) {
    memset(cache, 0, sizeof(cache));
    long long answer = 0; 
    cache[1] = 1;
    cache[2] = 2;
    for(int i=3; i<=n; i++)
        cache[i] = (cache[i-1] % 1234567 + cache[i-2] % 1234567) % 1234567;
    answer = cache[n];
    return answer;
}
