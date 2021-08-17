//fail
//백준에서도 똑같이 나온 문제.
//아이디어가 정말 중요한 문제.. 다음에도 한번 풀어볼 것.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


long long solution(int n, vector<int> times) {
    long long answer = 0;
    sort(times.begin(), times.end());
    long long lo = 0;
    long long hi = times.back() * n;
    while(lo != hi){
        long long mid = (lo + hi) / 2;
        long long canDoIt = 0;
        for(int i=0; i<times.size(); i++)
            canDoIt += mid / times[i];
        if(canDoIt >= n)
            hi = mid;
        else
            lo = mid + 1;
    }
    return answer = lo;
}
