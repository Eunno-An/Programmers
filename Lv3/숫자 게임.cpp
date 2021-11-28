//fail
//시간초과가 났음. 이유: multiset을 이용. 100000 * log(100000).
//시간제한이 명시는 되어있지 않았지만, 0.1초였을 것으로 예상함.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    //A: 1 3 5 7
    //B: 2 2 6 8
    //A를 큰 숫자부터 작은 숫자 순서대로 순회한다.
    //만약 A의 숫자를 B에서 이길 수 있다면, B에서 가장 큰 숫자부터 없앤다.
    //이길 수 없다면, B의 가장 작은 숫자랑 매칭시킨다
    int idx_start = 0, idx_end = B.size() - 1;
    int max_val = B[idx_end];
    for(int i=A.size()-1; i>=0; i--){
        if(A[i] < max_val){
            answer++;
            max_val = B[--idx_end];
        }
        else
            idx_start++;
        
    }
    return answer;
}

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
