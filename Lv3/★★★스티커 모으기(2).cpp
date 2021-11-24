//fail
//실패의 이유: 그리디로 하면 될거라고 생각했음. 
//항상 그리디로 했을 때 안되면, 반드시 완전탐색 방법으로 돌아가서 생각해보고, 완탐이 시간초과가 날 것 같으면 DP로 넘어가자
//https://hwan-shell.tistory.com/265
//그리디로 풀면 안되는 이유가 나와있다.
//항상 선택을 하느냐 안하느냐로 풀어가야 한다.
//완전탐색으로 풀게 되면 반드시 10만개에 해당하는 요소를 하나씩 선택할지 안할지 재귀로 짜야 한다. 이러면 엄청난 시간초과가 날 것이다. 
//따라서 DP가 필요하다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int solution(vector<int> sticker)
{
    int answer = 0;
    int tempMax = 0;
    int n = sticker.size();
    vector<int> cache(sticker.size());
    if (sticker.size() == 1)
        return sticker[0];

    //첫번째 스티커를 뗀 경우
    cache[0] = sticker[0];
    cache[1] = cache[0];

    for (int i = 2; i < n - 1; i++)
        cache[i] = max(cache[i - 1], cache[i - 2] + sticker[i]);
    cache[n - 1] = cache[n - 2];
    tempMax = *max_element(cache.begin(), cache.end());

    //첫번째 스티커를 안뗀 경우
    cache[0] = 0;
    cache[1] = sticker[1];
    for (int i = 2; i < n; i++)
        cache[i] = max(cache[i - 1], cache[i - 2] + sticker[i]);

    answer = max(tempMax, *max_element(cache.begin(), cache.end()));

    return answer;
}
