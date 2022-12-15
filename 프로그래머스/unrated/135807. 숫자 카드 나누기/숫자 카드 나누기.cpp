#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> candidate, my, other;

void find_candidate(int num){
    candidate.push_back(num);
    for(int i = num / 2; i > 1; i--) //my의 최소 값인 num의 약수들 찾기
        if(num % i == 0) candidate.push_back(i);
    
}

int check(){
    int ret = 0;
    for(auto c : candidate){
        int flag = 1;
        for(int i = 0; i < my.size(); i++){
            if(my[i] % c != 0 || other[i] % c == 0){ //조건 불만족
                flag = 0;
                break; //이미 조건을 만족하지 못하므로 나머지 검사 x
            }
        }
        //후보군은 내림차순으로 정렬돼 있으므로 찾았으면 바로 종료
        if(flag){  
            ret = c;
            break;
        }
    }
    return ret; //ret 초기값이 0이므로 조건을 만족하는 수를 찾지 못하면 0을 반환함.
}

int solution(vector<int> arrayA, vector<int> arrayB) {
    int answer = 0;
    sort(arrayA.begin(), arrayA.end());
    sort(arrayB.begin(), arrayB.end());
    
    find_candidate(arrayA[0]);
    my = arrayA, other = arrayB;
    answer = max(answer, check());
    
    candidate.clear();
    my = arrayB, other = arrayA;
    find_candidate(arrayB[0]);
    answer = max(answer, check());
    
    return answer; //answer 초기값이 0이므로 조건을 만족하는 a를 찾지 못하면 0을 반환함.
}