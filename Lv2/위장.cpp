#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
//내 문제: 시뮬레이션을 돌려서, n이 30일 경우에 시간초과가 났음.
//경우의 수를 잘 생각해보면 쉽게 풀 수 있음.
//옷이 만약 (머리) 3가지, (몸) 2가지, (다리) 1가지 가 있다면 (3+1) * (2 + 1) * (1 + 1) - 1 로 경우의 수를 계산할 수 있음
//+1을 한 것은, 세개 중 하나를 입지 않은 경우이고,
//마지막에 -1을 한 것은 아무것도 안 잆는 경우는 없기 떄문임
//solve = 시뮬레이션 코드. 
map<string, vector<string>> cabinet;
vector<vector<string>> vec_cabinet;

int solution(vector<vector<string>> clothes) {
    int answer = 1;

    for (int i = 0; i < clothes.size(); i++) {
        string name_clothes = clothes[i][0];
        string kind_clothes = clothes[i][1];
        if (cabinet.find(kind_clothes) == cabinet.end()) {
            vector<string> vec_clothes;
            vec_clothes.push_back(name_clothes);
            cabinet.insert(make_pair(kind_clothes, vec_clothes));
        }
        else {
            cabinet[kind_clothes].push_back(name_clothes);
        }
    }

    for (map<string, vector<string>>::iterator it = cabinet.begin(); it != cabinet.end(); it++) {
        //vec_cabinet.push_back(it->second);
        answer *= (it->second.size() + 1);
    }
    answer -= 1;
    /*
    for (int i = 1; i <= cabinet.size(); i++) { //옷의 종류를 몇가지 뽑을 건지?
        answer += solve(i);
    }
    */
    return answer;
}
//int solve(int number_kind) {//뽑는 가짓수가 number_kind일 때, 서로 다른 옷의 조합의 수
//
//    if (vec_cabinet.size() < number_kind)
//        return 0;
//    vector<bool> v(vec_cabinet.size() - number_kind, false);
//    v.insert(v.end(), number_kind, true);
//    int ret = 0;
//    do {
//        int result = 1;
//        for (int i = 0; i < vec_cabinet.size(); i++) {
//            if (v[i]) result *= vec_cabinet[i].size();
//        }
//        ret += result;
//    } while (next_permutation(v.begin(), v.end()));
//    return ret;
//}
