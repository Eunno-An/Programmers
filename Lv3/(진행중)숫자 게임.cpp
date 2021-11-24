#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    multiset<int> set_B;
    for (int i = 0; i < B.size(); i++)
        set_B.insert(B[i]);
    //1 3 5 7 ->(A의1이랑 B의 2가 매칭) -> 3 5 7 (B의 2는 현재 할 수 있는게 없음). -> (B의 6은 5와 매칭) -> 3 7 -> (B의 8은 3와 매칭)
    
    //B에 대해서 A의 요소 하나하나 upper_bound를 수행하면
    //A[i]보다 큰 B를 찾는거니까 이게 더 말이 되지.
    //
    for (int i = 0; i < A.size(); i++) {
        auto elem = upper_bound(set_B.begin(), set_B.end(), A[i]);
        
        if (elem == set_B.end())//A의 요소가 B의 모든 요소보다 클 때
            continue;
        else {
            answer++;
            set_B.erase(elem);
        }
    }
    return answer;
}
